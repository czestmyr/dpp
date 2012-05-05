#include "EnumTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>
#include <climits>
#include <string>

using namespace std;

void EnumTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&EnumTests::emptyEnumTest, "Enum type with no entries should not allow parsing option of this type");
	testSet.addTest(&EnumTests::stringInEnumTest, "All entries defined in enum should be accepted as parameters");
	testSet.addTest(&EnumTests::multipleStringsInEnumTest, "All strings from vector in enum should be accepted as parameters");
}

bool EnumTests::emptyEnumTest(){
	ArgList args;
	args.push("program").push("-e").push("ANO");
	args.push("-f").push("NE");
	
	FrontEnd arglib;
	EnumType enumType = EnumType();
	arglib.addOption("e", OPTION_ALLOWED, enumType, PARAM_REQUIRED);
	arglib.addOption("f", OPTION_ALLOWED, enumType, PARAM_ALLOWED);

	args.dump(cout);
	
	return Tests::parseMustThrow(arglib, args);
}
bool EnumTests::stringInEnumTest(){
	ArgList args;
	args.push("program").push("-e").push("ANO");
	args.push("-f").push("NE");
	
	FrontEnd arglib;
	EnumType enumType = EnumType();
	enumType.addAllowedString("ANO");
	enumType.addAllowedString("NE");
	arglib.addOption("e", OPTION_ALLOWED, enumType, PARAM_REQUIRED);
	arglib.addOption("f", OPTION_ALLOWED, enumType, PARAM_ALLOWED);

	args.dump(cout);
	
	return Tests::parseMustNotThrow(arglib, args);
}
bool EnumTests::multipleStringsInEnumTest(){
	ArgList args;
	args.push("program").push("-e").push("ANO");
	args.push("-f").push("NE");
	args.push("-g").push("MOZNA");
	
	vector<string> allowed;
	allowed.push_back("ANO");
	allowed.push_back("NE");
	allowed.push_back("MOZNA");
	EnumType enumType = EnumType();

	enumType.addAllowedStrings(allowed);

	FrontEnd arglib;
	arglib.addOption("e", OPTION_ALLOWED, enumType, PARAM_REQUIRED);
	arglib.addOption("f", OPTION_ALLOWED, enumType, PARAM_ALLOWED);
	arglib.addOption("g", OPTION_ALLOWED, enumType, PARAM_REQUIRED);

	args.dump(cout);
	
	return Tests::parseMustNotThrow(arglib, args);
}
