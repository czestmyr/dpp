#include "IntegerTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>
#include <sstream>
#include <climits>

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
	IntegerType intType = IntegerType();
	intType.setHighBound(0);
	arglib.addOption("i", REQUIRED, intType);

	args1.dump(cout);
	args2.dump(cout);

	return
		Tests::parseMustNotThrow(arglib, args1) &&
		Tests::parseMustThrow(arglib, args2);
}

bool IntegerTests::lowerLimitTest() {
	ArgList args1;
	args1.push("program").push("-i=-1");
	ArgList args2;
	args2.push("program").push("-i").push("0");

	FrontEnd arglib;
	IntegerType intType = IntegerType();
	intType.setLowBound(0);
	arglib.addOption("i", REQUIRED, intType);

	args1.dump(cout);
	args2.dump(cout);

	return
		Tests::parseMustThrow(arglib, args1) &&
		Tests::parseMustNotThrow(arglib, args2);
}

bool IntegerTests::unlimitedTest() {
	stringstream strStreamMin;
	stringstream strStreamMax;
	strStreamMin << INT_MIN;
	strStreamMax << INT_MAX;
	ArgList args;
	args.push("program").push("-i").push(strStreamMin.str().c_str()).push("-i").push(strStreamMax.str().c_str());

	args.dump(cout);

	FrontEnd arglib;
	arglib.addOption("i", REQUIRED, IntegerType());

	return
		Tests::parseMustNotThrow(arglib, args);
}

bool IntegerTests::correctTest() {
	return false;
}

bool IntegerTests::malformedTest() {
	return false;
}

