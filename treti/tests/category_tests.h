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
      Add1::init(this);
      Add2::init(this);
      Output::init(this);
    }

    DECLARE_TEST(Init1, "Checking sanity of default-constructed category")
    DECLARE_TEST(Init2, "Checking sanity of initialized category")
    DECLARE_TEST(Add1, "Checking sanity of category with options added using the operator() syntax")
    DECLARE_TEST(Add2, "Checking sanity of category with options added using the operator<< syntax")
    DECLARE_TEST(Output, "Trying formatted output of categories")

    static bool checkSanity(options::option_category& cat, size_t size = 0);
};

}  // End namespace Tests

#endif

