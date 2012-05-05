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
	testSet.addTest(&BoolTests::badInputTest, "Testing whether bad boolean inputs arent parsed");
	testSet.addTest(&BoolTests::trailingCharacterTest, "Testing whether only values true or false are accepted");

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
	args.push("program").push("-t").push("ahoj");
	args.push("--false");
	
	FrontEnd arglib;
	BoolType boolType = BoolType();
	arglib.addOption("t", REQUIRED, boolType);
	arglib.addOption("false", ALLOWED, boolType);

	args.dump(cout);
	
	return Tests::parseMustThrow(arglib, args);//&&
		//arglib.getOptionParameter<bool>("t") == true &&
		//arglib.getOptionParameter<bool>("false") == false;
}
bool BoolTests::trailingCharacterTest(){
	// TODO: implement
	return false;
}
