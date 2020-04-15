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

TEST_CASE( "dereferencing a std::nullopt using value() throws std::bad_optional_access") {

  std::optional<std::string> s = std::nullopt;

  int x;

  try {
    x = s.value().size();
  } catch (std::bad_optional_access& e) {
    x = 400000;
  }

  CHECK(x == REPLACE_THIS_VALUE);
}

TEST_CASE( "dereferencing a std::nullopt using * or -> is unchecked (and undefined behaviour!)") {

  std::optional<int> s = std::nullopt;

  int x;
  bool caught_exception = false;

  try {
    x = *s;
  } catch (std::bad_optional_access& e) {
    caught_exception = true;
  }

  // Delete one of these
  CHECK(caught_exception);
  CHECK_FALSE(caught_exception);
}

TEST_CASE( "value_or can be used to provide a default") {

  std::optional<int> x;
  std::optional<int> y{15};

  CHECK(x.value_or(100) == REPLACE_THIS_VALUE);
  CHECK(y.value_or(100) == REPLACE_THIS_VALUE);
}