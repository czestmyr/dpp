#include "common.h"

#include <string>

namespace options {

template<>
bool lexical_cast(std::string value)
{
	static const int STRING_COMPARE_SUCCESS = 0;
	static const std::string trueValue = "true";
	static const std::string falseValue = "false";

	if (value.compare(trueValue) == STRING_COMPARE_SUCCESS) {
		return true;
	}

	if (value.compare(falseValue) == STRING_COMPARE_SUCCESS) {
		return false;
	}

	throw bad_lexical_cast();
}

template<>
bool lexical_cast(const char * value)
{
	return lexical_cast<bool>(std::string(value));
}

} // namespace options