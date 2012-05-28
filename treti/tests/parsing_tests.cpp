#include "parsing_tests.h"

using namespace options;

namespace Tests {

bool ParsingTests::CatOutput::run() {
  option_category cat("Testing category");
  prepareCategory(cat);
  out() << cat;

  return true;
}

bool ParsingTests::SimpleOk::run() {
  option_category cat;
  prepareCategory(cat);

  option_parser parser(cat);

  const char* argv[] = { "program", "-f", "hello_world.cpp" };
  dumpArguments(3, argv);
  ASSERT(parser.parse(3, const_cast<char**>(argv)));

  return true;
}

bool ParsingTests::SimpleErr::run() {
  option_category cat;
  prepareCategory(cat);

  option_parser parser(cat);

  const char* argv[] = { "program", "-i", "hello_world.cpp" };
  dumpArguments(3, argv);
  ASSERT_FALSE(parser.parse(3, const_cast<char**>(argv)));

  return true;
}

bool ParsingTests::StrangeName::run() {
  option_category cat;
  prepareCategory(cat);

  option_parser parser(cat);

  const char* argv[] = { "program", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/" };
  dumpArguments(2, argv);
  ASSERT(parser.parse(2, const_cast<char**>(argv)));

  return true;
}

void ParsingTests::prepareCategory(option_category& cat) {
  cat.add_options()
    << option("f", "file", "Some file to be parsed")
    << option("s", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/", "Strange option");
}

}  // End namespace Tests

