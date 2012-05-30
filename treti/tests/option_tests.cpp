#include "option_tests.h"

namespace Tests {

bool OptionTests::EmptyOption::run() {
  option opt;
  checkOptionIntegrity(opt);
  return true;
}

bool OptionTests::ShortNames::run() {
  option opt;
  for (char c = 'a'; c <= 'z'; c++) {
    opt.insert_short_name(c);
  }
  for (char c = 'f'; c <= 'z'; c++) {
    opt.erase_short_name(c);
  }
  ASSERT_EQUALS(opt.short_names_size(), 'f'-'a');

  checkOptionIntegrity(opt);
  return true;
}

bool OptionTests::LongNames::run() {
  option opt;
  opt.insert_long_name("foo");
  opt.insert_long_name("bar");
  opt.insert_long_name("tag");
  opt.erase_long_name("bar");

  ASSERT_EQUALS(opt.long_names_size(), 2);

  checkOptionIntegrity(opt);
  return true;
}

bool OptionTests::Mark::run() {
  option opt;
  ASSERT_FALSE(opt);
  ASSERT(!opt);
  opt.mark();
  ASSERT(opt);
  ASSERT_FALSE(!opt);

  checkOptionIntegrity(opt);
  return true;
}

bool OptionTests::OutputTest::run() {
  option opt("fF", "foo,Foo", "Foo option");
  out() << opt;

  checkOptionIntegrity(opt);
  return true;
}

void OptionTests::checkOptionIntegrity(option& opt) {
  const option& const_opt = opt;
  ASSERT_EQUALS(opt.short_names_begin() + opt.short_names_size(), opt.short_names_end());
  ASSERT_EQUALS(opt.long_names_begin() + opt.long_names_size(), opt.long_names_end());
  ASSERT_EQUALS(const_opt.short_names_begin() + const_opt.short_names_size(), const_opt.short_names_end());
  ASSERT_EQUALS(const_opt.long_names_begin() + const_opt.long_names_size(), const_opt.long_names_end());
}

}  // End namespace Tests

