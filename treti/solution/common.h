#ifndef OPTIONS_COMMON_H
#define OPTIONS_COMMON_H

#include <string>
#include <sstream>
#include <typeinfo>

/// \def NULLPTR
/// Macro representing null pointer. Since c++11 standard, there should be
/// nullptr keyword representing null pointer value. It's supported only
/// on msvc++10 and newer compilers. Otherwise macros value is literal 0.
/// By standard it is equivalent with
/// \code reinterpret_cast<void *>(0) \endcode
/// expression.
#if _MSC_VER >= 1600
#define NULLPTR nullptr
#else
#define NULLPTR 0
#endif

/// Macro disabling specialized copy functions.
/// Macro has to be presented inside private section.
#define NONCOPYABLE(name) \
	name(const name &); \
	name & operator =(const name &);

/// Macro disabling specialized move functions.
/// Macro has to be presented inside private section.
#define NONMOVABLE(name) \
	name(name &&); \
	name & operator =(name &&);

/// Macro disabling both copy/move semantics.
/// Macro has to be presented inside private section.
#define NONCOPYMOVABLE(name) \
	NONCOPYABLE(name) \
	NONMOVABLE(name)

/// Macro that states variable is unused and suppress compiler warnings.
#define UNUSED_VARIABLE(name) (void)name

namespace options {

// presence category:
/// Enumeration of possible option and its values categories.
enum presence_category {
	REQUIRED,	///< Option/value is required. If not presented, parsing fails.
	OPTIONAL	///< Option/value is optional. If not presented, default value is used.
};

// type casting:
/// Expception class indicating failure while casting.
struct bad_lexical_cast : public std::bad_cast {};

/// Casting one type to another type.
/**
 * Function uses std::stringstream to convert between different types.
 * If you want to use your own type as option value, you need to specialize
 * this function or define operator << and operator >> for std::stringstream
 * and your class.
 *
 * \param value input parameter.
 * \return Returns casted value of input parameter.
 */
template<typename To, typename From>
To lexical_cast(From value)
{
	std::stringstream stream;
	stream << value;
	To result;
	stream >> result;

	if (stream.fail()) {
		throw bad_lexical_cast();
	}

	return result;
}

/// Specialized functions for casting text to boolean.
/**
 * std::stringstream can't handle casting "false" to false or
 * "true" to true values. We need to overload/specialize
 * lexical_cast functions.
 */
template<>
bool lexical_cast(std::string value);

/// \see lexical_cast<bool>(std::string)
template<>
bool lexical_cast(const char * value);

} // namespace options

#endif // OPTIONS_COMMON_H
