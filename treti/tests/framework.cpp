#include "framework.h"

#include <iostream>

using namespace std;

namespace Tests {

int TestGroup::runTests() {
  int numTestsOk = 0;

  cout << endl << "Running " << description << "..." << endl;
  for (unsigned int i = 0; i < tests.size(); i++) {
    cout << "       " << tests[i]->getDescription();
    if (tests[i]->run()) {
      cout << "\r" << GREEN_BEGIN << "[ OK ]" << COLOR_END << endl;
      numTestsOk++;
    } else {
      cout << "\r" << RED_BEGIN << "[FAIL]" << COLOR_END << endl;
    }
  }
  cout << "End of " << description << endl;

  return numTestsOk;
}

Tests::~Tests() {
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    delete testGroups[i];
  }
}

bool Tests::runTests() {
  int failed = 0;

  int numTotalTests = 0;
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    numTotalTests += testGroups[i]->getTestNum();
  }

  cout << "Testing Option library (" << numTotalTests << " tests)..." << endl;
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    int numGroupTests = testGroups[i]->getTestNum();
    int okGroupTests  = testGroups[i]->runTests();

    if (okGroupTests < numGroupTests) {
      cout << RED_BEGIN << "[" << okGroupTests << "/" << numGroupTests << "] tests OK" << COLOR_END << endl;
      failed += numGroupTests - okGroupTests;
    } else {
      cout << GREEN_BEGIN << "[" << okGroupTests << "/" << numGroupTests << "] tests OK" << COLOR_END << endl;
    }
  }

  if (failed != 0) {
    cout << endl << RED_BEGIN << failed << " test(s) failed!" << COLOR_END << endl;
  } else {
    cout << endl << GREEN_BEGIN << "All tests passed!" << COLOR_END << endl;
  }

  return failed == 0;
}

}  // End namespace Tests

