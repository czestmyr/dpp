#ifndef _ARGLIB_PARAMETER_ATTRIBUTE_H_
#define _ARGLIB_PARAMETER_ATTRIBUTE_H_

namespace Arglib {

/// Attribute af an option parameter.
/// Defines whether the parameter is required, forbidden or allowed
enum ParameterAttribute {
	PARAM_REQUIRED, ///< Parameter is required
	PARAM_ALLOWED, ///< Parameter is allowed but not required
	PARAM_FORBIDDEN ///< Option does not have a parameter
};

} // End namespace Arglib

#endif

