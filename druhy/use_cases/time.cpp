#include "Arglib.h"
#include "FormatType.h"
#include "FileType.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace Arglib;

int main(int argc, const char* argv[]) {
	FrontEnd arglib;

	FormatType formatType = FormatType();
	arglib.addOption("f", OPTION_ALLOWED, formatType, PARAM_REQUIRED);
	arglib.addSynonym("f","format");
	string formatHelp = "Specify output format, possibly overriding the format ";
	formatHelp+="specified in the environment variable TIME.";
	arglib.setOptionHelp("f", formatHelp);

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

	try {
		arglib.parse(argc, argv);
	} catch (ArgumentException e) {
		cerr << "time: " << e.what() << endl;
		return 1;
	}

	// Ask which options were defined and possibly ask arguments
	if (arglib.isOptionSet("help")) {
		cout << "time - time a simple command or give resource usage" << endl << endl;
		cout << "\tSynopsis:" << endl;
		cout << "\t\ttime [OPTIONS] command [ARGUMENT(s)]..." << endl << endl;
		arglib.writeHelp(cout);
		return 0;
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

	vector<string> args = arglib.getRegularArguments();
	if (args.size() == 0) {
		cerr << "No command specified, try --help for help" << endl;
		return -1;
	}
	cout << "Program got this arguments:";
	for( vector<string>::iterator it = args.begin(); it!=args.end();++it){
		cout<< " " << (*it);
	}
	cout << endl;
	return 0; 
}

