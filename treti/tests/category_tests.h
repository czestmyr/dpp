#ifndef OPTION_TESTS_CATEGORY_TESTS_H
#define OPTION_TESTS_CATEGORY_TESTS_H

#include "framework.h"

namespace Tests {

class CategoryTests: public TestGroup {
  public:
    CategoryTests(): TestGroup("OptionCategory tests") {
      Init1::init(this);
    }

    DECLARE_TEST(Init1, "Initialization")
};

}  // End namespace Tests

#endif

