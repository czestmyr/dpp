#include "IntegerTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>

using namespace std;

void IntegerTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&IntegerTests::upperLimitTest, "Testing whether integer upper limit is correctly tested");
	testSet.addTest(&IntegerTests::lowerLimitTest, "Testing whether integer lower limit is correctly tested");
	testSet.addTest(&IntegerTests::unlimitedTest, "Testing whether unlimited integer is really unlimited");
	testSet.addTest(&IntegerTests::correctTest, "Testing a set of correctly formed integers");
	testSet.addTest(&IntegerTests::malformedTest, "Testing refusal of malformed integers");
}

bool IntegerTests::upperLimitTest() {
	ArgList args1;
	args1.push("program").push("-i").push("0");
	ArgList args2;
	args2.push("program").push("-i").push("1");

	FrontEnd arglib;
	Integer* intType = new Integer();
	intType->setHighBound(0);
	arglib.addOption("i", REQUIRED, intType);

	
	try {
		arglib.parse(args1.getCount(), args1.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return false;
	}

	try {
		arglib.parse(args2.getCount(), args2.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool IntegerTests::lowerLimitTest() {
	return false;
}

bool IntegerTests::unlimitedTest() {
	return false;
}

bool IntegerTests::correctTest() {
	return false;
}

bool IntegerTests::malformedTest() {
	return false;
}

