#ifndef OPTION_TESTS_USAGE_TESTS_H
#define OPTION_TESTS_USAGE_TESTS_H

#include "framework.h"
#include "options.h"

namespace Tests {

class UsageTests: public TestGroup {
  public:
    UsageTests(): TestGroup("Library usage tests") {
      TimeOutput::init(this);
      ValueTest::init(this);
      SynonymTest::init(this);
      ResetTest::init(this);
      ArgumentsTest::init(this);
      ArgumentsTest2::init(this);
      ValueOrSeparator::init(this);
      OptionOrArgument::init(this);
      Nonexistent::init(this);
      OwnRestriction::init(this);
    }

    DECLARE_TEST(TimeOutput, "Output of help for the \"Time\" tests");
    DECLARE_TEST(ValueTest, "Time: Testing whether the value parsed by the library is correct");
    DECLARE_TEST(SynonymTest, "Time: Testing whether the values are the same for different synonyms of the option");
    DECLARE_TEST(ResetTest, "Time: Testing whether the parser can be run more than once");
    DECLARE_TEST(ArgumentsTest, "Time: Testing whether all the provided regular arguments are set (without --)");
    DECLARE_TEST(ArgumentsTest2, "Time: Testing whether all the provided regular arguments are set (--)");
    DECLARE_TEST(ValueOrSeparator, "Time: Testing whether \"--\" after an option is not an option value");
    DECLARE_TEST(OptionOrArgument, "Time: Testing whether the optional option is parsed correctly (not as a regular argument)");
    DECLARE_TEST(Nonexistent, "Time: Testing failure when getting an non-existent option value");
    DECLARE_TEST(OwnRestriction, "Testing whether user-defined restrictions work");

    static void prepareTimeExample(options::option_parser& parser);
};

}  // End namespace Tests

#endif

