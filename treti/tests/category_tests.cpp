#include "category_tests.h"

#include <iostream>

using namespace options;
using namespace std;

namespace Tests {

bool CategoryTests::Init1::run() {
  option_category cat;
  return checkSanity(cat);
}

bool CategoryTests::Init2::run() {
  option_category cat("Test options", "Options that should test this library");
  return checkSanity(cat);
}

bool CategoryTests::Init3::run() {
  option_category cat("Test options", "Options that should test this library");
  cout << endl << cat;
  return checkSanity(cat);
}

bool CategoryTests::checkSanity(option_category& cat) {
  const option_category& constCat = cat;

  ASSERT_EQUALS(cat.size(), 0);
  ASSERT_EQUALS_NOPRINT(cat.begin() + cat.size(), cat.end());
  ASSERT_EQUALS_NOPRINT(constCat.begin() + constCat.size(), constCat.end());

  return true;
}

}  // End namespace Tests

