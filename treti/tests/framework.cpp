#include "framework.h"

#include <iostream>
#include <cstring>

using namespace std;

namespace Tests {

void Test::dumpArguments(int argc, const char* argv[]) {
  for (int i = 0; i < argc; ++i) {
    // If the option contains backspaces, output it with quotes
    if (strchr(argv[i], ' ')) {
      out() << "\"" << argv[i] << "\" ";
    } else {
      out() << argv[i] << " ";
    }
  }
  out() << endl;
}

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

int TestGroup::runTests(bool verbose) {
  // Print the test gruop header
  cout << endl << TEST_SEP << "Running " << description << "... (" << (int)(tests.size()) << " tests)" << endl;

  // Run all tests in this category and calculate number of successes
  int numTestsOk = 0;
  for (unsigned int i = 0; i < tests.size(); i++) {
    cout << TEST_TAB << tests[i]->getDescription();

    tests[i]->redirectErr();

    // Run test and catch any exceptions
    bool success = false;
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

    // If the user wanted, print the standart output and error output
    if (verbose) {
      tests[i]->dumpOutput();
      tests[i]->dumpErrorOutput();
    }
  }
  cout << TEST_TAB << "End of " << description << " ";

  return numTestsOk;
}

Tests::~Tests() {
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    delete testGroups[i];
  }
}

bool Tests::runTests(bool verbose) {
  // Calculate the total number of tests
  int numTotalTests = 0;
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    numTotalTests += testGroups[i]->getTestNum();
  }

  // Print the header
  cout << "Testing Option library (" << numTotalTests << " tests)..." << endl;
  if (!verbose) {
    cout << "For verbose tests add option -v or --verbose" << endl;
  }

  // Run all test groups and count number of failed tests
  int failed = 0;
  for (unsigned int i = 0; i < testGroups.size(); ++i) {
    int numGroupTests = testGroups[i]->getTestNum();
    int okGroupTests  = testGroups[i]->runTests(verbose);

    if (okGroupTests < numGroupTests) {
      cout << RED_BEGIN << "[" << okGroupTests << "/" << numGroupTests << "] tests OK" << COLOR_END << endl;
      failed += numGroupTests - okGroupTests;
    } else {
      cout << GREEN_BEGIN << "[" << okGroupTests << "/" << numGroupTests << "] tests OK" << COLOR_END << endl;
    }
  }

  // Print how many tests have failed
  if (failed != 0) {
    cout << endl << RED_BEGIN << failed << " test(s) failed!" << COLOR_END << endl;
    if (!verbose) {
      cout << RED_BEGIN << "You can re-run the tests with option \"-v\" to see more details" << COLOR_END << endl;
    }
  } else {
    cout << endl << GREEN_BEGIN << "All tests passed!" << COLOR_END << endl;
  }

  return failed == 0;
}

}  // End namespace Tests

