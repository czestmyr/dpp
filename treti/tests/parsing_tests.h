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
    }

    DECLARE_TEST(CatOutput, "Output of the category used in following tests");
    DECLARE_TEST(SimpleOk, "Simple parsing test (should pass)");
    DECLARE_TEST(SimpleErr, "Simple parsing test (should NOT pass)");
    DECLARE_TEST(StrangeName, "Testing option with a strange name");

    static void prepareCategory(options::option_category& cat);
};

}  // End namespace Tests

#endif

