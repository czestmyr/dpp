#ifndef OPTIONS_OPTIONS_H
#define OPTIONS_OPTIONS_H

/** \mainpage Program options
 * 
 * \section section_intro Introduction
 * Program options library allows user to parse and access command line options and arguments easily.
 *
 * - Handwritten parsing is quiet hard to do in C++ and standard library doesn't support such functionality.
 *
 * - Using options in command line is very common thing even in GUI applications.
 *
 * - C++ syntax is very strong and can make options definitions and access readable and comprendious.
 *
 * \section section_starting Getting started
 * Lets start with few examples of how to use library.
 *
 * \subsection subsection_syntax Supported syntax
 * There are 2 possible syntaxes of defining options. They are available through option_category::add_options()
 * \see options::option_category::add_options()
 *
 * _The first syntax type_
 * \code
 * using namespace options;
 *
 * option_category category("Allowed options");
 * category.add_options()
 *         ("i", "include-files", "files included before program starts")
 *         ("n", "number,num", "some number", option_value<int>(range<int>(0, 10)));
 * \endcode
 *
 * _The second syntax type_
 * \code
 * using namespace options;
 *
 * option_category category("Allowed options");
 * category.add_options()
 *         << option("i", "include-files", "files included before program starts")
 *         << option("n", "number,num", "some number", option_value<int>(range<int>(0, 10)));
 * \endcode
 * 
 * \subsection subsection_definition Defining options
 * Arguments of operator () used in options definition are the same
 * as arguments for option class + its copy constructor overload.
 * \see options::option
 *
 * Firstly we need to define categories of options. For example _Allowed options_, _Input files_, etc.
 * Then we add add these categories into command line parser.
 * \see options::option_parser::add_category(option_category &)
 *
 * \subsection subsection_parsing Parsing
 * There is parse function on parser class getting command line arguments and parses them.
 * This function returns value indicating whether parsing was successful.
 *
 * \code
 * using namespace options;
 *
 * option_category allowed("Allowed options");
 * allowed.add_options()
 *         ("h", "help", "prints this help")
 *         ("lL", "level,debug-level", "sets debug level on range from 0-5", option_value<int>(range<int>(0, 5), 1))
 *         ("iI", "input-files", "files where input values are get from", option_value<std::vector<std::string>>());
 *
 * option_parser parser(allowed);
 * if (!parser.parse(argc, argv)) {
 *         std::cerr << parser;
 *         return ERROR;
 * }
 * \endcode
 *
 * \subsection subsection_results Parsing results
 * Parser supports overload of operator [] for both short and long options names. Operator returns reference
 * to corresponsing option object that supports overload for bool type cast and operator !. You can then
 * test whether option was presented or not.
 *
 * To access option value use option_cast.
 * \see options::option_cast<T>(const options::option &)
 *
 * \code
 * using namespace options;
 *
 * option_parser parser;
 *
 * ...
 *
 * if (parser["help"]) {
 *         std::cout << parser;
 *         return SUCCESS;
 * }
 *
 * int debug_level = option_cast<int>(parser["level"]);
 * \endcode
 *
 * \section section_advanced Advanced
 * Options with values can use restrictions for these values. Library support few of them like range, lower_bound, etc.
 * You can find them in \see option_restrictions.h
 * 
 * You can also define your own restriction by implementing interface option_restriction<T>.
 * \see options::option_restriction
 *
 * \section section_files Files
 * - option.h
 * definiton of option and option_cast.
 *
 * - option_parser.h
 * definition of parser
 *
 * - option_category.h
 * definition of category and its inner proxy class.
 *
 * - option_value.h
 * definition of option_value template and specialized template for std::vector values.
 *
 * - option_restrictions.h
 * definition of base class for all restriction and few restriction definitions.
 *
 */

#include "option.h"
#include "option_parser.h"
#include "option_value.h"
#include "option_category.h"
#include "option_restrictions.h"

#endif // OPTIONS_OPTIONS_H