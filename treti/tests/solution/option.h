#ifndef OPTIONS_OPTION_H
#define OPTIONS_OPTION_H

#include "common.h"
#include "option_value.h"

#include <vector>
#include <iterator>
#include <memory>
#include <string>
#include <iosfwd>

namespace options {

/// Class representing program option.
/**
 * Program option supports multiple short and long aliases and holding values, one or more.
 * This class should be used like immutable class, even though there's way of manipulating
 * its content (not all content).
 */
class option {
public:
	// typedefs:
	typedef char short_name_type;
	typedef std::vector<short_name_type> short_names_type;
	typedef short_names_type::iterator short_names_iterator;
	typedef short_names_type::const_iterator short_names_const_iterator;

	typedef std::string long_name_type;
	typedef std::vector<long_name_type> long_names_type;
	typedef long_names_type::iterator long_names_iterator;
	typedef long_names_type::const_iterator long_names_const_iterator;

	typedef size_t size_type;

	//
	// create/copy/move:
	//

	/// Create empty option.
	/** 
	 * Be aware that there's no way to add holder of option after its creation.
	 * \see templated version of constructor.
	 */
	option();
	
	/// Create option with multiple aliases and description.
	/** 
	 * \param shorts string of short name aliases.
	 * \param longs string of long name aliases seperated by ',' character
	 * \param description string representing option description.
	 */
	option(std::string shorts, std::string longs, std::string description);
	
	/// Create option with multiple aliases and value holder.
	/**
	 * \see option(std::string, std::string, std::string)
	 * \param holder object of holder for option value.
	 */
	template<typename T>
	option(std::string shorts, std::string longs, std::string description, option_value<T> holder)
		: short_names_()
		, long_names_()
		, description_()
		, placeholder_(new option_value<T>(holder))
		, category_(OPTIONAL)
		, marked_(false)
	{
		parse_names(shorts, longs, description);
	}

	// specialized functions:
	option(const option & other);
	option(option && other);
	option & operator =(const option & other);
	option & operator =(option && other);

	//
	// size:
	//

	/// Number of short name aliases stored in option.
	size_type short_names_size() const;

	/// Number of long name aliases stored in option.
	size_type long_names_size() const;

	/// Indicates whether option has value or not.
	bool empty() const;

	//
	// iterators:
	//

	/// Iterator to the beggining of short names sequence.
	short_names_iterator short_names_begin();

	/// Constant iterator to the beggining of short names sequence.
	short_names_const_iterator short_names_begin() const;

	/// Iterator right after end of short names sequence.
	short_names_iterator short_names_end();
	
	/// Constant iterator right after end of short names sequence.
	short_names_const_iterator short_names_end() const;
	
	/// Iterator to the beggining of long names sequence.
	long_names_iterator long_names_begin();
	
	/// Constant iterator to the beggining of long names sequence.
	long_names_const_iterator long_names_begin() const;
	
	/// Iterator right after end of long names sequence.
	long_names_iterator long_names_end();

	/// Constant iterator right after end of long names sequence.
	long_names_const_iterator long_names_end() const;

	//
	// manipulation:
	//

	/// Insert new short name alias int option.
	/**
	 * Function doesn't crash. In case new alias would be redundant,
	 * it will just ignore it.
	 *
	 * \param name short name alias to be inserted.
	 */
	void insert_short_name(short_name_type name);

	/// Erase short name alias from list.
	/**
	 * \param name short name alias to be erased from aliases.
	 */
	void erase_short_name(short_name_type name);

	/// Insert new long name alias into option.
	/**
	 * Function doesn't crash. In case new alias would be redundant,
	 * it will just ignore it.
	 *
	 * \param name long name alias to be inserted.
	 */
	void insert_long_name(long_name_type name);

	/// Erase long name alias from list.
	/** 
	 * \param name long name alias to be erased from aliases.
	 */
	void erase_long_name(long_name_type name);

	//
	// category:
	//

	/// Getter for option category.
	/**
	 * \return Returns current option category.
	 */
	presence_category category() const;

	/// Setter for option category.
	/**
	 * \param category category to be set.
	 */
	void category(presence_category category);

	/// Getter for option value category.
	/**
	 * \return Returns current option value presence category.
	 */
	presence_category value_category() const;

	//
	// evaluation:
	//

	/// Set option as marked.
	/**
	 * Function is used to indicate whehter option was parsed or not. After marking,
	 * there's not way to unmark option.
	 */
	void mark();

	/// Type cast pperator that evaluates true if option is marked.
	operator bool() const;

	/// Negation of operator bool return value.
	bool operator !() const;

	//
	// value access:
	//

	/// Number of arguments representing option value.
	/**
	 * Different options can take different number of arguments as values.
	 *
	 * \return Returns maximal number of arguments representing option values.
	 * 0 for option without value.
	 */
	size_type size() const;

	/// Parse value of option.
	/**
	 * Function is available only for options with value holder.
	 *
	 * \param argument command line argument representing option value.
	 * \return Returns true if argument was parsed correctly, otherwise false.
	 */
	bool parse_value(std::string argument);

	//
	// miscellaenous:
	//

	/// Standard way of providing manipulation with hard copyable items.
	/**
	 * \param other object of the same class to swap content with.
	 * \throws nothing.
	 */
	void swap(option & other); // noexcept

	/// Publicly accessed constant of delimiter character for long options.
	static const char LONG_NAME_DELIMITER = ',';

private:
	// friends:
	template<typename T>
	friend T option_cast(const option &);
	friend std::ostream & operator <<(std::ostream &, const option &);

	/// Function parses names and store them in appropriate structures.
	/**
	 * Since class supports mutliple aliases for short and long options and
	 * C++11 standard initializers lists nor variadic templates are widely
	 * supported. We need to allow programmer to simply insert aliases.
	 *
	 * \param shorts string with short aliases.
	 * \param longs string with long aliases separated by ','
	 * \param description string with option description.
	 */
	void parse_names(std::string shorts, std::string longs, std::string description = std::string());

	// data members:
	short_names_type short_names_;			///< List of short name aliases.
	long_names_type long_names_;			///< List of long name aliases.
	std::string description_;			///< Option text description.
	std::unique_ptr<placeholder> placeholder_;	///< Pointer to holder of option value.
	presence_category category_;			///< Presence category of option.
	bool marked_;					///< Indicator whether option was parsed or not.

	static const int STRING_COMPARE_SUCCESS = 0;	///< Value representing success in string comparison.
};

/// Casting of option value.
/**
 * Option value is hidden behind placeholder that only has access
 * to memory location of stored value. Cast is used to represent
 * this memory location as memory location of specific type.
 *
 * \param operand option object which value we want to gain.
 * \return Value of desired type stored in option.
 */
template<typename T>
T option_cast(const option & operand)
{
	return *reinterpret_cast<T *>(operand.placeholder_->value());
}

/// Option output function.
/**
 * Function outputs option into stream
 *
 * \param stream output stream.
 * \param operand const reference to output option.
 * \return Returns reference to stream.
 */
std::ostream & operator <<(std::ostream & stream, const option & operand);

} // namespace options

namespace std {

/// Overload of standard swap function for option class.
/**
 * \param lhs left-handed side operand.
 * \param rhs right-handed side operand.
 */
template<>
void swap(options::option & lhs, options::option & rhs);

} // namespace std

#endif // OPTIONS_OPTION_H
