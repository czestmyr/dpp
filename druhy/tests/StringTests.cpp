#include "StringTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>
#include <climits>

using namespace std;

void StringTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&StringTests::correctTest, "Testing whether string value is correctly read");
}

bool StringTests::correctTest() {
	ArgList args1;
	args1.push("program").push("-s").push("abcdefgh");
	ArgList args2;
	args2.push("program").push("-s").push("!@#$%^&*()_+");

	FrontEnd arglib;
	StringType stringType = StringType();
	arglib.addOption("s", REQUIRED, stringType);

	args1.dump(cout);
	args2.dump(cout);

	return
		Tests::parseMustNotThrow(arglib, args1) &&
		Tests::parseMustNotThrow(arglib, args2);
}
