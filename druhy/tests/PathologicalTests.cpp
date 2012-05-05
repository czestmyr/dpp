#include "PathologicalTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void PathologicalTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&PathologicalTests::sameOptionTwiceTest, "Adding the same option twice should throw an exception");
	testSet.addTest(&PathologicalTests::sameSynonymTwiceTest, "Adding synonym with same name as existing option should throw an exception");
	testSet.addTest(&PathologicalTests::synonymSameAsOriginalTest, "Adding synonym with same name as original option should throw an exception");
	testSet.addTest(&PathologicalTests::twoCallsOfParseFunctionTest, "Options parsed in last call should be reset in the new call of parse");
	testSet.addTest(&PathologicalTests::twoCallsOfParseFunctionArgumentsTest, "Regular arguments parsed in last call should be reset in the new call of parse");
	testSet.addTest(&PathologicalTests::wrongOptionSynonymCallOrder, "Synonyms must not be defined before basic options");
}

bool PathologicalTests::sameOptionTwiceTest() {
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

bool PathologicalTests::sameSynonymTwiceTest() {
	FrontEnd arglib;
	arglib.addOption("i");
	arglib.addOption("j");

	try {
		arglib.addSynonym("i","j");
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool PathologicalTests::synonymSameAsOriginalTest() {
	FrontEnd arglib;
	arglib.addOption("i");

	try {
		arglib.addSynonym("i","i");
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool PathologicalTests::twoCallsOfParseFunctionTest() {
	// TODO: check if option parameters are reseted as well
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
bool PathologicalTests::twoCallsOfParseFunctionArgumentsTest() {
	// TODO: test if regular arguments are correctly read
	ArgList args1;
	args1.push("program").push("firstArgument").push("SecondArgument");
	
	ArgList args2;
	args2.push("program").push("Argument");

	FrontEnd arglib;
	
	bool noExceptionArgs1 = Tests::parseMustNotThrow(arglib, args1);
	vector<string> arguments1 = arglib.getRegularArguments();
	if(arguments1.size()!=2) {
		cout << "Arguments weren't read";
	}

	bool noExceptionArgs2 = Tests::parseMustNotThrow(arglib, args2);
	vector<string> arguments2 = arglib.getRegularArguments();
	if(arguments2.size()!=1) {
		cout << "Arguments weren't reseted";
	}

	return noExceptionArgs1 && noExceptionArgs2 &&
		arguments1.size()==2 &&
		arguments2.size()==1 ;
}
bool PathologicalTests::wrongOptionSynonymCallOrder(){
	FrontEnd arglib;

	try {
		arglib.addSynonym("i","j");
		arglib.addOption("i");
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}
