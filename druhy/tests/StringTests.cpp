#include "StringTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>
#include <climits>
#include <string>

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

	bool withoutException = Tests::parseMustNotThrow(arglib, args1) &&
		Tests::parseMustNotThrow(arglib, args2);

	arglib.parse(args1.getCount(), args1.getArguments());
	string paramName = "s";
	string param1 = arglib.getOptionParameter<string>(paramName);
	bool isParam1OK = (param1 == "abcdefgh");
	if (!isParam1OK) {
		cout << "Param1: " << param1;
	}

	arglib.parse(args2.getCount(), args2.getArguments());
	string param2 = arglib.getOptionParameter<string>("s");
	bool isParam2OK = (param2 == "!@#$%^&*()_+");
	if (!isParam2OK) {
		cout << "Param2: " << param2;
	}

	return withoutException && isParam1OK && isParam2OK;
}
