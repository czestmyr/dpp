#include "framework.h"
#include "category_tests.h"
#include "parsing_tests.h"
#include "options.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace options;

int main (int argc, char* argv[]) {
  Tests::Tests tests;

  // Parse the "verbose" option
  option_category cat("Test options");
  cat.add_options() << option("v", "verbose", "Whether the output should be verbose");

  option_parser parser(cat);
  parser.parse(argc, argv);

  bool verbose = parser["verbose"];

  // Append the test groups and run the tests
  tests.appendGroup(new Tests::CategoryTests());
  tests.appendGroup(new Tests::ParsingTests());

  return tests.runTests(verbose);
}

