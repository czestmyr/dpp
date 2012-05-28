#include "framework.h"
#include "category_tests.h"
#include "parsing_tests.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main (int arc, char* argv[]) {
  Tests::Tests tests;

  tests.appendGroup(new Tests::CategoryTests());
  tests.appendGroup(new Tests::ParsingTests());

  return tests.runTests();
}

