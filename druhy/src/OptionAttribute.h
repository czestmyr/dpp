#ifndef _ARGLIB_OPTION_ATTRIBUTE_H_
#define _ARGLIB_OPTION_ATTRIBUTE_H_

namespace Arglib {

/// Attribute of an option.
/// Defines whether the option is required or not
enum OptionAttribute {
	OPTION_REQUIRED, ///< Option is required
	OPTION_ALLOWED ///< Option is allowed but not required
};

} // End namespace Arglib

#endif

