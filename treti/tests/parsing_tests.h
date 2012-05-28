#ifndef OPTION_TESTS_PARSING_TESTS_H
#define OPTION_TESTS_PARSING_TESTS_H

#include "framework.h"
#include "options.h"

namespace Tests {

class ParsingTests: public TestGroup {
  public:
    ParsingTests(): TestGroup("Parsing tests") {
      Simple::init(this);
    }

    DECLARE_TEST(Simple, "Simple parsing test");

    static void prepareCategory(options::option_category& cat);
};

}  // End namespace Tests

#endif

