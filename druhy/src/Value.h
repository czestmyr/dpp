#ifndef _ARGLIB_VALUE_H_
#define _ARGLIB_VALUE_H_

namespace Arglib {

/// Class Value serves as a base class for other Value classes
/// and provides for them reference counting.
/// Refcountig doesn't work transparently automatically
/// and has be done manually using methods grab() and drop().
class Value {
	public:
		Value();
	private:
		/// Private copy constructor.
		/// This is private because values won't be copiable
		Value(const Value& other) {}
	public:
		/// Destructor is protected because Values are refcounted.
		/// Protected destructor ensures that Value instances cannot be created on stack
		virtual ~Value();
	
	public:
		/// Increases the reference counter.
		/// After calling this function, it is safe to assume that this instance won't
		/// be deleted until drop() is called.
		void grab();

		/// Decreases the reference counter.
		/// This means that we don't want to work with this instance anymore.
		/// If the refcount drops to zero, the object is destroyed.
		void drop();

	private:
		int refCount;///< Number of references pointing to this instance
};

} // End namespace Arglib

#endif

