#ifndef OPTIONS_OPTION_VALUE_H
#define OPTIONS_OPTION_VALUE_H

#include "option_restrictions.h"

#include <vector>
#include <memory>
#include <sstream>

namespace options {

/// Base class (interface) for any option value holder.
/**
 * Since we need support for different types as option values, we need to have different
 * types as holders for these values. Struct is abstract holder of all typed holders.
 */
struct placeholder
{
	// specialized function:
	/// Public virtual destructor means "deletable through base pointer" (mandatory).
	virtual ~placeholder()
	{}

	// value:
	/// Non-const version of value access.
	/**
	 * \return Returns pointer to memory location where value is stored.
	 */
	virtual void * value() = 0;

	/// Const version of value access.
	/**
	 * \return Returns pointer to constant memory location where value is stored.
	 */
	virtual const void * value() const = 0;

	// parse:
	/// Maximal number of values that can be parsed.
	virtual size_t size() const = 0;

	/// Parse argument as option value.
	/**
	 * \param argument option value represented as text.
	 * \return Returns true if option was parsed correctly, otherwise false.
	 */
	virtual bool parse(std::string argument) = 0;

	// miscellaneous:
	/// Prototype design pattern.
	/**
	 * \return Returns pointer to new heap allocated clone of current object.
	 * Caller is responsible for deallocation.
	 */
	virtual placeholder * clone() const = 0;

	/// Retrieve option value category.
	/**
	 * \return Returns option value presence category.
	 */
	virtual presence_category category() const = 0;
	
};

/// Templated class holding value of any type as option value.
/**
 * Class is inherited from placeholder class.
 */
template<typename T>
class option_value : public placeholder {
public:
	// typedefs:
	typedef T value_type;
	typedef option_restriction<value_type> restriction_type;

	//
	// create/copy/move:
	//

	/// Default/parametrized constructor.
	/** 
	 * Creates class with default construct value and OPTIONAL category that
	 * effectively means value doesn't have to be presented and default will be used.
	 *
	 * \param default_value initialization value. It won't be changed until argument is parsed.
	 * \param category indicates whether value is mandatory or optional.
	 */
	explicit option_value(value_type default_value = value_type(), presence_category category = OPTIONAL)
		: value_(default_value)
		, category_(category)
		, restriction_(NULLPTR)
	{}

	/// Templated constructor with restriction type.
	/** 
	 * \see option_value(value_type, presence_category)
	 * \param restriction object of class implementing restriction<T> interface.
	 */
	template<typename Restriction>
	explicit option_value(Restriction restriction,
		value_type default_value = value_type(),
		presence_category category = OPTIONAL)
		: value_(default_value)
		, category_(category)
		, restriction_(new Restriction(restriction))
	{}

	// specialized functions:
	option_value(const option_value & other)
		: value_(other.value_)
		, category_(other.category_)
		, restriction_(NULLPTR)
	{
		if (other.restriction_.get() != NULLPTR) {
			restriction_.reset(other.restriction_->clone());
		}
	}

	option_value(option_value && other)
		: value_(std::move(other.value_))
		, category_(other.category_)
		, restriction_(std::move(other.restriction_))
	{}

	option_value & operator =(option_value other)
	{
		swap(other);
		return *this;
	}

	option_value & operator =(option_value && other)
	{
		value_ = std::move(other.value_);
		category_ = other.category_;
		restriction_ = std::move(other.restriction_);
		return *this;
	}

	// inherited members:
	/// \see placeholder::value()
	virtual void * value()
	{
		return &value_;
	}

	/// \see placeholder::value() const
	virtual const void * value() const
	{
		return &value_;
	}

	/// \see placeholder::clone() const
	virtual placeholder * clone() const
	{
		return new option_value(*this);
	}

	/// \see placeholder::size() const
	virtual size_t size() const
	{
		return VALUE_COUNT;
	}

	/// \see placeholder::parse(std::string)
	virtual bool parse(std::string parameter)
	{
		try {
			value_ = lexical_cast<value_type>(parameter);
		} catch (bad_lexical_cast e) {
			return false;
		}

		if (restriction_.get() != NULLPTR) {
			return restriction_->accept(value_);
		}

		return true;
	}

