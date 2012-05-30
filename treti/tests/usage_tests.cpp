#include "usage_tests.h"

#include "options.h"
#include <string>

using namespace options;
using namespace std;

namespace Tests {

bool UsageTests::TimeOutput::run() {
  option_parser parser;
  prepareTimeExample(parser);

  out() << parser;
  return true;    
}

bool UsageTests::ValueTest::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-f=%H:%m", "--portability", "-o", "output.txt" };
  dumpArguments(5, argv);

  ASSERT(parser.parse(5, const_cast<char**>(argv)));
  ASSERT_EQUALS(option_cast<string>(parser['f']), "%H:%m");
  ASSERT_EQUALS(option_cast<string>(parser['o']), "output.txt");
  ASSERT(parser["portability"]);

  return true;
}

bool UsageTests::SynonymTest::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-f=format", "--output", "myfile.txt" };
  dumpArguments(4, argv);

  ASSERT(parser.parse(4, const_cast<char**>(argv)));
  ASSERT_EQUALS(option_cast<string>(parser['f']), option_cast<string>(parser['F']));
  ASSERT_EQUALS(option_cast<string>(parser['f']), option_cast<string>(parser["format"]));
  ASSERT_EQUALS(option_cast<string>(parser["output"]), option_cast<string>(parser["Output"]));
  ASSERT_EQUALS(option_cast<string>(parser["output"]), option_cast<string>(parser['o']));

  return true;
}

bool UsageTests::ResetTest::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-f=format" };
  dumpArguments(2, argv);

  ASSERT(parser.parse(2, const_cast<char**>(argv)));

  const char* argv2[] = { "program", "--output", "myfile.txt" };
  dumpArguments(3, argv2);

  out() << "Trying to parse for the second time... If the test fails on parsing, it probably is not good." << endl;
  ASSERT(parser.parse(3, const_cast<char**>(argv2)));
  ASSERT_EQUALS(option_cast<string>(parser["output"]), "myfile.txt");
  // The values should probably be reset, so 'f' should not be defined
  ASSERT_FALSE(parser['f']);

  return true;
}

bool UsageTests::ArgumentsTest::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-f=format", "arg1", "arg2" };
  dumpArguments(4, argv);

  vector<string> args;

  ASSERT(parser.parse(4, const_cast<char**>(argv)));
  args = parser.arguments();
  ASSERT_EQUALS(args.size(), 2);
  ASSERT_EQUALS(args[0], "arg1");
  ASSERT_EQUALS(args[1], "arg2");

  return true;
}

bool UsageTests::ArgumentsTest2::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-f=format", "--", "arg1", "arg2" };
  dumpArguments(5, argv);

  vector<string> args;

  ASSERT(parser.parse(5, const_cast<char**>(argv)));
  args = parser.arguments();
  ASSERT_EQUALS(args.size(), 2);
  ASSERT_EQUALS(args[0], "arg1");
  ASSERT_EQUALS(args[1], "arg2");

  return true;
}

bool UsageTests::ValueOrSeparator::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-o", "--", "arg1", "arg2" };
  dumpArguments(5, argv);

  vector<string> args;

  ASSERT(parser.parse(5, const_cast<char**>(argv)));
  args = parser.arguments();
  ASSERT_EQUALS(args.size(), 2);
  ASSERT_EQUALS(args[0], "arg1");
  ASSERT_EQUALS(args[1], "arg2");
  ASSERT_EQUALS(option_cast<string>(parser['o']), "");

  return true;
}

bool UsageTests::OptionOrArgument::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-o", "myfile.txt", "arg" };
  dumpArguments(4, argv);

  vector<string> args;

  ASSERT(parser.parse(4, const_cast<char**>(argv)));
  args = parser.arguments();
  ASSERT_EQUALS(args.size(), 1);
  ASSERT_EQUALS(args[0], "arg");
  ASSERT_EQUALS(option_cast<string>(parser['o']), "myfile.txt");

  return true;
}

bool UsageTests::Nonexistent::run() {
  option_parser parser;
  prepareTimeExample(parser);

  const char* argv[] = { "program", "-o", "myfile.txt", "-f=%H:%m:%s" };
  dumpArguments(4, argv);

  ASSERT(parser.parse(4, const_cast<char**>(argv)));
  try {
    parser['w'];
  } catch (exception exc) {
    // Exception is unusual here, so throw it again to fail the test
    cerr << "This example threw an exception, which is inconsistent with the rest of the library, therefore fail" << endl;
    throw;
  }

  return true;
}

bool UsageTests::OwnRestriction::run() {
  class adams_restriction: public option_restriction<int> {
    public:
      bool accept(int value) const {
        if (value == 42) return true;
        return false;
      }

      option_restriction<int>* clone() const {
        return new adams_restriction();
      }
  };

  option_category cat;
  cat.add_options()
    << option("o", "option", "Just a test option", option_value<int>(adams_restriction()));

  const char* argv[] = { "program", "-o", "32" };
  dumpArguments(3, argv);

  option_parser parser(cat);
  ASSERT_FALSE(parser.parse(3, const_cast<char**>(argv)));

  const char* argv2[] = { "program", "-o", "42" };
  dumpArguments(3, argv2);

  option_parser parser2(cat);
  ASSERT(parser2.parse(3, const_cast<char**>(argv2)));
  ASSERT_EQUALS(option_cast<int>(parser2['o']), 42);

  return true;
}

void UsageTests::prepareTimeExample(options::option_parser& parser) {
  option_category gnu_opts("GNU options");

  gnu_opts.add_options()
    << option("fF", "format,Format", "Specify output format, possibly overriding the format specified"
              " in the environment variable TIME.", option_value<string>(string(""), REQUIRED))
    << option("p", "portability", "Use the portable output format")
    << option("oO", "output,Output", "Do not send the results to stderr, but overwrite the specified file.",
              option_value<string>(string(""), OPTIONAL))
    << option("a", "append", "(Used together with -o.) Do not overwrite, but append.")
    << option("v", "verbose", "Give very verbose output about all the program knows about.");

  option_category std_opts("GNU standard options");

  std_opts.add_options()
    << option("", "help", "Print a usage message on the standard output and exit immediately.")
    << option("V", "version", "Print version information on stadard output and exit successfully.");

  parser.add_category(gnu_opts);
  parser.add_category(std_opts);

  return;
}

}  // End namespace Tests

