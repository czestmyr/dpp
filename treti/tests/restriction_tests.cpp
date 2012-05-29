#include "restriction_tests.h"
#include "options.h"

#include <climits>
#include <cstdlib>

// Number of tries in various restriction tests
#define BATCH_SIZE 10000

using namespace options;

namespace Tests {

bool RestrictionTests::LowerPositive::run() {
  lower_bound<int> lower(0);
  ASSERT(lower.accept(0));

  // Also test cloning
  option_restriction<int>* lower_clone = lower.clone();
  ASSERT(lower_clone->accept(0));
  delete lower_clone;
  return true;
}

bool RestrictionTests::LowerNegative::run() {
  lower_bound<int> lower(0);
  ASSERT_FALSE(lower.accept(-1));

  // Also test cloning
  option_restriction<int>* lower_clone = lower.clone();
  ASSERT_FALSE(lower_clone->accept(-1));
  delete lower_clone;
  return true;
}

bool RestrictionTests::UpperPositive::run() {
  upper_bound<int> upper(0);
  ASSERT(upper.accept(0));

  // Also test cloning
  option_restriction<int>* upper_clone = upper.clone();
  ASSERT(upper_clone->accept(0));
  delete upper_clone;
  return true;
}

bool RestrictionTests::UpperNegative::run() {
  upper_bound<int> upper(0);
  ASSERT_FALSE(upper.accept(1));

  // Also test cloning
  option_restriction<int>* upper_clone = upper.clone();
  ASSERT_FALSE(upper_clone->accept(1));
  delete upper_clone;
  return true;
}

bool RestrictionTests::RangePositive::run() {
  range<int> rng(0,10);
  ASSERT(rng.accept(0));
  ASSERT(rng.accept(10));

  // Also test cloning
  option_restriction<int>* rng_clone = rng.clone();
  ASSERT(rng_clone->accept(0));
  ASSERT(rng_clone->accept(10));
  delete rng_clone;
  return true;
}

bool RestrictionTests::RangeNegative::run() {
  range<int> rng(0,10);
  ASSERT_FALSE(rng.accept(-1));
  ASSERT_FALSE(rng.accept(11));

  // Also test cloning
  option_restriction<int>* rng_clone = rng.clone();
  ASSERT_FALSE(rng_clone->accept(-1));
  ASSERT_FALSE(rng_clone->accept(11));
  delete rng_clone;
  return true;
}

bool RestrictionTests::Any::run() {
  any<int> any_restrict;
  option_restriction<int>* any_clone = any_restrict.clone();

  // O.K. I don't really test every int, but several random values should be enough
  srand(42);
  for (int i = 0; i < BATCH_SIZE; ++i) {
    int n = rand();
    ASSERT(any_restrict.accept(n));
    ASSERT(any_clone->accept(n));
  }

  delete any_clone;
  return true;
}

bool RestrictionTests::EnumPositive::run() {
  // First, initialize the restriction
  enumeration<int> enum_restrict;
  srand(42);
  for (int i = 0; i < BATCH_SIZE; ++i) {
    int n = rand();
    enum_restrict.add(n);
  }
  option_restriction<int>* enum_clone = enum_restrict.clone();

  // Test all the values now
  srand(42);
  for (int i = 0; i < BATCH_SIZE; ++i) {
    int n = rand();
    ASSERT(enum_restrict.accept(n));
    ASSERT(enum_clone->accept(n));
  }

  delete enum_clone;
  return true;
}

bool RestrictionTests::EnumNegative::run() {
  // Initialize the enum restriction
  enumeration<int> enum_restrict;
  for (int i = 0; i < 10; ++i) {
    enum_restrict.add(i);
  }
  option_restriction<int>* enum_clone = enum_restrict.clone();

  // Test a few numbers from outside the restriction
  for (int i = -100; i < 0; ++i) {
    ASSERT_FALSE(enum_restrict.accept(i));
    ASSERT_FALSE(enum_clone->accept(i));
  }
  for (int i = 10; i < 10; ++i) {
    ASSERT_FALSE(enum_restrict.accept(i));
    ASSERT_FALSE(enum_clone->accept(i));
  }

  delete enum_clone;
  return true;
}

}  // End namespace Tests