	/// \see placeholder::category() const
	virtual presence_category category() const
	{
		return category_;
	}

	// miscellaneous:
	/// Swap content with other object.
	/**
	 * Standard function provided for hard to copy objects.
	 */
	void swap(option_value & other) // noexcept
	{
		std::swap(value_, other.value_);
		std::swap(category_, other.category_);
		std::swap(restriction_, other.restriction_);
	}

private:
	// data members:
	value_type value_;					///< Storage for option value.
	presence_category category_;				///< Option value presence category.
	std::unique_ptr<restriction_type> restriction_;		///< Pointer to base restrition object.

	/// Number of values holded by class object.
	static const size_t VALUE_COUNT = 1;
};

/// Specialized template for holder of vector of values.
/**
 * Class is used for options with multiple values like for example include files option.
 */
template<typename T>
class option_value<std::vector<T>> : public placeholder {
public:
	// typedefs:
	typedef T value_type;
	typedef option_restriction<T> restriction_type;

	// create/copy/move:
	/// Default/parametrized constructor.
	/**
	 * Initializes presence category of option, defaulted to OPTIONAL.
	 *
	 * \param category indicates whether value is mandatory or optional.
	 */
	explicit option_value(presence_category category = OPTIONAL)
		: values_()
		, category_(category)
		, restriction_(std::unique_ptr<restriction_type>(NULLPTR))
	{}

	/// Templated constructor with restriction type.
	/** 
	 * \see option_value(presence_category)
	 * \param restriction object of class implementing restriction<T> interface.
	 */
	template<typename Restriction>
	explicit option_value(Restriction restriction, presence_category category = OPTIONAL)
		: values_()
		, category_(category)
		, restriction_(new Restriction(restriction))
	{}

	// specialized functions:
	option_value(const option_value & other)
		: values_(other.values_)
		, category_(other.category_)
		, restriction_(NULLPTR)
	{
		if (other.restriction_.get() != NULLPTR) {
			restriction_.reset(other.restriction_->clone());
		}
	}

	option_value(option_value && other)
		: values_(std::move(other.values_))
		, category_(other.category_)
		, restriction_(std::move(other.restriction_))
	{}

	option_value & operator =(option_value other)
	{
		swap(other);
		return *this;
	}

	option_value & operator =(option_value && other)
	{
		values_ = std::move(other.values_);
		category_ = other.category_;
		restriction_ = std::move(other.restriction_);
		return *this;
	}

	// inherited members:
	/// \see placeholder::value()
	virtual void * value()
	{
		return &values_;
	}

	/// \see placeholder::value() const
	virtual const void * value() const
	{
		return &values_;
	}

	/// \see placeholder::clone() const
	virtual placeholder * clone() const
	{
		return new option_value(*this);
	}

	/// \see placeholder::size() const
	virtual size_t size() const
	{
		return values_.max_size();
	}

	/// \see placeholder::parse(std::string)
	virtual bool parse(std::string value)
	{
		try {
			value_type result = lexical_cast<value_type>(value);

			if ((restriction_.get() != NULLPTR) && !restriction_->accept(result)) {
				return false;
			}

			values_.push_back(result);
		} catch (bad_lexical_cast e) {
			return false;
		}

		return true;
	}

	/// \see placeholder::category() const
	virtual presence_category category() const
	{
		return category_;
	}

	// miscellaneous:
	/// Swap content with other object.
	/**
	 * Standard function provided for hard to copy objects.
	 */
	void swap(option_value & other) // noexcept
	{
		std::swap(values_, other.values_);
		std::swap(category_, other.category_);
		std::swap(restriction_, other.restriction_);
	}

private:
	// typedefs:
	typedef std::vector<value_type> values;

	// data members:
	values values_;						///< Vector of option values.
	presence_category category_;				///< Option presence category.
	std::unique_ptr<restriction_type> restriction_;		///< Pointer to base restriction object.
};

} // namespace options

#endif // OPTIONS_OPTION_VALUE_H
