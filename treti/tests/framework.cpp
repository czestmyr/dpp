#include "framework.h"

#include <iostream>

using namespace std;

namespace Tests {

void Test::dumpOutput() {
  if (output.str().size() != 0) {
    string line;
    cout << TEST_TAB << "Output of std::cout: " << endl;
    cout << YELLOW_BEGIN;
    while (getline(output, line)) {
      cout << TEST_TAB << line << endl;
    }
    cout << COLOR_END;
  }

  output.str() = "";
  output.clear();
}

void Test::dumpErrorOutput() {
  if (errorOutput.str().size() != 0) {
    string line;
    cout << TEST_TAB << "Output of std::cerr: " << endl;
    cout << YELLOW_BEGIN;
    while (getline(errorOutput, line)) {
      cout << TEST_TAB << line << endl;
    }
    cout << COLOR_END;
  }

  errorOutput.str() = "";
  errorOutput.clear();
}

int TestGroup::runTests() {
  int numTestsOk = 0;

  cout << endl << TEST_SEP << "Running " << description << "... (" << (int)(tests.size()) << " tests)" << endl;
  for (unsigned int i = 0; i < tests.size(); i++) {
    cout << TEST_TAB << tests[i]->getDescription();
    bool success = false;

    tests[i]->redirectErr();

    try {
      success = tests[i]->run();
      if (success) {
        cout << "\r" << GREEN_BEGIN << "[ OK ]" << COLOR_END << endl;
        numTestsOk++;
      } else {
        cout << "\r" << RED_BEGIN << "[FAIL]" << COLOR_END << endl;
      }
    } catch (std::exception& exc) {
      cout << "\r" << RED_BEGIN << "[FAIL]" << COLOR_END << TEST_ENDL;
      cout << RED_BEGIN << exc.what() << COLOR_END << endl;
    }

    tests[i]->restoreErr();

    tests[i]->dumpOutput();
    tests[i]->dumpErrorOutput();
  }
  cout << TEST_TAB << "End of " << description << " ";

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

