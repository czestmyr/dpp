#include "category_tests.h"
#include "options.h"

namespace Tests {

bool CategoryTests::Init1::run() {
  ASSERT_EQUALS(2, 3);
  return true;
}

}  // End namespace Tests

