#include "Arglib.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace Arglib;

int main(int argc, const char* argv[]) {
	//TODO: proc jsme vlastne pro Option neudelali vlastni tridu?
	FrontEnd arglib;

	arglib.addOption("a");
	arglib.addSynonym("a","all");
	arglib.setOptionHelp("a", "do not ignore entries starting with .");
	
	StringType sizeType = StringType();
	sizeType.setParameterName("SIZE");
	arglib.addOption("block-size", OPTION_ALLOWED, sizeType, PARAM_REQUIRED);
	arglib.setOptionHelp("block-size", "scale sizes by SIZE before printing them.  E.g., `--block-size=M' prints sizes in units of 1,048,576 bytes.   See  SIZE  format below.");

	IntType widthType = IntType();
	widthType.setParameterName("COLS");
	widthType.setLowBound(0);
	arglib.addOption("w", OPTION_ALLOWED, widthType, PARAM_REQUIRED);
	arglib.addSynonym("w","width");
	arglib.setOptionHelp("w", "assume screen width instead of current value");


	arglib.addOption("d");
	arglib.addSynonym("d","directory");
	arglib.setOptionHelp("d", "list directory entries instead of contents, and do not dereference symbolic links");

	arglib.addOption("help");
	arglib.setOptionHelp("help", "display this help and exit");

	arglib.addOption("version");
	arglib.setOptionHelp("version", "output version information and exit");


	arglib.parse(argc, argv);

	// Ask which options were defined and possibly ask arguments
	if (arglib.isOptionSet("help")) {
		arglib.writeHelp(cout);
	}
	if (arglib.isOptionSet("block-size")) {
		if (arglib.isOptionParameterSet("block-size")) {
			int val = arglib.getOptionParameter<int>("block-size");
			cout << "Option: " << "block-size" << " has param: " << val << endl; 
		}
	}
	if (arglib.isOptionSet("w")) {
		if (arglib.isOptionParameterSet("w")) {
			int val = arglib.getOptionParameter<int>("w");
			cout << "Option: " << "w" << " has param: " << val << endl; 
		}
	}
	if (arglib.isOptionSet("a")) {
		cout << "Option: " << "a" << " was set." << endl; 
	}
	if (arglib.isOptionSet("d")) {
		cout << "Option: " << "d" << " was set." << endl; 
	}
	if (arglib.isOptionSet("version")) {
		cout << "Option: " << "version" << " was set." << endl; 
	}

	cout << "Program got this arguments:";
	vector<string> args = arglib.getRegularArguments();
	for( vector<string>::iterator it = args.begin(); it!=args.end();++it){
		cout<< " " << (*it);
	}
	cout << endl;
	return 0; 
}

