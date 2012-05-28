#include "category_tests.h"

#include <iostream>

using namespace options;
using namespace std;

namespace Tests {

bool CategoryTests::Init1::run() {
  option_category cat;
  return checkSanity(cat);
}

bool CategoryTests::Init2::run() {
  option_category cat("Test options", "Options that should test this library");
  return checkSanity(cat);
}

bool CategoryTests::Add1::run() {
  option_category cat("Test options", "Options that should test this library");
  cat.add_options()
    ("v", "verbose", "Whether the output of the program should be verbose")
    ("h", "help", "Print out help for the program");
  return checkSanity(cat, 2);
}

bool CategoryTests::Add2::run() {
  option_category cat("Test options", "Options that should test this library");
  cat.add_options()
    << option("v", "verbose", "Whether the output of the program should be verbose")
    << option("h", "help", "Print out help for the program");
  return checkSanity(cat, 2);
}

bool CategoryTests::Output::run() {
  option_category cat("Test options", "Options that should test this library");
  out() << cat;
  return checkSanity(cat, 0);
}

bool CategoryTests::checkSanity(option_category& cat, size_t size) {
  const option_category& constCat = cat;

  ASSERT_EQUALS(cat.size(), size);
  ASSERT_EQUALS_NOPRINT(cat.begin() + cat.size(), cat.end());
  ASSERT_EQUALS_NOPRINT(constCat.begin() + constCat.size(), constCat.end());

  return true;
}

}  // End namespace Tests

