#include "BoolTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>
#include <climits>
#include <string>

using namespace std;

void BoolTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&BoolTests::trueFalseTest, "Testing whether boolean values true and false are correctly handled");
	testSet.addTest(&BoolTests::badInputTest, "Testing whether bad boolean inputs aren't parsed");
	testSet.addTest(&BoolTests::noInputTest, "Empty boolean argument can't be queried");

}

bool BoolTests::trueFalseTest(){
	ArgList args;
	args.push("program").push("-t").push("true");
	args.push("--false").push("false");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	arglib.addOption("t", OPTION_ALLOWED, boolType, PARAM_REQUIRED);
	arglib.addOption("false", OPTION_ALLOWED, boolType, PARAM_ALLOWED);

	args.dump(cout);
	
	return Tests::parseMustNotThrow(arglib, args)&&
		arglib.getOptionParameter<bool>("t") == true &&
		arglib.getOptionParameter<bool>("false") == false;

}

bool BoolTests::badInputTest(){
	ArgList args;
	args.push("program").push("-t").push("abcd");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	arglib.addOption("t", OPTION_ALLOWED, boolType, PARAM_REQUIRED);

	args.dump(cout);
	
	return Tests::parseMustThrow(arglib, args);
}

bool BoolTests::noInputTest(){
	ArgList args;
	args.push("program").push("--false");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	string optionName = "false";
	arglib.addOption(optionName, OPTION_ALLOWED, boolType, PARAM_ALLOWED);

	args.dump(cout);
	return Tests::parseMustNotThrow(arglib, args)&&
		Tests::getOptionValueMustThrow<bool>(arglib, "false"); 
}

