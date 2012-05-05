#ifndef _ARGLIB_ENUM_TESTS_H_
#define _ARGLIB_ENUM_TESTS_H_

class Tests;

class EnumTests {
	public:
		static void prepareTests();

	private:
		static bool emptyEnumTest();
		static bool stringInEnumTest();
		static bool multipleStringsInEnumTest();
};

#endif

