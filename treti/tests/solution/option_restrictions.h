#ifndef OPTIONS_OPTION_RESTRICTIONS_H
#define OPTIONS_OPTION_RESTRICTIONS_H

#include <vector>
#include <algorithm>
#include <iterator>

namespace options {

/// Base class for restriction over type.
/**
 * All restrictions has to implement this simple interface.
 */
template<typename T>
struct option_restriction {
	// typedefs:
	typedef T value_type;

	/// Public virtual destructor means "deletable through base pointer".
	virtual ~option_restriction()
	{}

	/// Acceptance function.
	/**
	 * Function indicates whether value is accepted by restriction.
	 *
	 * \param value tested value.
	 * \return Returns true if restriction allows value to be stored in option, otherwise false.
	 */
	virtual bool accept(value_type value) const = 0;

	/// Prototype design pattern.
	/**
	 * \return Returns pointer to new allocated object.
	 * Caller is responsible for its deallocation.
	 */
	virtual option_restriction * clone() const = 0;
};

/// Restriction accepting any value.
template<typename T>
class any : public option_restriction<T> {
public:
	// typedefs:
	typedef T value_type;
	typedef any restriction_type;

	// inehrited memebers:
	/// \see option_restriction<T>::accept(value_type) const
	virtual bool accept(value_type value) const
	{
		return true;
	}

	/// \see option_restriction<T>::clone() const
	virtual option_restriction<T> * clone() const
	{
		return new any;
	}
};

/// Restriction for range of values.
template<typename T>
class range : public option_restriction<T> {
public:
	// typedefs:
	typedef T value_type;
	typedef range restriction_type;

	// create:
	/// Parametrized constructor.
	/**
	 * Creates object with desired minimal and maximal values (inclusive).
	 *
	 * \param min minimal value allowed by restriction.
	 * \param max maximal value allowed by restriction.
	 */
	range(value_type min, value_type max)
		: min_(min)
		, max_(max)
	{}

	// inehrited memebers:
	/// \see option_restriction<T>::accept(value_type) const
	virtual bool accept(value_type value) const
	{
		return (value >= min_) && (value <= max_);
	}

	/// \see option_restriction<T>::clone() const
	virtual option_restriction<T> * clone() const
	{
		return new range(*this);
	}

private:
	value_type min_; ///< Minimal value accepted by restriction.
	value_type max_; ///< Maximal value accepted by restriction.
};

/// Restriction with lower bound for values.
template<typename T>
class lower_bound : public option_restriction<T> {
public:
	// typedefs:
	typedef T value_type;
	typedef lower_bound restriction_type;

	// create:
	/// Parametrized constructor.
	/**
	 * Creates object with desired minimal value (inclusive).
	 *
	 * \param bound minimal value accepted by restriction.
	 */
	explicit lower_bound(value_type bound)
		: bound_(bound)
	{}

	// inherited members:
	/// \see option_restriction<T>::accept(value_type) const
	virtual bool accept(value_type value) const
	{
		return (value >= bound_);
	}

	/// \see option_restriction<T>::clone() const
	virtual option_restriction<T> * clone() const
	{
		return new lower_bound(*this);
	}

private:
	value_type bound_; ///< Minimal value accepted by restriction.
};

/// Restriction with upper bound for values.
template<typename T>
class upper_bound : public option_restriction<T> {
public:
	// typedefs:
	typedef T value_type;
	typedef upper_bound restriction_type;

	// create:
	/// Parametrized constructor.
	/**
	 * Creates object with desired maximal value (inclusive).
	 *
	 * \param bound maximal value accepted by restriction.
	 */
	explicit upper_bound(value_type bound)
		: bound_(bound)
	{}

	// inherited members:
	/// \see option_restriction<T>::accept(value_type) const
	virtual bool accept(value_type value) const
	{
		return (value <= bound_);
	}

	/// \see option_restriction<T>::clone() const
	virtual option_restriction<T> * clone() const
	{
		return new upper_bound(*this);
	}

private:
	value_type bound_; ///< Maximal value accepted by restriction.
};

/// Restriction accepting only values from set.
template<typename T>
class enumeration : public option_restriction<T> {
public:
	// typedefs:
	typedef T value_type;
	typedef enumeration restriction_type;

	// create:
	/// Default constructor.
	/**
	 * Creates empty enumeration. Effectively enumeration that doesn't accept any value.
	 */
	enumeration()
		: values_()
	{}

	/// Parametrized constructor.
	/**
	 * Creates enumeration with values stored in [first, last) sequence.
	 * Constructor accepts input iterators.
	 *
	 * \param first iterator to the begging of sequence.
	 * \param last iterator right after end of sequence.
	 */
	template<typename InputIterator>
	enumeration(InputIterator first, InputIterator last)
		: values_()
	{
		std::copy(first, last, std::back_inserter(values_));
	}

	// manipulation:
	/// Add new value to enumeration.
	/**
	 * Function controls for duplicities. If value is already presented, it is ignored.
	 *
	 * \param value new enumeration value.
	 * \return Returns reference to this object so operations can be chained.
	 */
	enumeration & add(value_type value)
	{
		if (std::find(values_.begin(), values_.end(), value) == values_.end()) {
			values_.push_back(value);
		}
		return *this;
	}

	/// Add new value to enumeration.
	/**
	 * Function is just syntactic sugar to add member function.
	 *
	 * \code
	* enumeration<std::string> answers;
	 * answers << "yes"
	 *         << "no"
	 *         << "cancel";
	 * \endcode
	 *
	 * \see add(value_type)
	 */
	enumeration & operator <<(value_type value)
	{
		return add(value);
	}

	// inherited members:
	/// \see option_restriction<T>::accept(value_type) const
	virtual bool accept(value_type value) const
	{
		return (std::find(values_.begin(), values_.end(), value) != values_.end());
	}

	/// \see option_restriction<T>::clone() const
	virtual option_restriction<T> * clone() const
	{
		return new enumeration(*this);
	}

private:
	// typedefs:
	typedef std::vector<value_type> values_type;

	values_type values_; ///< Set of values accepted by restriction.
};

} // namespace options

#endif // OPTIONS_OPTION_RESTRICTIONS_H
