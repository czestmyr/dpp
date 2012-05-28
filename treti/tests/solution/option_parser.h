#ifndef OPTIONS_OPTION_PARSER_H
#define OPTIONS_OPTION_PARSER_H

#include "option_category.h"

#include <map>
#include <vector>
#include <string>
#include <iosfwd>

namespace options {

/// Parsing class for command line.
/**
 * Class is used as container for option categories and parses commandline
 * using options in owned categories.
 */
class option_parser {
public:
	// typedefs:
	typedef std::string argument_type;
	typedef std::vector<argument_type> arguments_type;
	typedef option::short_name_type short_name_type;
	typedef option::long_name_type long_name_type;

	typedef option::size_type size_type;

	// create:
	/// Default constructor.
	/**
	 * Creates object with no option categories.
	 */
	option_parser();

	/// Parametrized constructor.
	/**
	 * Creates object with just one category. Constructor is equivalent with
	 * \code
	 * option_parser parser;
	 * parser.add_category(category);
	 * \endcode
	 *
	 * \param category initialization category.
	 */
	explicit option_parser(option_category & category);

	/// Parametrized constructor.
	/**
	 * Creates object with just one category and parse command line.
	 * Constructor is equivalent with
	 * \code
	 * option_parser parser;
	 * parser.add_category(category);
	 * parser.parse(argc, argv);
	 * \endcode
	 *
	 * \param category initialization category.
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 */
	option_parser(option_category & category, int argc, char * argv[]);

	// manipulation:
	/// Function that add option category into command line.
	/**
	 * After adding category there is no way to remove that category from parser.
	 * Categories are stored as copies so your category object can't be used as
	 * accessor to parsed options.
	 *
	 * \param category new inserted category.
	 */
	void add_category(option_category & category);

	/// Parses command line.
	/**
	 * There should be at least one category inserted, otherwise its useless
	 * runtime overhead.
	 * 
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \return Returns true if parsing was successful, otherwise false.
	 */
	bool parse(int argc, char * argv[]);

	// accessors:
	/// Accessor for short name options.
	/**
	 * In case name is not presented in any option of inserted categories,
	 * assertion arise.
	 *
	 * \param name short option name.
	 * \return Returns const reference to corresponding option.
	 * \see option
	 */
	const option & operator [](short_name_type name) const;

	/// Accessor for long name options.
	/**
	 * In case name is not presented in any option of inserted categories,
	 * assertion arise.
	 *
	 * \param name long option name.
	 * \return Returns const reference to corresponding option.
	 * \see option
	 */
	const option & operator [](long_name_type name) const;

	/// Accessor for parsed arguments.
	/**
	 * \return Returns std::vector of arguments.
	 */
	arguments_type arguments() const;

private:
	// parser output:
	friend std::ostream & operator <<(std::ostream &, const option_parser &);

	// typedefs:
	typedef std::map<short_name_type, option *> short_options_type;
	typedef std::map<long_name_type, option *> long_options_type;
	typedef std::vector<option_category> categories_type;

	/// Enumeration of arguments type that can show in command line.
	enum parse_type {
		SHORT_OPTION,		///< Argument is short option.
		LONG_OPTION,		///< Argument is long option.
		DELIMITER_OPTION,	///< Argument is delimiter of options and regular arguments.
		ARGUMENT		///< Regular argument.
	};

	// helpers:
	/// Builds options map before parsing.
	/**
	 * Function passes all categories and maps short and long names to
	 * corresponding option objects. This should speedup parsging.
	 */
	void build_maps();

	/// Builds map over one category.
	/**
	 * \param category non-const reference to options category whos map will be built.
	 */
	void build_maps(option_category & category);

	/// Add option names into map.
	/**
	 * Each option can have multiple short and long names. We need to
	 * parse them and store in std::map for better runtime performance.
	 *
	 * \param operand non-const reference to option object.
	 */
	void build_maps(option & operand);

