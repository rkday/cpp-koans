#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "values.hpp"
#include <optional>
#include <string>

TEST_CASE( "std::optional represents a value that may or may not exist") {

  std::optional<std::string> s;

  // Delete one of these
  CHECK( s.has_value() );
  CHECK_FALSE( s.has_value() );

  s = "Hello world";

  // Delete one of these
  CHECK( s.has_value() );
  CHECK_FALSE( s.has_value() );

  CHECK(s.value().length() == REPLACE_THIS_VALUE);
}

TEST_CASE( "std::optional evaluates to boolean true if it has a value and false otherwise") {

  std::optional<bool> b = std::nullopt;

  int x;

  if (b)
  {
    x = 11;
  }
  else
  {
    x = 14;
  }

  CHECK(x == REPLACE_THIS_VALUE);

  b = false;

  x = b ? 17 : 21;

  CHECK(x == REPLACE_THIS_VALUE);

  b = true;

  x = b ? 16 : 22;

  CHECK(x == REPLACE_THIS_VALUE);
}

TEST_CASE( "the * and -> dereference operators work on a std::optional") {

  std::optional<std::string> s{"Hello world"};

  // Delete one of these
  CHECK(s.value() == *s);
  CHECK_FALSE(s.value() == *s);

  CHECK(s->size() == REPLACE_THIS_VALUE);
}

TEST_CASE( "dereferencing a std::nullopt throws std::bad_optional_access") {

  std::optional<std::string> s = std::nullopt;
  std::string s2;

  int x;

  try {
    x = s->size();
  } catch (std::bad_optional_access& e) {
    x = 400000;
  }

  CHECK(x == REPLACE_THIS_VALUE);
}
