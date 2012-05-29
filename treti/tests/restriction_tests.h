#ifndef OPTION_TESTS_RESTRICTION_TESTS_H
#define OPTION_TESTS_RESTRICTION_TESTS_H

#include "framework.h"

namespace Tests {

class RestrictionTests: public TestGroup {
  public:
    RestrictionTests(): TestGroup("option_restriction tests") {
      LowerPositive::init(this);
      LowerNegative::init(this);
      UpperPositive::init(this);
      UpperNegative::init(this);
      RangePositive::init(this);
      RangeNegative::init(this);
      Any::init(this);
      EnumPositive::init(this);
      EnumNegative::init(this);
    }

    DECLARE_TEST(LowerPositive, "Testing acceptance of lower bound in lower_bound restriction");
    DECLARE_TEST(LowerNegative, "Testing refusal of lower bound minus one in lower_bound restriction");
    DECLARE_TEST(UpperPositive, "Testing acceptance of upper bound in upper_bound restriction");
    DECLARE_TEST(UpperNegative, "Testing refusal of upper bound plus one in upper_bound restriction");
    DECLARE_TEST(RangePositive, "Testing acceptance of limit values in range restriction");
    DECLARE_TEST(RangeNegative, "Testing refusal of values one-beyond the limit values in range restriction");
    DECLARE_TEST(Any, "Testing whether the any restriction really accepts everything");
    DECLARE_TEST(EnumPositive, "Testing whether all values from an enumeration are accepted");
    DECLARE_TEST(EnumNegative, "Testing whether values outside of an enumeration are rejected");
};

}  // End namespace Tests

#endif

