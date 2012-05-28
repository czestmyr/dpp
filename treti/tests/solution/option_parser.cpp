#include "option_parser.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iterator>

namespace options {

// constants:
const int option_parser::PARSE_ERROR = -1;

const std::string option_parser::PARSE_ERROR_MESSAGE = "program options parse error: ";
const std::string option_parser::PARSE_ERROR_PROGRAM = "program";
const std::string option_parser::PARSE_ERROR_POINTER = "^";
const int option_parser::PARSE_ERROR_INDENT_SIZE = 4;
const char option_parser::PARSE_ERROR_INDENT = ' ';
const char option_parser::PARSE_OPTION_MARK = '-';
const char option_parser::PARSE_OPTION_VALUE_DELIMITER = '=';

const int option_parser::PARSE_STARTING_INDEX = 1;

//
// option_parser:
//

// create:
option_parser::option_parser()
	: categories_()
	, short_options_()
	, long_options_()
{}

option_parser::option_parser(option_category & category)
	: categories_()
	, short_options_()
	, long_options_()
{
	add_category(category);
}

option_parser::option_parser(option_category & category, int argc, char * argv[])
	: categories_()
	, short_options_()
	, long_options_()
{
	add_category(category);
	parse(argc, argv);
}

// manipulation:
void option_parser::add_category(option_category & category)
{
	categories_.push_back(category);
}

bool option_parser::parse(int argc, char * argv[])
{
	build_maps();

	int argi = PARSE_STARTING_INDEX;
	while (argi < argc) {

		switch (type(argv[argi])) {
			case ARGUMENT: {
				parse_arguments(argc, argv, argi);
				return check_required();
			}
			case SHORT_OPTION: {
				argi = parse_short_options(argc, argv, argi);
				if (argi == PARSE_ERROR) {
					return false;
				}
				break;
			}
			case LONG_OPTION: {
				argi = parse_long_option(argc, argv, argi);
				if (argi == PARSE_ERROR) {
					return false;
				}
				break;
			}
			case DELIMITER_OPTION: {
				parse_arguments(argc, argv, argi + 1);
				return check_required();
			}
			default: {
				// huh. out of enumeration?
				assert(false);
			}
		}

	}

	return check_required();
}

// access:
const option & option_parser::operator [](short_name_type name) const
{
	auto find_result = short_options_.find(name);

	if (find_result == short_options_.end()) {
		throw std::runtime_error("option is not presented in parser");
	}

	return *(find_result->second);
}

const option & option_parser::operator [](long_name_type name) const
{
	auto find_result = long_options_.find(name);
	
	if (find_result == long_options_.end()) {
		throw std::runtime_error("option is not presented in parser");
	}

	return *(find_result->second);
}

option_parser::arguments_type option_parser::arguments() const
{
	return arguments_;
}

// helpers:
void option_parser::build_maps()
{
	std::for_each(categories_.begin(), categories_.end(),
		[this](option_category & category) {
			build_maps(category);
		});
}

void option_parser::build_maps(option_category & category)
{
	std::for_each(category.begin(), category.end(),
		[this](option & operand) {
			build_maps(operand);
		});	
}

void option_parser::build_maps(option & operand)
{
	// store short names.
	for (auto name = operand.short_names_begin(); name != operand.short_names_end(); ++name) {
		if (short_options_.find(*name) != short_options_.end()) {
			throw std::runtime_error("duplicated short option");
		}

		short_options_.insert(std::make_pair(*name, &operand));
	}

	// store long names.
	for (auto name = operand.long_names_begin(); name != operand.long_names_end(); ++name) {
		if (long_options_.find(*name) != long_options_.end()) {
			throw std::runtime_error("duplicated long option");
		}

		long_options_.insert(std::make_pair(*name, &operand));
	}
}

bool option_parser::check_required() const
{
	for (auto it = categories_.begin(); it != categories_.end(); ++it) {
		if (!check_required(*it)) {
			return false;
		}
	}

	return true;
}

bool option_parser::check_required(const option_category & category) const
{
	for (auto it = category.begin(); it != category.end(); ++it) {
		if ((it->category() == REQUIRED) && !(*it)) {
			std::string message("required option missing ");
			if (it->short_names_size() != 0) {
				message += "-";
				message += *(it->short_names_begin());
			} else {
				message += "--";
				message += *(it->long_names_begin());
			}

			print_simple_error_header(message);
			return false;
		}
	}

	return true;
}

void option_parser::parse_arguments(int argc, char * argv[], int argi)
{
	std::copy(argv + argi, argv + argc, std::back_inserter(arguments_));
}

int option_parser::parse_short_options(int argc, char * argv[], int argi)
{
	std::string argument(argv[argi]);
		
	for (size_t i = 1; i < argument.size(); ++i) {
		auto option_iterator = short_options_.find(argument[i]);
		if (option_iterator == short_options_.end()) {
			print_error_header(argc, argv, argi, i, "uknown option");
			return PARSE_ERROR;
		}
			
		option_iterator->second->mark();
		if (!option_iterator->second->empty()) {
			return parse_option_value(argc, argv, argi, i + 1, option_iterator->second);
		}
	}

	return argi + 1;
}

int option_parser::parse_long_option(int argc, char * argv[], int argi)
{
	std::string argument(argv[argi] + 2);
	auto delimiter = argument.find(PARSE_OPTION_VALUE_DELIMITER);

	// argument has format --option=value.
	if (delimiter != std::string::npos) {
		std::string name = argument.substr(0, delimiter);
		std::string value = argument.substr(delimiter + 1);

		auto option_it = long_options_.find(name);
		if (option_it == long_options_.end()) {
			print_error_header(argc, argv, argi, 2, "uknown option");
			return PARSE_ERROR;
		}

		option_it->second->mark();
		if (option_it->second->size() == 0) {
			print_error_header(argc, argv, argi, 2, "option doesn't have value");
			return PARSE_ERROR;
		}

		if (!option_it->second->parse_value(value)) {
			print_error_header(argc, argv, argi, name.length() + 3, "failed to parse argument");
			return PARSE_ERROR;
		}

		return argi + 1;
	}

	// argument has format --option.
	auto option_it = long_options_.find(argument);
	if (option_it == long_options_.end()) {
		print_error_header(argc, argv, argi, 2, "uknown option");
		return PARSE_ERROR;
	}

	option_it->second->mark();
	if (!option_it->second->empty()) {
		return parse_option_value(argc, argv, argi, argument.size() + 2, option_it->second);
	}

	return argi + 1;
}

int option_parser::parse_option_value(int argc, char * argv[], int argi, int index, option * operand)
{
	std::string argument(argv[argi]);

	// parsing options of type --option=value (-o=value).
	if (index < static_cast<int>(argument.size())) {
		if (argument[index] != PARSE_OPTION_VALUE_DELIMITER) {
			print_error_header(argc, argv, argi, index, "option value expected");
			return PARSE_ERROR;
		}

		std::string option_value = argument.substr(index + 1);
		if (!operand->parse_value(option_value)) {
			print_error_header(argc,
				argv,
				argi,
				index + 1,
				"failed to parse value or restriction does not accept it");

			return PARSE_ERROR;
		}

		return argi + 1;
	}

	// parsing option of type --option value1 value2 ... (-o value1 value2 ...).
	++argi;
	size_type parsed = 0;
	const size_type max_values = operand->size();
	for (; argi < argc; ++argi, ++parsed) {

		// everything is already parsed.
		if (parsed == max_values) {
			break;
		}

		// we have another option or delimiter.
		if (type(argv[argi]) != ARGUMENT) {
			break;
		}

		// parse argument.
		if (!operand->parse_value(argv[argi])) {
			print_error_header(argc,
				argv,
				argi,
				0,
				"failed to parse value or restriction does not accept it");

			return PARSE_ERROR;
		}
	}

	if ((parsed == 0) && (operand->value_category() == REQUIRED)) {
		print_error_header(argc,
			argv,
			argi - 1,
			index,
			"option has required value");

			return PARSE_ERROR;
	}

	return argi;
}

// helpers:
void option_parser::print_simple_error_header(std::string message)
{
	std::cerr << PARSE_ERROR_MESSAGE << message << std::endl << std::endl;
}

void option_parser::print_error_header(int argc, char * argv[], int argi, int index, std::string message)
{
	print_simple_error_header(message);

	std::fill_n(std::ostream_iterator<char>(std::cerr), PARSE_ERROR_INDENT_SIZE, PARSE_ERROR_INDENT);
	print_error_command_line(argc, argv);

	size_type pointer_position = error_position(argv, argi, index);
	std::fill_n(std::ostream_iterator<char>(std::cerr),
		pointer_position + PARSE_ERROR_INDENT_SIZE + PARSE_ERROR_PROGRAM.size() + 1,
		PARSE_ERROR_INDENT);

	std::cerr << PARSE_ERROR_POINTER << std::endl;
}

void option_parser::print_error_command_line(int argc, char * argv[])
{
	std::cerr << PARSE_ERROR_PROGRAM;
	int argi = PARSE_STARTING_INDEX;
	for (; argi < argc; ++argi) {
		std::cerr << PARSE_ERROR_INDENT << argv[argi];
	}

	std::cerr << std::endl;
}

option_parser::size_type option_parser::error_position(char * argv[], int argi, int index)
{
	size_type result = 0;
	std::for_each(argv + PARSE_STARTING_INDEX, argv + argi,
		[&result](std::string argument) {
			result += argument.size() + 1;
		});

	return result + index;
}

option_parser::parse_type option_parser::type(std::string argument)
{
	assert(argument.size() != 0);

	if (argument[0] == PARSE_OPTION_MARK) {
		if (argument.size() == 1) {
			return ARGUMENT;
		}

		if (argument[1] == PARSE_OPTION_MARK) {
			if (argument.size() == 2) {
				return DELIMITER_OPTION;
			}

			return LONG_OPTION;
		}

		return SHORT_OPTION;
	}

	return ARGUMENT;
}

// paser output.
std::ostream & operator <<(std::ostream & stream, const option_parser & parser)
{
	std::for_each(parser.categories_.begin(), parser.categories_.end(),
		[&stream](const option_category & category) {
			stream << category;
		});

	return stream;
}

} // namespace options