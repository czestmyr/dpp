#include "Tests.h"

#include <iostream>
#include "TestCases.h"

using namespace std;

Tests& Tests::inst() {
	return instance;
}

Tests::Tests() {
	TestCases::addTestsTo(this);
}

Tests::~Tests() {
	for (int i = 0; i < tests.size(); ++i) {
		delete(tests[i]);
	}
}

void Tests::addTest(AbstractTest* test) {
	tests.push_back(test);
}

void Tests::runTests(){
	cout << "Running tests..." << endl;
	bool success = true;

	for (int i = 0; i < tests.size(); ++i) {
		cout << "Test " << (i+1) << "/" << tests.size() << ": ";
		cout << tests[i]->getDescription() << " ... ";
		if (tests[i]->runTest()) {
			cout << "OK." << endl;
		} else {
			cout << "FAIL!" << endl;
		}
	}
}

Tests Tests::instance = Tests();
