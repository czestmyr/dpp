#include "parsing_tests.h"

#include <string>

using namespace options;
using namespace std;

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

bool ParsingTests::ComplexOk::run() {
  const char* argv[] = { "program", "-r=3", "-s", "-r=-1234.5", "--file", "--", "Arg1", "Arg2" };
  testOk(this, 8, argv);
  return true;
}

bool ParsingTests::UnknownShort::run() {
  const char* argv[] = { "program", "-i", "hello_world.cpp" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::UnknownLong::run() {
  const char* argv[] = { "program", "--input", "hello_world.cpp" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::MalformedShort::run() {
  const char* argv[] = { "program", "-fs" };
  testFail(this, 2, argv);
  return true;
}

bool ParsingTests::CamoShort::run() {
  const char* argv[] = { "program", "--s" };
  testFail(this, 2, argv);
  return true;
}

bool ParsingTests::MissingRequired::run() {
  const char* argv[] = { "program", "-r" };
  testFail(this, 2, argv);
  return true;
}

bool ParsingTests::ProvidedOptional::run() {
  const char* argv[] = { "program", "-f", "myfile.txt" };
  testOk(this, 3, argv);
  return true;
}

bool ParsingTests::OmitedOptional::run() {
  const char* argv[] = { "program", "-f" };
  testOk(this, 2, argv);
  return true;
}

bool ParsingTests::DifferentType::run() {
  const char* argv[] = { "program", "-r", "ahoj" };
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
    << option("f", "file", "Some file to be parsed", option_value<string>("output.txt", OPTIONAL))
    << option("s", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/", "Strange option")
    << option("r", "", "Required option", option_value<int>(5, REQUIRED));
}

}  // End namespace Tests