	/// Check whether all required options are marked.
	/**
	 * Function is called after parsing passed to indicates whether all required
	 * options are presented.
	 *
	 * \return Returns true if every required option is marked, otherwise false.
	 */
	bool check_required() const;

	/// Overload for category check.
	/**
	 * \see check_required() const
	 */
	bool check_required(const option_category & category) const;

	/// Parse command line arguments.
	/**
	 * Basically it means copying command line arguments into local storage.
	 *
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument from where to start parsing.
	 */
	void parse_arguments(int argc, char * argv[], int argi);

	/// Parse short option argument.
	/**
	 * Short option argument can contain more than one options and value.
	 * Last option can also contain value(s).
	 * 
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument to parse.
	 * \return Returns index of argument where parsing should continue.
	 */
	int parse_short_options(int argc, char * argv[], int argi);

	/// Parse long option argument.
	/**
	 * There can be only one long option name in one argument, but it can also
	 * contain value(s).
	 *
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument to parse.
	 * \return Returns index of argument where parsing should continue.
	 */
	int parse_long_option(int argc, char * argv[], int argi);

	/// Parse option value(s).
	/**
	 * Helper that helps parsing options with values.
	 *
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument to parse.
	 * \param index index right after last character of option thats value will be parsed.
	 * \param operand pointer to option which value is being parsed.
	 * \return Returns index of argument where parsing should continue.
	 */
	int parse_option_value(int argc, char * argv[], int argi, int index, option * operand);

	//
	// statics:
	//

	/// Function just templated prints error message.
	/**
	 * \param message text that will be printed right after error report.
	 */
	static void print_simple_error_header(std::string message);

	/// Function prints header for error message.
	/**
	 * Output of function is one line of error message, another line of command line,
	 * and one line with pointer and specific message.
	 *
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument to parse.
	 * \param index index right after last character of option thats value will be parsed.
	 * \param message text that will be printed right behind pointer.
	 */
	static void print_error_header(int argc, char * argv[], int argi, int index, std::string message);

	/// Function prints command line with all its arguments.
	/**
	 * \param argc arguments count.
	 * \param argv c-like array of c-like strings of arguments.
	 */
	static void print_error_command_line(int argc, char * argv[]);

	/// Count position for error pointer.
	/**
	 * \param argv c-like array of c-like strings of arguments.
	 * \param argi index of argument to parse.
	 * \param index index right after last character of option thats value will be parsed.
	 * \return Returns position on line for error pointer.
	 */
	static size_type error_position(char * argv[], int argi, int index);

	/// Gather argument type.
	/**
	 * In case argument is empty string, assertion arise.
	 *
	 * \param argument text representation of argument.
	 * \return Returns argument type.
	 * \see parse_type
	 */
	static parse_type type(std::string argument);

	// data members:
	categories_type categories_;		///< List of categories.
	short_options_type short_options_;	///< Map of short option names to corresponding options.
	long_options_type long_options_;	///< Map of long option names to corresponding options.
	arguments_type arguments_;		///< List of arguments.

	// constants:
	static const int PARSE_ERROR;

	static const std::string PARSE_ERROR_MESSAGE;
	static const std::string PARSE_ERROR_PROGRAM;
	static const std::string PARSE_ERROR_POINTER;
	static const std::string PARSE_ERROR_END;
	static const int PARSE_ERROR_INDENT_SIZE;
	static const char PARSE_ERROR_INDENT;
	static const char PARSE_OPTION_MARK;
	static const char PARSE_OPTION_VALUE_DELIMITER;

	static const int PARSE_STARTING_INDEX;
	
};

/// Parser output.
/**
 * Function prints into output stream categories one by one.
 *
 * \param stream output stream.
 * \param parser parser object that will be output into stream.
 * \return Returns reference to stream object.
 */
std::ostream & operator <<(std::ostream & stream, const option_parser & parser);

} // namespace options

#endif // OPTIONS_OPTION_PARSER_H
