#ifndef OPTIONS_OPTION_CATEGORY_H
#define OPTIONS_OPTION_CATEGORY_H

#include "option.h"
#include "option_value.h"

#include <iosfwd>

namespace options {

/// Class grouping options together into the same category.
/**
 * Option categories can then be passed to option parser. Program then can
 * be run in different modes with different options.
 */
class option_category {
public:
	// typedefs:
	typedef std::vector<option> options_type;
	typedef options_type::value_type value_type;
	typedef options_type::size_type size_type;
	typedef options_type::reference reference;
	typedef options_type::const_reference const_reference;
	typedef options_type::pointer pointer;
	typedef options_type::const_pointer const_pointer;
	typedef options_type::iterator iterator;
	typedef options_type::const_iterator const_iterator;

	// helpers:
	/// Proxy class used for better syntactic options managment.
	/**
	 * Class implements operator () and operator << for option insertion.
	 * operator () is mainly overloaded the same as option contructors.
	 */
	class option_proxy {
	public:
		/// \see option(std::string, std::string, std::string)
		option_proxy & operator ()(std::string shorts, std::string longs, std::string description);

		/// Operator with presence category.
		/**
		 * \see operator ()(std::string, std::string, std::string)
		 * \param category presence category of option indicates whether option is required/optional/forbidden.
		 */
		option_proxy & operator ()(std::string shorts,
			std::string longs,
			std::string description,
			presence_category category);

		/// \see option(std::string, std::string, std::string, option_value<T>)
		template<typename T>
		option_proxy & operator ()(std::string shorts,
			std::string longs,
			std::string description,
			option_value<T> holder)
		{
			parent_.options_.push_back(value_type(shorts, longs, description, holder));
			return * this;
		}

		/// Operator with presence category.
		/**
		 * \see operator ()(std::string, std::string, std::string, option_value<T> holder)
		 * \param category presence category of option indicates whether option is required/optional/forbidden.
		 */
		template<typename T>
		option_proxy & operator ()(std::string shorts,
			std::string longs,
			std::string description,
			option_value<T> holder,
			presence_category category)
		{
			value_type value(shorts, longs, description, holder);
			value.category(category);
			parent_.options_.push_back(value);
			return * this;
		}

		/// Overload for fully constructed option.
		/**
		 * Programmer may want to construct option outside proxy class, but doesn't want
		 * to give up syntactic sugar.
		 *
		 * \param value fully-constructed option object.
		 * \return Returns reference to itself.
		 */
		option_proxy & operator ()(value_type value);

		/// Overload for binary operator <<.
		/**
		 * Since operator << is binary, it can't get all syntactic features of
		 * operator (). It may only accept fully constructed options.
		 *
		 * \param value fully-constructed option object.
		 * \return Returns reference to itself.
		 */
		option_proxy & operator <<(value_type value);

	private:
		friend class option_category;

		// protection:
		option_proxy();
		NONCOPYMOVABLE(option_proxy)

		// create:
		/// Parametrized constructor used by friends of mine.
		/**
		 * \param parent reference to parent option_category object.
		 */
		explicit option_proxy(option_category & parent);
		
		option_category & parent_; ///< Reference to parent option_category object.
	};

	// create:
	/// Default constructor.
	/**
	 * Creates object with empty name, description and with no option.
	 */
	option_category();

	/// Parametrized constructor.
	/**
	 * Create object with desired name and description, but with no option.
	 *
	 * \param name option category name.
	 * \param description option category description. Defaulted to empty.
	 */
	explicit option_category(std::string name, std::string description = std::string());
	
	// iterators:
	/// Iterator to the beggining of option sequence.
	iterator begin();
	
	/// Constant iterator to the beggining of option sequence.
	const_iterator begin() const;
	
	/// Iterator right after end of option sequence.
	iterator end();
	
	/// Const iterator right after end of option sequence.
	const_iterator end() const;
	
	// size:
	/// Number of options inside category.
	size_type size() const;
	
	// manipulation:
	/// Function that creates header for both semantics.
	/**
	 * \see option_proxy
	 * \return Returns proxy object with this object as its parent.
	 *
	 * \code
	 *
	 * // the first syntax type:
	 * option_category category("Allowed options");
	 * category.add_options()
	 *         ("i", "include-files", "files included before program starts")
	 *         ("n", "number,num", "some number", option_value<int>(range<int>(0, 10)));
	 *
	 * // the second syntax type:
	 * option_category category("Allowed options");
	 * category.add_options()
	 *         << option("i", "include-files", "files included before program starts")
	 *         << option("n", "number,num", "some number", option_value<int>(range<int>(0, 10)));
	 *
	 * \endcode
	 */
	option_proxy add_options();

private:
	// category output:
	friend std::ostream & operator <<(std::ostream &, const option_category &);

	// data members:
	std::string name_;		///< Name of options category.
	std::string description_;	///< Description of category.
	options_type options_;		///< Vector of options that belongs to category.
};

/// Category output.
/**
 * Function prints options one by one in output stream.
 *
 * \param stream output stream.
 * \param category output category.
 * \return Returns reference to stream.
 */
std::ostream & operator <<(std::ostream & stream, const option_category & category);

} // namespace options

#endif // OPTIONS_OPTION_CATEGORY_H