#include "IntegerTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>
#include <climits>

using namespace std;

void IntegerTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&IntegerTests::upperLimitTest, "Testing whether integer upper limit is correctly tested");
	testSet.addTest(&IntegerTests::lowerLimitTest, "Testing whether integer lower limit is correctly tested");
	testSet.addTest(&IntegerTests::unlimitedTest, "Testing whether unlimited integer is really unlimited");
	testSet.addTest(&IntegerTests::overflowTest, "Integer overflow must return MIN_INT or MAX_INT");
	testSet.addTest(&IntegerTests::correctTest, "Testing a set of correctly formed integers");
	testSet.addTest(&IntegerTests::malformedTest, "Testing refusal of malformed integers");
}

bool IntegerTests::upperLimitTest() {
	ArgList args1;
	args1.push("program").push("-i").push("0");
	ArgList args2;
	args2.push("program").push("-i").push("1");

	FrontEnd arglib;
	IntType intType = IntType();
	intType.setHighBound(0);
	arglib.addOption("i", OPTION_ALLOWED, intType, PARAM_REQUIRED);

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
	IntType intType = IntType();
	intType.setLowBound(0);
	arglib.addOption("i", OPTION_ALLOWED, intType, PARAM_REQUIRED);

	args1.dump(cout);
	args2.dump(cout);

	return
		Tests::parseMustThrow(arglib, args1) &&
		Tests::parseMustNotThrow(arglib, args2);
}

bool IntegerTests::unlimitedTest() {
	ArgList args;
	args.push("program").push("-i").push("-2147483648").push("-i").push("2147483647");

	args.dump(cout);

	FrontEnd arglib;
	arglib.addOption("i", OPTION_ALLOWED, IntType(), PARAM_REQUIRED);

	return
		Tests::parseMustNotThrow(arglib, args);
}

bool IntegerTests::overflowTest() {
	ArgList args;
	args.push("program").push("--max").push("123456789123456789");
	args.push("--min").push("-123456789123456789");

	args.dump(cout);

	FrontEnd arglib;
	arglib.addOption("min", OPTION_ALLOWED, IntType(), PARAM_REQUIRED);
	arglib.addOption("max", OPTION_ALLOWED, IntType(), PARAM_REQUIRED);

	return
		Tests::parseMustNotThrow(arglib, args) &&
		arglib.getOptionParameter<int>("max") == INT_MAX &&
		arglib.getOptionParameter<int>("min") == INT_MIN;
}

bool IntegerTests::correctTest() {
	ArgList args;
	args.push("program");
	args.push("-i").push("1");
	args.push("-i").push("+1");
	args.push("-i").push(" + 15");
	args.push("-i").push(" - 42");
	args.push("-i").push("   1456   ");

	args.dump(cout);

	FrontEnd arglib;
	arglib.addOption("i", OPTION_ALLOWED, IntType(), PARAM_REQUIRED);

	return
		Tests::parseMustNotThrow(arglib, args);
}

bool IntegerTests::malformedTest() {
	ArgList args;
	args.push("program");
	args.push("-i").push("1.4");

	args.dump(cout);

	FrontEnd arglib;
	arglib.addOption("i", OPTION_ALLOWED, IntType(), PARAM_REQUIRED);

	return
		Tests::parseMustThrow(arglib, args);
}

