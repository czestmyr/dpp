#include <iostream>

#include "options.h"

int main(int argc, char * argv[])
{
	static const int SUCCCESS = 0;
	static const int ERROR = -1;

	using namespace options;

	// define enumerations.
	enumeration<std::string> answers;
	answers << "yes"
		<< "no"
		<< "maybe";

	// general options category.
	option_category general("Testing options", "Options used to test library features.");
	general.add_options()
		("a", "aa", "1st testing option with boolean value.", option_value<bool>(true, REQUIRED))
		(
			"b",
			"bb",
			"2nd testing option is list with possible words yes/no/maybe.",
			option_value<std::vector<std::string>>(answers)
		)
		("zZ", "zz", "the last option is required", REQUIRED);
		
	// standard options category.
	option_category standard("Standard options");
	standard.add_options()
		("v", "version", "prints program version.")
		("h", "help", "prints program help.");

	// input options category.
	option_category input("Input options", "Controlling all input data.");
	input.add_options()
		("iI", "input,input-files", "list of input files.", option_value<std::vector<std::string>>());

	// parse command line.
	options::option_parser cmd_parser;
	cmd_parser.add_category(general);
	cmd_parser.add_category(standard);
	cmd_parser.add_category(input);

	if ((argc < 2) || !cmd_parser.parse(argc, argv)) {
		std::cerr << cmd_parser;
		return ERROR;
	}

	// access results.
	if (cmd_parser["help"]) {
		std::cout << cmd_parser;
		return SUCCCESS;
	}

	if (cmd_parser["aa"]) {
		std::cout << "aa option presented with value: " << option_cast<bool>(cmd_parser["aa"]) << std::endl;
	}

	if (cmd_parser["bb"]) {
		std::vector<std::string> values = option_cast<std::vector<std::string>>(cmd_parser["bb"]);
		std::cout << "bb option presented with values: ";
		std::for_each(values.begin(), values.end(),
			[](std::string value) {
				std::cout << value << ' ';
			});

		std::cout << std::endl;
	}

	if (cmd_parser["version"]) {
		std::cout << "heh, version is ... early" << std::endl;
	}

	if (cmd_parser['i']) {
		std::vector<std::string> values = option_cast<std::vector<std::string>>(cmd_parser['i']);
		std::cout << "include files list: ";
		std::for_each(values.begin(), values.end(),
			[](std::string value) {
				std::cout << value << ' ';
			});

		std::cout << std::endl;
	}

	return 0;
}