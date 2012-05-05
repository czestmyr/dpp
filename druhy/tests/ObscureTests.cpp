#include "ObscureTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void ObscureTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&ObscureTests::sameOptionTwiceTest, "Adding the same option twice should throw an exception");
	testSet.addTest(&ObscureTests::twoCallsOfParseFunctionTest, "Options parsed in last call should be reset in the new call of parse");
}

bool ObscureTests::sameOptionTwiceTest() {
	FrontEnd arglib;
	arglib.addOption("i");

	try {
		arglib.addOption("i");
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool ObscureTests::twoCallsOfParseFunctionTest() {
	// // should test if status is reset before second call of that function
	ArgList args1;
	args1.push("program").push("-t");
	
	ArgList args2;
	args2.push("program");

	FrontEnd arglib;
	StringType stringType = StringType();
	arglib.addOption("t", OPTION_ALLOWED, stringType, PARAM_ALLOWED);
	
	bool noExceptionArgs1 = Tests::parseMustNotThrow(arglib, args1);
	bool isOptionSetArgs1 = arglib.isOptionSet("t");
	if(!isOptionSetArgs1) {
		cout << "Option isn't set yet";
	}

	bool noExceptionArgs2 = Tests::parseMustNotThrow(arglib, args2);
	bool isOptionSetArgs2 = arglib.isOptionSet("t");
	if(isOptionSetArgs2) {
		cout << "Option is still set";
	}

	return noExceptionArgs1 && noExceptionArgs2 && isOptionSetArgs1 && !isOptionSetArgs2;
}
