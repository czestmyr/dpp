// Prevent including this file. It only serves as a place for the front-page documentation in doxygen.
#error This file should not be included anywhere. It does not contain anything useful
/*! \mainpage Arglib library documentation
 * 
 * \section intro_sec Introduction
 *
 * Arglib is a university project for the course Recommended Programming Practices at the Charles University in Prague.
 * It is a command-line parsing library that supports short and long format options with or without parameters as well
 * as regular arguments (i.e. not options). The parameters can have any of the built-in types - see Type hierarchy.
 * If that was not enough, the user can use inheritance to create new types. The library was created by Čestmír Houška
 * and Martin Bulant.
 *
 * \section using_sec Using Arglib
 *
 * \subsection compile_link_subsec Compilation and Linking
 *
 * Compilation of the library is very easy. It uses only the STL library, so you should have no problems with it. If
 * you are working on a *nix environment, a Makefile is included in the src directory that compiles the library with
 * the \t g++ compiler and creates a library archive with \t ar. This archive will be named \b arglib.a
 *
 * So you have basically two options when you want to use Arglib:
 * \li You can either include all of the sources in the /src directory into your project and compile the library with
 * your project
 * \li Or, which we encourage you to do, you can compile the library into the aforementioned \b arglib.a archive and
 * link against it. To compile the source files that will use the library, you just have to include
 * \b /src/Arglib.h
 *
 * \subsection tests_subsec Tests and Use Cases
 *
 * The distribution of the library contains some basic tests as well as use cases which you can study to learn how to
 * use the library. If you make the library from the main directory, all the tests and use cases will be compiled as
 * well and if successful, the tests will be run to check if the library works.
 *
 * \subsection basic_subsec Basic Usage
 *
 * All of our library is contained in the namespace \t Arglib, so you either have to prepend everything with
 * \t Arglib::, or just write into all your soruce files:
 * \code
 * using namespace Arglib;
 * \endcode
 *
 * To start using the library, you just need to look at the documentation for the class Arglib::FrontEnd. For every
 * set of command-line arguments that you want to parse (which is, in most cases, one), you create an instance of
 * this class, call the Arglib::FrontEnd::addOption several times together with Arglib::FrontEnd::addSynonym to
 * define allowed options:
 * \code
 * using namespace Arglib;
 *
 * FrontEnd arglib;
 * arglib.addOption("version");
 * arglib.addSynonym("version", "v");
 * arglib.addOption("file", OPTION_ALLOWED, StringType(), PARAM_REQUIRED);
 * arglib.addSynonym("file", "input-file");
 * arglib.addSynonym("file", "f");
 *
 * // etc...
 * \endcode
 *
 * Then, you can parse the arguments from the command line. To do that, just pass the \t argv and \t argc arguments
 * from the standard C++ main function to the Arglib::FrontEnd::parse() function. It will parse the arguments,
 * possibly throwing some an exception or two in the process (just kidding, one is enough). The exceptions are all of
 * a type Arglib::ArgumentException, meaning that the exception occured during parsing or processing the arguments.
 * The FrontEnd then saves the argument data into the internal structures of the library.
 * \code
 * int main(int argc, char* argv[]) {
 *
 *   FrontEnd arglib;
 *   // [...]
 *
 *   try {
 *     arglib.parse(argc, argv);
 *   } catch (ArgumentException e) {
 *     cout << e.what();
 *     return -1;
 *   }
 *
 *   // etc...
 * }
 * \endcode
 *
 * To find out, which options were supplied and find out about their parameters, just use methods
 * Arglib::FrontEnd::isOptionSet() (to see, whether an option was specified), Arglib::FrontEnd::isParameterSet()
 * (to see, whether a parameter was given to an option), Arglib::FrontEnd::getOptionParameter() (to get the value of
 * a parameter) and Arglib::FrontEnd::getRegularArguments() (to get all the other arguments that are not options).
 *
 * If getting the option parameter, you have to tell the library the class type of the parameter's value. This type
 * \b MUST match the type that is returned by the corresponding class derived from Arglib::Value. Bot don't panic -
 * in most cases, you will know what to expect to get from each type: Arglib::StringType returns std::strings,
 * Arglib::IntType returns ints, etc... - you get the idea.
 * \code
 * string inputFile = arglib.getOptionParameter<string>("file");
 * \endcode
 *
 * \subsection help_subsec Option help
 *
 * Arglib supports printing option help. This help lists all the defined options and their parameters and prints a
 * help string for each of the options. This help string can be supplied by calling the
 * Arglib::FrontEnd::setOptionHelp() function. To write out the help, use Arglib::FrontEnd::writeHelp() function.
 *
 * \section advanced_sec Advanced Usage
 *
 * In this section, you will find advanced concepts that you might find useful, but chance is you'll never need them.
 *
 * \subsection newtypes_subsec New Types
 *
 * Your options can use a variety of pre-defined Types (see Arglib::Type hierarchy), but it might happen that these
 * are not enough. Mainly because you might want to provide a specific parsing function for your type or because
 * you want to return some obscure value from the respective option parameter. In order to do this, you have to
 * create your own type that will derive from Arglib::Type.
 *
 * The type must have a destructor defined as well as following virtual methods:
 * \li Arglib::Value* Arglib::Type::fromString() const;
 * \li Arglib::Type* Arglib::Type::clone() const;
 *
 * The first method parses a string argument and constructs a Arglib::Value type that is then passed into the library
 * and can be saved. You can either use the pre-defined values or create your own value type as well.
 *
 * A value type only has to have a destructor and then a template specialization has to be created for the template
 * method ValueHandle::getValue(). This method is used to get value of a parameter. Remember what we told you in the
 * Basic Usage section about specifying the type of the parameter's value? That type is the type for which you
 * are writing a specialized method. Here's an example from the BoolValue class definition:
 * \code
 * template <>
 * bool ValueHandle::getValue<bool>();
 * \endcode
 * One last thing about value types: when you end up defining a specialization for a type that is already provided by
 * a class from the Arglib::Value hierarchy, it means that you should use that value class from the library.
 *
 * The second method clones the type. This is necessary to be able to copy the Arglib::Type by using its pointer only.
 *
 * If you want the parameter of your new type to appear nicely in the option help, you can provide a parameter name
 * with the method Arglib::Type::setParameterName()
 *
 */

