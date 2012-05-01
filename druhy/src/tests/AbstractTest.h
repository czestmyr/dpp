#ifndef _ARGLIB_ABSTRACTTEST_H_
#define _ARGLIB_ABSTRACTTEST_H_

class AbstractTest {
	public:
		/// Virtual destructor is needed for proper destruction in testing class
		virtual ~AbstractTest() {};

		/// Runs the test and returns whether it was successful.
		virtual bool runTest() = 0;

		/// Returns a short description of what the test does.
		virtual const char* getDescription() = 0;
	private:
};

#endif
