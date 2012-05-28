#ifndef OPTION_TESTS_FRAMEWORK_H
#define OPTION_TESTS_FRAMEWORK_H

#include <exception>
#include <vector>
#include <string>
#include <sstream>

//------------------------------------------------------------------------------
//                             Colored output macros
//------------------------------------------------------------------------------
#ifdef COLORS
	#define GREEN_BEGIN "\e[0;32m"
	#define RED_BEGIN "\e[0;31m"
	#define COLOR_END "\e[0m"
#else
	#define GREEN_BEGIN ""
	#define RED_BEGIN ""
	#define COLOR_END ""
#endif

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
#define ASSERT_EQUALS(value1, value2) {\
  if (value1 != value2) {\
    throw ::Tests::TestingException() << "Assertion failed in \"" << #value1 << " == " << #value2 <<\
      "\". Was " << value1 << " and " << value2;\
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

    TestingException(const TestingException& other) {
      message << other.message.rdbuf();
    }

    ~TestingException() throw() {}

    /// Operator for exception message creation
    template <class T>
    TestingException& operator<< (const T& output) {
      message << output;
      return *this;
    }

    /// Extraction of exception message
    const char* what() const throw() { return message.str().c_str(); }

  private:
    std::stringstream message;
};

// A simple test class
class Test {
  public:
    /// The method that will run the test.
    /// A boolean value describing the outcome of the test should be returned.
    virtual bool run() = 0;

    /// A short (one line) description of this test.
    virtual const char* getDescription() = 0;
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
    /// &return Number of tests that were successful.
    int runTests();

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
    bool runTests();

  private:
    std::vector<TestGroup*> testGroups;
};

}  // End namespace Tests

#endif

