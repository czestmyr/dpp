#ifndef _ARGLIB_USE_CASES_H_
#define _ARGLIB_USE_CASES_H_

class Tests;

class UseCases {
	public:
		/// Adds the use cases to the given test set.
		static void addTestsTo(Tests* testSet);

	private:
		static bool runShortOptionsTest();
};

#endif
