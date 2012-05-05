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
	//testSet.addTest(&BoolTests::trailingCharacterTest, "Testing whether only values true or false are accepted");

}

bool BoolTests::trueFalseTest(){
	ArgList args;
	args.push("program").push("-t").push("true");
	args.push("--false").push("false");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	arglib.addOption("t", REQUIRED, boolType);
	arglib.addOption("false", ALLOWED, boolType);

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
	arglib.addOption("t", REQUIRED, boolType);

	args.dump(cout);
	
	return Tests::parseMustThrow(arglib, args);
}
bool BoolTests::noInputTest(){
	ArgList args;
	args.push("program").push("--false");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	string optionName = "false";
	arglib.addOption(optionName, ALLOWED, boolType);

	args.dump(cout);
	return Tests::parseMustNotThrow(arglib, args)&&
		Tests::getOptionValueMustThrow<bool>(arglib, "false"); 
}
bool BoolTests::trailingCharacterTest(){
	// TODO: implement
	return false;
}
