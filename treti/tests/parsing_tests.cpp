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
  const char* argv[] = { "program", "-f", "hello_world.cpp" };
  testOk(this, 3, argv);
  return true;
}

bool ParsingTests::SimpleErr::run() {
  const char* argv[] = { "program", "-i", "hello_world.cpp" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::StrangeName::run() {
  const char* argv[] = { "program", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/" };
  testOk(this, 2, argv);
  return true;
}

bool ParsingTests::DuplicateOption::run() {
  const char* argv[] = { "program", "-s", "-s" };
  testOk(this, 3, argv);
  return true;
}

void ParsingTests::testOk(Test* test, int argc, const char* argv[]) {
  option_category cat;
  prepareCategory(cat);
  option_parser parser(cat);

  test->dumpArguments(argc, argv);
  ASSERT(parser.parse(argc, const_cast<char**>(argv)));
}

void ParsingTests::testFail(Test* test, int argc, const char* argv[]) {
  option_category cat;
  prepareCategory(cat);
  option_parser parser(cat);

  test->dumpArguments(argc, argv);
  ASSERT_FALSE(parser.parse(argc, const_cast<char**>(argv)));
}

void ParsingTests::prepareCategory(option_category& cat) {
  cat.add_options()
    << option("f", "file", "Some file to be parsed")
    << option("s", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/", "Strange option");
}

}  // End namespace Tests

