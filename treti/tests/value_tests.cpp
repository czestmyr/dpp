#include "value_tests.h"

#include "options.h"
#include <string>
#include <vector>

using namespace options;
using namespace std;

namespace Tests {

bool ValueTests::ValueParsing::run() {
  option_value<int> intVal;
  option_value<float> floatVal;
  option_value<string> strVal;

  ASSERT(intVal.parse("42"));
  ASSERT(floatVal.parse("3.14"));
  ASSERT(strVal.parse("foo"));

  ASSERT_EQUALS(*(int*)intVal.value(), 42);
  ASSERT_EQUALS(*(float*)floatVal.value(), 3.14f);
  ASSERT_EQUALS(*(string*)strVal.value(), "foo");

  return true;
}

bool ValueTests::VectorParsing::run() {
  option_value< vector<int> > intVec;

  ASSERT(intVec.parse("0"));
  ASSERT(intVec.parse("1"));
  ASSERT(intVec.parse("2"));
  ASSERT(intVec.parse("3"));
  ASSERT(intVec.parse("4"));
  ASSERT(intVec.parse("5"));

  vector<int>& vec = *(vector<int>*)intVec.value();
  ASSERT_EQUALS(vec.size(), 6);
  for (int i = 0; i <= 5; ++i) {
    ASSERT_EQUALS(vec[i], i);
  }

  return true;
}

bool ValueTests::SwapTest::run() {
  option_value<int> val1;
  option_value<int> val2;

  ASSERT(val1.parse("1"));
  ASSERT(val2.parse("2"));

  val1.swap(val2);

  ASSERT_EQUALS(*(int*)val1.value(), 2);
  ASSERT_EQUALS(*(int*)val2.value(), 1);

  return true;
}

}  // End namespace Tests

