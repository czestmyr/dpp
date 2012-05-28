#ifndef OPTION_TESTS_FRAMEWORK_H
#define OPTION_TESTS_FRAMEWORK_H

#include <exception>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------
//                             Formatted output macros
//------------------------------------------------------------------------------
#ifdef COLORS
  #define GREEN_BEGIN "\e[0;32m"
  #define RED_BEGIN "\e[0;31m"
  #define YELLOW_BEGIN "\e[0;33m"
  #define COLOR_END "\e[0m"
#else
  #define GREEN_BEGIN ""
  #define RED_BEGIN ""
  #define COLOR_END ""
#endif
#define TEST_TAB "       "
#define TEST_SEP "=====> "
#define TEST_ENDL std::endl << TEST_TAB

//------------------------------------------------------------------------------
//         Macros for definition of test classes inside test groups
//------------------------------------------------------------------------------
#define DECLARE_TEST(name, description) \
    class name: public Test {\
      public:\
        static void init(TestGroup* parent) {\
          parent->appendTest(new name ());\
        }\
\
        const char* getDescription() {\
          return description ;\
        }\
\
        bool run();\
    };\

//------------------------------------------------------------------------------
//                                  Assertions
//------------------------------------------------------------------------------

// Asserts that an expression evaluates to true
#define ASSERT(expr) {\
  if (expr) {\
  } else {\
    throw ::Tests::TestingException() << "Assertion \"" << #expr << "\" failed in " << __FILE__ << ":" << __LINE__;\
  }\
}

// Asserts that an expression evaluates to true
#define ASSERT_FALSE(expr) {\
  if (expr) {\
    throw ::Tests::TestingException() << "Assertion \"" << #expr << " == false\" failed in " << __FILE__ << ":" << __LINE__;\
  }\
}

// Assert that two expressions are equal. Warning! Both expressions are evaluated twice!
#define ASSERT_EQUALS(value1, value2) {\
  if (value1 != value2) {\
    throw ::Tests::TestingException() << "Assertion failed in \"" << #value1 << " == " << #value2 <<\
      "\". Was " << value1 << " and " << value2;\
  }\
}

// Asserts that two expressions are equal. Does not print their value and evaluates them only once.
#define ASSERT_EQUALS_NOPRINT(value1, value2) {\
  if (value1 != value2) {\
    throw ::Tests::TestingException() << "Assertion failed in \"" << #value1 << " == " << #value2 << "\"";\
  }\
}

//------------------------------------------------------------------------------
//                                 Test classes
//------------------------------------------------------------------------------
namespace Tests {

/// Testing exception class
class TestingException: public std::exception {
  public:
    TestingException() {}
    ~TestingException() throw() {}

    /// Operator for exception message creation
    template <class T>
    TestingException& operator<< (const T& output) {
      std::stringstream ss(message);
      ss.seekp(0, std::ios_base::end);
      ss << output;
      message = ss.str();
      return *this;
    }

    /// Extraction of exception message
    const char* what() const throw() { return message.c_str(); }

  private:
    std::string message;
};

// A simple test class
class Test {
  public:
    /// The method that will run the test.
    /// A boolean value describing the outcome of the test should be returned.
    virtual bool run() = 0;

    /// A short (one line) description of this test.
    virtual const char* getDescription() = 0;

    /// Outputs the simulated command line to the cout.
    void dumpArguments(int argc, const char* argv[]);

    /// Returns an output stream to be used in tests
    std::ostream& out() {
      return output;
    }

    /// Redirects error output to our stringstream
    void redirectErr() {
      errBackup = std::cerr.rdbuf();
      std::cerr.rdbuf(errorOutput.rdbuf());
    }

    /// Restores the state of error output to original state before calling redirectErr()
    void restoreErr() {
      std::cerr.rdbuf(errBackup);
    }

    /// Dumps output stream to std::cout
    void dumpOutput();

    /// Dumps error output stream to std::cout
    void dumpErrorOutput();

  private:
    std::stringstream output;
    std::stringstream errorOutput;
    std::streambuf* errBackup;
};

/// A group of tests
class TestGroup {
  public:
    /// Destructor is virtual, so that we can define new test groups by inheritance.
    virtual ~TestGroup() {
      for (unsigned int i = 0; i < tests.size(); i++) {
        delete tests[i];
      }
    }

  private:
    /// Copying of this class is forbidden.
    TestGroup(const TestGroup& other) {}

  public:
    /// Create a new test group with the given description.
    /// &param _description The description of the new test group.
    TestGroup(const char* _description): description(_description) {}

    /// Runs all tests that were included in this group by appendTest().
    /// &param verbose Whether cerr and cout should be 
    /// &return Number of tests that were successful.
    int runTests(bool verbose);

    /// Returns the total number of tests that are inside this group.
    /// &return Number of included tests.
    int getTestNum() {
      return tests.size();
    }

    /// Appends a test to this group.
    /// &param test The test object to be included in this group.
    void appendTest(Test* test) {
      tests.push_back(test);
    }

  private:
    std::vector<Test*> tests;
    const char* description;
};

/// Testing framework
class Tests {
  public:
    Tests() {}
    ~Tests();

    /// Appends a new test group to the framework
    void appendGroup(TestGroup* group) {
      testGroups.push_back(group);
    }

  private:
    /// Copying of this class is forbidden
    Tests(const Tests& other) {}

  public:
    /// Runs all the tests and prints output to console
    bool runTests(bool verbose);

  private:
    std::vector<TestGroup*> testGroups;
};

}  // End namespace Tests

#endif

