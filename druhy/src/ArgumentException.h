#ifndef _ARGLIB_ARGUMENT_EXCEPTION_H_
#define _ARGLIB_ARGUMENT_EXCEPTION_H_

#include <exception>
#include <string>

namespace Arglib {

/// Exception that happened during parsing of the arguments.
class ArgumentException: public std::exception {
	public:
		ArgumentException(const std::string& exceptionMessage);
		virtual ~ArgumentException() throw();

		/// Prepends more information to the exception.
		/// @param moreInfo The string that will be prepended to the exception
		void prepend(const std::string& moreInfo);

		virtual const char* what() const throw();
	private:
		std::string message;
};

} // End namespace Arglib

#endif

