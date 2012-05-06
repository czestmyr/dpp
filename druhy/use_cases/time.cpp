#include "Arglib.h"
#include "FormatType.h"
#include "FileType.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace Arglib;

int main(int argc, const char* argv[]) {
	//TODO: proc jsme vlastne pro Option neudelali vlastni tridu?
	FrontEnd arglib;

	FormatType formatType = FormatType();
	arglib.addOption("f", OPTION_ALLOWED, formatType, PARAM_REQUIRED);
	arglib.addSynonym("f","format");
	arglib.setOptionHelp("f", "Specify output format, possibly overriding the format specified in the environment variable TIME.");

	arglib.addOption("p");
	arglib.addSynonym("p","portability");
	arglib.setOptionHelp("p", "Use the portable output format.");

	FileType fileType = FileType();
	arglib.addOption("o", OPTION_ALLOWED, fileType, PARAM_REQUIRED);
	arglib.addSynonym("o","output");
	arglib.setOptionHelp("o", "Do not send the results to stderr, but overwrite the specified file.");

	arglib.addOption("a");
	arglib.addSynonym("a","append");
	arglib.setOptionHelp("a", "(Used together with -o.) Do not overwrite but append.");

	arglib.addOption("v");
	arglib.addSynonym("v","verbose");
	arglib.setOptionHelp("v", "Give very verbose output about all the program knows about.");

	arglib.addOption("help");
	arglib.setOptionHelp("help", "Print a usage message on standard output and exit successfully.");

	arglib.addOption("V");
	arglib.addSynonym("V","version");
	arglib.setOptionHelp("V", "Print version information on standard output, then exit successfully.");

	arglib.parse(argc, argv);
	if (arglib.isOptionSet("help")) {
		arglib.writeHelp(cout);
	}
	if (arglib.isOptionSet("f")) {
		string val = arglib.getOptionParameter<string>("f");
		cout << "Option: " << "f" << " has param: " << val << endl; 
	}
	if (arglib.isOptionSet("portability")) {
		cout << "Option: " << "portability" << " was set." << endl; 
	}
	if (arglib.isOptionSet("o")) {
		string val = arglib.getOptionParameter<string>("o");
		cout << "Option: " << "o" << " has param: " << val << endl; 
	}
	if (arglib.isOptionSet("a")) {
		cout << "Option: " << "a" << " was set." << endl; 
	}
	if (arglib.isOptionSet("v")) {
		cout << "Option: " << "v" << " was set." << endl; 
	}
	if (arglib.isOptionSet("V")) {
		cout << "Option: " << "V" << " was set." << endl; 
	}

	cout << "Program got this arguments:";
	vector<string> args = arglib.getRegularArguments();
	for( vector<string>::iterator it = args.begin(); it!=args.end();++it){
		cout<< " " << (*it);
	}
	cout << endl;
	return 0; 
}

