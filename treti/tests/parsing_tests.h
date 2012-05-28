#ifndef OPTION_TESTS_PARSING_TESTS_H
#define OPTION_TESTS_PARSING_TESTS_H

#include "framework.h"
#include "options.h"

namespace Tests {

class ParsingTests: public TestGroup {
  public:
    ParsingTests(): TestGroup("Parsing tests") {
      CatOutput::init(this);
      SimpleOk::init(this);
      ComplexOk::init(this);
      UnknownShort::init(this);
      UnknownLong::init(this);
      MalformedShort::init(this);
      CamoShort::init(this);
      MissingRequired::init(this);
      ProvidedOptional::init(this);
      OmitedOptional::init(this);
      DifferentType::init(this);
      StrangeName::init(this);
      DuplicateOption::init(this);
    }

    DECLARE_TEST(CatOutput, "Output of the category used in following tests");
    DECLARE_TEST(SimpleOk, "Simple parsing test");
    DECLARE_TEST(ComplexOk, "Complex parsing test");
    DECLARE_TEST(UnknownShort, "Unknown short option test");
    DECLARE_TEST(UnknownLong, "Unknown long option test");
    DECLARE_TEST(MalformedShort, "Malformed short option");
    DECLARE_TEST(CamoShort, "Camouflaged short option");
    DECLARE_TEST(MissingRequired, "Required option value missing");
    DECLARE_TEST(ProvidedOptional, "Optional option value is provided");
    DECLARE_TEST(OmitedOptional, "Optional option value is omited");
    DECLARE_TEST(DifferentType, "Parsing different type should be an error");
    DECLARE_TEST(StrangeName, "Testing option with a strange name");
    DECLARE_TEST(DuplicateOption, "Testing behavior for duplicate options (should probably be OK)");

    /// Helper function that dumps the arguments and asserts that argument parsing will be successful
    static void testOk(Test* test, int argc, const char* argv[]);

    /// Helper function that dumps the arguments and asserts that argument parsing will fail
    static void testFail(Test* test, int argc, const char* argv[]);

    /// Helper function that prepares the category used in testing
    static void prepareCategory(options::option_category& cat);
};

}  // End namespace Tests

#endif

