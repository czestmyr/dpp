#ifndef OPTION_TESTS_CATEGORY_TESTS_H
#define OPTION_TESTS_CATEGORY_TESTS_H

#include "framework.h"
#include "options.h"

namespace Tests {

class CategoryTests: public TestGroup {
  public:
    CategoryTests(): TestGroup("option_category tests") {
      Init1::init(this);
      Init2::init(this);
      Init3::init(this);
    }

    DECLARE_TEST(Init1, "Checking sanity of default-constructed category")
    DECLARE_TEST(Init2, "Checking sanity of initialized category")
    DECLARE_TEST(Init3, "Trying formatted output of categories")

    static bool checkSanity(options::option_category& cat);
};

}  // End namespace Tests

#endif

