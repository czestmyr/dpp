#ifndef _ARGLIB_VALUE_H_
#define _ARGLIB_VALUE_H_

class Value {
	public:
		int getInt();
		unsigned int getUnsignedInt();
		long getLong();
		unsigned long getUnsignedLong();
		float getFloat();
		double getDouble();
		template <class T> T* getPointer();
	
		void setInt(int newValue) { i = newValue; }
		void setUnsignedInt(unsigned int newValue) { ui = newValue; }
		void setLong(long newValue) { l = newValue; }
		void setUnsignedLong(unsigned long newValue) { ul = newValue; }
		void setFloat(float newValue) { f = newValue; }
		void setDouble(double newValue) { d = newValue; }
		void setPointer(void* pointer);

	private:
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

