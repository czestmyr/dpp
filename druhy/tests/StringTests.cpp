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
	testSet.addTest(&StringTests::correctTest, "Testing whether string value is correctly read in 2 following parses");
}

bool StringTests::correctTest() {
	string param1 = "abcdefgh";
	ArgList args1;
	args1.push("program").push("-s").push(param1.c_str());
	string param2 = "!@#$%^&*()_+";
	ArgList args2;
	args2.push("program").push("-s").push(param2.c_str());

	FrontEnd arglib;
	StringType stringType = StringType();
	arglib.addOption("s", OPTION_ALLOWED, stringType, PARAM_REQUIRED);

	args1.dump(cout);
	args2.dump(cout);

	bool firstParseWithoutException = Tests::parseMustNotThrow(arglib, args1);
	bool isParam1OK = (param1 == arglib.getOptionParameter<string>("s"));
	bool secondParseWithoutException = Tests::parseMustNotThrow(arglib, args2);
	bool isParam2OK = (param2 == arglib.getOptionParameter<string>("s"));

	return
		firstParseWithoutException &&
		secondParseWithoutException &&
		isParam1OK &&
		isParam2OK;
}
