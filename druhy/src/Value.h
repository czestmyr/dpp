#ifndef _ARGLIB_VALUE_H_
#define _ARGLIB_VALUE_H_

class Value {
	public:
		Value();

		int getInt();
		unsigned int getUnsignedInt();
		long getLong();
		unsigned long getUnsignedLong();
		float getFloat();
		double getDouble();

		template <class T> T* getPointer() {
			return (T*)ptr;
		}
	
		void setInt(int newValue);
		void setUnsignedInt(unsigned int newValue);
		void setLong(long newValue);
		void setUnsignedLong(unsigned long newValue);
		void setFloat(float newValue);
		void setDouble(double newValue);
		void setPointer(void* pointer);

		bool isValid() { return valid; }
	private:
		bool valid;

		union {
			int i;
			unsigned int ui;
			long l;
			unsigned long ul;
			float f;
			double d;
			void* ptr;
		};
};

#endif

