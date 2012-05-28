#include "parsing_tests.h"

using namespace options;

namespace Tests {

bool ParsingTests::Simple::run() {
  option_category cat;
  prepareCategory(cat);

  option_parser parser(cat);

  const char* argv[] = {
    "program",
    "-i",
    "hello_world.cpp",
  };
  ASSERT(parser.parse(2, const_cast<char**>(argv)));

  return true;
}

void ParsingTests::prepareCategory(option_category& cat) {
  cat.add_options()
    << option("f", "file", "Some file to be parsed");
}

}  // End namespace Tests

