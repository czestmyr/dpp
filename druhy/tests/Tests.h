#ifndef _ARGLIB_TESTS_H_
#define _ARGLIB_TESTS_H_

#include <vector>
#include <string>
#include "Arglib.h"

#include "TestFunction.h"

class ArgList;
class FrontEnd;

class Tests {
	public:
		/// Returns the singleton instance of the testing class.
		static Tests& inst();

		/// Adds a new test to be performed.
		void addTest(TestFunctionPtr test, const char* testDescription);

		/// Runs all the tests that have been registered so far.
		bool runTests();

		/// Parse the argument list with the instance of arguments library.
		/// This method succeedes when the parsing throws an exception
		static bool parseMustThrow(FrontEnd& arglib, const ArgList& arguments);

		/// Parse the argument list with the instance of arguments library.
		/// This method succeedes when the parsing does not throw an exception
		static bool parseMustNotThrow(FrontEnd& arglib, const ArgList& arguments);

		/// Queries the instance of arguments library to specified option 
		/// This method succeedes when the parsing throws an exception
		template <class returnType, class nameType>
		static bool getOptionValueMustThrow(FrontEnd& arglib, nameType optionName) {
			try {
				arglib.getOptionParameter<returnType>(optionName);
			} catch (ArgumentException e) {
				cout << "Exception: " << e.what();
				return true;
			}

			return false;
		};

		/// Queries the instance of arguments library to specified option 
		/// This method succeedes when the parsing does not throw an exception
		template <class returnType, class nameType>
		static bool getOptionValueMustNotThrow(FrontEnd& arglib, nameType optionName) {
			try {
				arglib.getOptionParameter<returnType>(optionName);
			} catch (ArgumentException e) {
				cout << "Exception: " << e.what();
				return false;
			}

			return true;
		};

	private:
		std::vector<TestFunctionPtr> tests;
		std::vector<std::string> testDescriptions;

		static Tests instance;
};

#endif
