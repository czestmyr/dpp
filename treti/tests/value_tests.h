#ifndef OPTION_TESTS_VALUE_TESTS_H
#define OPTION_TESTS_VALUE_TESTS_H

#include "framework.h"

namespace Tests {

class ValueTests: public TestGroup {
  public:
    ValueTests(): TestGroup("option_value tests") {
      ValueParsing::init(this);
      VectorParsing::init(this);
      SwapTest::init(this);
    }

    DECLARE_TEST(ValueParsing, "Trying to parse several values of standard types");
    DECLARE_TEST(VectorParsing, "Trying to parse a vector of standard types");
    DECLARE_TEST(SwapTest, "Testing swap method");
};

}  // End namespace Tests

#endif

