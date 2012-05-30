#ifndef OPTION_TESTS_OPTION_TESTS_H
#define OPTION_TESTS_OPTION_TESTS_H

#include "framework.h"
#include "options.h"

using namespace options;

namespace Tests {

class OptionTests: public TestGroup {
  public:
    OptionTests(): TestGroup("option tests") {
      EmptyOption::init(this);
      ShortNames::init(this);
      LongNames::init(this);
      Mark::init(this);
      OutputTest::init(this);
    }

    DECLARE_TEST(EmptyOption, "Testing integrity of an empty option");
    DECLARE_TEST(ShortNames, "Trying to add and remove a few short names for the option");
    DECLARE_TEST(LongNames, "Trying to add and remove a few long names for the option");
    DECLARE_TEST(Mark, "Testing the mark() function and boolean operators() of options");
    DECLARE_TEST(OutputTest, "Testing output of an option");

    static void checkOptionIntegrity(option& opt);
};

}  // End namespace Tests

#endif

