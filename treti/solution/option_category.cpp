#include "option_category.h"

#include <ostream>

namespace options {

//
// option_category::option_proxy
//

// operator () overloads:
option_category::option_proxy &
option_category::option_proxy::operator ()(std::string shorts, std::string longs, std::string description)
{
	parent_.options_.push_back(value_type(shorts, longs, description));
	return *this;
}

option_category::option_proxy &
option_category::option_proxy::operator ()(std::string shorts,
	std::string longs,
	std::string description,
	presence_category category)
{
	value_type value(shorts, longs, description);
	value.category(category);
	parent_.options_.push_back(value);
	return *this;
}

option_category::option_proxy &
option_category::option_proxy::operator ()(value_type value)
{
	parent_.options_.push_back(value);
	return *this;
}

// operator << overload:
option_category::option_proxy &
option_category::option_proxy::operator <<(value_type value)
{
	operator ()(value);
	return *this;
}

// friendly constructor:
option_category::option_proxy::option_proxy(option_category & parent)
	: parent_(parent)
{}

//
// option_category
//

// create:
option_category::option_category()
	: name_()
	, description_()
	, options_()
{}

option_category::option_category(std::string name, std::string description)
	: name_(name)
	, description_(description)
	, options_()
{}

// iterators:
option_category::iterator option_category::begin()
{
	return options_.begin();
}

option_category::const_iterator option_category::begin() const
{
	return options_.begin();
}

option_category::iterator option_category::end()
{
	return options_.end();
}

option_category::const_iterator option_category::end() const
{
	return options_.end();
}

// size:
option_category::size_type option_category::size() const
{
	return options_.size();
}

// manipulation:
option_category::option_proxy option_category::add_options()
{
	return option_proxy(*this);
}

//
// operator <<
//

std::ostream & operator <<(std::ostream & stream, const option_category & category)
{
	static const char * OPTION_CATEGORY_DELIMITER = ":";

	stream << category.name_ << OPTION_CATEGORY_DELIMITER << std::endl;
	if (!category.description_.empty()) {
		stream << category.description_ << std::endl;
	}

	std::for_each(category.options_.begin(), category.options_.end(),
		[&stream](const option & operand) {
			stream << operand;
		});

	return stream;
}

} // namespace options