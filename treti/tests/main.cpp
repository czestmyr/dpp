#include "options.h"
#include "framework.h"

#include <iostream>
#include <vector>

using namespace std;

int main (int arc, char* argv[]) {
  Tests::Tests tests;
  return tests.runTests();
}

