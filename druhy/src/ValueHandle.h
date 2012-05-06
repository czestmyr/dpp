#ifndef _ARGLIB_VALUE_HANDLE_H_
#define _ARGLIB_VALUE_HANDLE_H_

#include <cstring>
#include "Value.h"

namespace Arglib {

class ValueHandle {
	public:
		/// Konstructs new instance of the handle and set handled Value to newValue.
		/// @param newValue Value to be stored in this instance of ValueHandle.
		///	Default Value is NULL to reprezent no Value.
		ValueHandle(Value* newValue = NULL);

		/// Copy constructor ensures correct behavior when using this type in standard collection. 
		/// @param other Reference to ValueHandle which has to be copied.
		ValueHandle(const ValueHandle& other);

		/// Virtual destructor ensures proper destruction of the Value handled by this instance.
		/// 
		~ValueHandle();

		/// Assign operator ensures correct behavior when using this type in standard collection. 
		/// @param other Reference to ValueHandle which has to be assigned to this instance.
		ValueHandle& operator=(const ValueHandle& other);

		/// Change argument value holded by this handle to new One.
		/// Properly dealocates the old value.
		/// @param newValue New argument value to be hold by this handle.
		void setValue(Value* newValue);

		/// Defines method to access and cast the value to proper type. TODO: rewrite for better text 
		/// T Template parameter type to which the handled value shuuld be stored.
		/// Must be specialized for Type derived from class Value and stored in this instance. 
		template <class T>
		T getValue();
		
		/// Checks if the value handled by this instance is not defined.
		/// return If the value is not defined.
		bool isEmpty();
	private:
		Value* valuePtr;/// Pointer to value of type derived from Value
};

} // End namespace Arglib

#endif

