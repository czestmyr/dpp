#include "option.h"
#include "common.h"

#include <string>
#include <algorithm>
#include <cassert>

namespace options {

// create/copy/move:
option::option()
	: short_names_()
	, long_names_()
	, description_()
	, placeholder_(NULLPTR)
	, category_(OPTIONAL)
	, marked_(false)
{}

option::option(std::string shorts, std::string longs, std::string description)
	: short_names_()
	, long_names_()
	, description_()
	, placeholder_(NULLPTR)
	, category_(OPTIONAL)
	, marked_(false)
{
	parse_names(shorts, longs, description);
}

// special member functions:
option::option(const option & other)
	: short_names_(other.short_names_)
	, long_names_(other.long_names_)
	, description_(other.description_)
	, placeholder_(NULLPTR)
	, category_(other.category_)
	, marked_(other.marked_)
{
	if (other.placeholder_.get() != NULLPTR) {
		placeholder_.reset(other.placeholder_->clone());
	}
}

option::option(option && other)
	: short_names_(std::move(other.short_names_))
	, long_names_(std::move(other.long_names_))
	, description_(std::move(other.description_))
	, placeholder_(std::move(other.placeholder_))
	, category_(other.category_)
	, marked_(other.marked_)
{}

option & option::operator =(const option & other)
{
	option temp(other);
	swap(temp);
	return *this;
}

option & option::operator =(option && other)
{
	short_names_ = std::move(other.short_names_);
	long_names_ = std::move(other.long_names_);
	description_ = std::move(other.description_);
	placeholder_ = std::move(other.placeholder_);
	category_ = other.category_;
	marked_ = other.marked_;
	return *this;
}

// size:
option::size_type option::short_names_size() const
{
	return short_names_.size();
}

option::size_type option::long_names_size() const
{
	return long_names_.size();
}

bool option::empty() const
{
	return (placeholder_.get() == NULLPTR);
}

// iterators:
option::short_names_iterator option::short_names_begin()
{
	return short_names_.begin();
}

option::short_names_const_iterator option::short_names_begin() const
{
	return short_names_.begin();
}

option::short_names_iterator option::short_names_end()
{
	return short_names_.end();
}

option::short_names_const_iterator option::short_names_end() const
{
	return short_names_.end();
}

option::long_names_iterator option::long_names_begin()
{
	return long_names_.begin();
}

option::long_names_const_iterator option::long_names_begin() const
{
	return long_names_.begin();
}

option::long_names_iterator option::long_names_end()
{
	return long_names_.end();
}

option::long_names_const_iterator option::long_names_end() const
{
	return long_names_.end();
}


// manipulation:
void option::insert_short_name(short_name_type name)
{
	auto result = std::find(short_names_.begin(), short_names_.end(), name);
	if (result == short_names_.end()) {
		short_names_.push_back(name);
	}
}

void option::erase_short_name(short_name_type name)
{
	auto result = std::find(short_names_.begin(), short_names_.end(), name);
	if (result != short_names_.end()) {
		short_names_.erase(result);
	}
}

void option::insert_long_name(long_name_type name)
{
	auto result = std::find_if(long_names_.begin(), long_names_.end(),
		[&name](const std::string & operand) {
			return (operand.compare(name) == STRING_COMPARE_SUCCESS);
		});

	if (result == long_names_.end()) {
		long_names_.push_back(name);
	}
}

void option::erase_long_name(long_name_type name)
{
	auto result = std::find_if(long_names_.begin(), long_names_.end(),
		[&name](const std::string & operand) {
			return (operand.compare(name) == STRING_COMPARE_SUCCESS);
		});

	if (result != long_names_.end()) {
		long_names_.erase(result);
	}
}

// category:
presence_category option::category() const
{
	return category_;
}

void option::category(presence_category category)
{
	category_ = category;
}

presence_category option::value_category() const
{
	assert(placeholder_.get() != NULLPTR);
	return placeholder_->category();
}

// evaluation:
void option::mark()
{
	marked_ = true;
}

option::operator bool() const
{
	return marked_;
}

bool option::operator !() const
{
	return !marked_;
}

// values:
option::size_type option::size() const
{
	assert(!empty());
	return placeholder_->size();
}

bool option::parse_value(std::string argument)
{
	assert(!empty());
	return placeholder_->parse(argument);
}

// miscellaneous:
void option::swap(option & other) // noexcept
{
	std::swap(short_names_, other.short_names_);
	std::swap(long_names_, other.long_names_);
	std::swap(description_, other.description_);
	std::swap(placeholder_, other.placeholder_);
	std::swap(category_, other.category_);
	std::swap(marked_, other.marked_);
}

// helpers:
void option::parse_names(std::string shorts, std::string longs, std::string description)
{
	// parse short names.
	std::copy(shorts.begin(), shorts.end(), std::back_inserter(short_names_));

	// parse long names.
	std::string builder;
	std::for_each(longs.begin(), longs.end(),
		[&builder, this](char c) {
			if (c == LONG_NAME_DELIMITER) {
				long_names_.push_back(builder);
				builder.clear();
			} else {
				builder.push_back(c);
			}
		});

	if (!longs.empty()) {
		long_names_.push_back(builder);
	}
		
	// store description.
	description_ = description;
}

// option output:
std::ostream & operator <<(std::ostream & stream, const option & operand)
{
	static const char * OPTION_INDENT = "    ";
	static const char * OPTION_DESCRIPTION_INDENT = "        ";
	static const char * OPTION_SHORT_PREFIX = "-";
	static const char * OPTION_LONG_PREFIX = "--";
	static const char * OPTION_DELIMITER = ", ";
	static const char * OPTION_VALUE_BRACKET_LEFT = "[";
	static const char * OPTION_VALUE_BRACKET_RIGHT = "]";
	static const char * OPTION_VALUE_TEXT = "value";

	stream << OPTION_INDENT;

	// print short names.
	if (!operand.short_names_.empty()) {
		stream << OPTION_SHORT_PREFIX;
		std::copy(operand.short_names_.begin(),
			operand.short_names_.end(),
			std::ostream_iterator<option::short_name_type>(stream));
	}

	// print long names.
	if (!operand.long_names_.empty()) {
		if (!operand.short_names_.empty()) {
			stream << OPTION_DELIMITER;
		}
		stream << OPTION_LONG_PREFIX;
		stream << operand.long_names_.front();

		std::for_each(operand.long_names_.begin() + 1, operand.long_names_.end(),
			[&stream](const option::long_name_type name) {
				stream << OPTION_DELIMITER;
				stream << OPTION_LONG_PREFIX;
				stream << name;
			});
	}
	
	// print value info.
	if (!operand.empty()) {
		stream << ' ';
		stream << OPTION_VALUE_BRACKET_LEFT;
		stream << OPTION_VALUE_TEXT;
		stream << OPTION_VALUE_BRACKET_RIGHT;
	}

	// print description.
	if (!operand.description_.empty()) {
		stream << std::endl;
		stream << OPTION_DESCRIPTION_INDENT;
		stream << operand.description_;
	}

	// finish print.
	stream << std::endl << std::endl;
	return stream;
}

} // namespace options

namespace std {

template<>
void swap(options::option & lhs, options::option & rhs)
{
	lhs.swap(rhs);
}

} // namespace std
