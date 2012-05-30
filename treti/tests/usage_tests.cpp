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

void UsageTests::prepareTimeExample(options::option_parser& parser) {
  option_category gnu_opts("GNU options");

  gnu_opts.add_options()
    << option("f", "format", "Specify output format, possibly overriding the format specified"
              " in the environment variable TIME.", option_value<string>(string(""), REQUIRED))
    << option("p", "portability", "Use the portable output format")
    << option("o", "output", "Do not send the results to stderr, but overwrite the specified file.",
              option_value<string>(string(""), REQUIRED))
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

