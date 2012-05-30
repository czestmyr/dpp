#ifndef OPTION_TESTS_USAGE_TESTS_H
#define OPTION_TESTS_USAGE_TESTS_H

#include "framework.h"
#include "options.h"

namespace Tests {

class UsageTests: public TestGroup {
  public:
    UsageTests(): TestGroup("Library usage tests") {
      TimeOutput::init(this);
    }

    DECLARE_TEST(TimeOutput, "Output of help for the \"Time\" tests");

    static void prepareTimeExample(options::option_parser& parser);
};

}  // End namespace Tests

#endif

