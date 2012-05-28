#include "options.h"
#include "framework.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace options;

int main (int arc, char* argv[]) {
  option_category blah;

  Tests::Tests tests;
  return tests.runTests();
}

