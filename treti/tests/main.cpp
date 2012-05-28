#include "options.h"
#include "framework.h"
#include "category_tests.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace options;

int main (int arc, char* argv[]) {
  Tests::Tests tests;

  tests.appendGroup(new Tests::CategoryTests());

  return tests.runTests();
}

