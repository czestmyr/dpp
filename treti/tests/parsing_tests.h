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
      SimpleErr::init(this);
      StrangeName::init(this);
      DuplicateOption::init(this);
    }

    DECLARE_TEST(CatOutput, "Output of the category used in following tests");
    DECLARE_TEST(SimpleOk, "Simple parsing test (should be OK)");
    DECLARE_TEST(SimpleErr, "Simple parsing test (should output error)");
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

