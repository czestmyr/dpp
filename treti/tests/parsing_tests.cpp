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
  const char* argv[] = { "program", "-r", "-f", "hello_world.cpp" };
  testOk(this, 4, argv);
  return true;
}

bool ParsingTests::ComplexOk::run() {
  const char* argv[] = { "program", "-r=3", "-s", "-r=-1234.5", "--file", "--", "Arg1", "Arg2" };
  testOk(this, 8, argv);
  return true;
}

bool ParsingTests::UnknownShort::run() {
  const char* argv[] = { "program", "-r", "-i", "hello_world.cpp" };
  testFail(this, 4, argv);
  return true;
}

bool ParsingTests::UnknownLong::run() {
  const char* argv[] = { "program", "-r", "--input", "hello_world.cpp" };
  testFail(this, 4, argv);
  return true;
}

bool ParsingTests::MalformedShort::run() {
  const char* argv[] = { "program", "-r", "-fs" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::CamoShort::run() {
  const char* argv[] = { "program", "--s" };
  testFail(this, 2, argv);
  return true;
}

bool ParsingTests::MissingRequired::run() {
  const char* argv[] = { "program", "-r", "--required_value" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::ProvidedOptional::run() {
  const char* argv[] = { "program", "-r", "-f", "myfile.txt" };
  testOk(this, 4, argv);
  return true;
}

bool ParsingTests::OmitedOptional::run() {
  const char* argv[] = { "program", "-r", "-f" };
  testOk(this, 3, argv);
  return true;
}

bool ParsingTests::RequiredOption::run() {
  const char* argv[] = { "program", "-f" };
  testFail(this, 2, argv);
  return true;
}

bool ParsingTests::DifferentType::run() {
  const char* argv[] = { "program", "-r", "ahoj" };
  testFail(this, 3, argv);
  return true;
}

bool ParsingTests::StrangeName::run() {
  const char* argv[] = { "program", "-r", "--!@#$%^&*()-_+[]{}\\|;:\"'<>.?/" };
  testOk(this, 3, argv);
  return true;
}

bool ParsingTests::DuplicateOption::run() {
  const char* argv[] = { "program", "-r", "-s", "-s" };
  testOk(this, 4, argv);
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
  option required = option("r", "", "Required option with an optional value", option_value<int>(5, OPTIONAL));
  required.category(REQUIRED);
  cat.add_options()
    << option("f", "file", "Some file to be parsed", option_value<string>("output.txt", OPTIONAL))
    << option("s", "!@#$%^&*()-_+[]{}\\|;:\"'<>.?/", "Strange option")
    << option("", "required_value", "Option with a required value", option_value<int>(0, REQUIRED))
    << required;
}

}  // End namespace Tests

