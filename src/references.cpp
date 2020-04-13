#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "values.hpp"

TEST_CASE( "References are an alias of the original variable") {
  int x = 4;
  int& reference_to_x = x;
  CHECK(reference_to_x == REPLACE_THIS_VALUE );
}

TEST_CASE( "Changing a reference changes the original value") {
  int x = 4;
  int& reference_to_x = x;
  reference_to_x++;
  CHECK( x == REPLACE_THIS_VALUE);
}

TEST_CASE( "This is different to a normal variable copy") {
  int x = 4;
  int y = x;
  int& reference_to_x = x;
  reference_to_x++;

  // Delete one of these
  CHECK(x == y);
  CHECK_FALSE(x == y);
}

TEST_CASE( "All references to the same variable are indistinguishable") {
  int x = 4;
  int& reference_to_x = x;
  int& other_reference_to_x = x;

  // Delete one of these
  CHECK(reference_to_x == other_reference_to_x);
  CHECK_FALSE(reference_to_x == other_reference_to_x);
}

TEST_CASE( "References are identical to the referenced variable so have the same size") {
  uint64_t x = 400000000000;
  int8_t y = -2;

  uint64_t& reference_to_x = x;
  int8_t& reference_to_y = y;

  // Delete one of these
  CHECK(sizeof(x) == sizeof(y));
  CHECK_FALSE(sizeof(x) == sizeof(y));

    // Delete one of these
  CHECK(sizeof(reference_to_x) == sizeof(reference_to_y));
  CHECK_FALSE(sizeof(reference_to_x) == sizeof(reference_to_y));
}

TEST_CASE( "References cannot be reassigned - assigning to them changes the original variable.") {
  int32_t a = 100;
  int32_t b = 200;

  int32_t& reference_to_a = a;

  CHECK(reference_to_a == REPLACE_THIS_VALUE);
  
  reference_to_a = b;

  CHECK(reference_to_a == REPLACE_THIS_VALUE);
  CHECK(a == REPLACE_THIS_VALUE);
  CHECK(b == REPLACE_THIS_VALUE);
}

TEST_CASE( "The . operator can be used to call methods through a reference") {
  std::string x = "Hello world";
  std::string& reference_to_x = x;

  // Delete one of these
  CHECK(x.size() == reference_to_x.size());
  CHECK_FALSE(x.size() == reference_to_x.size());
}

void do_something_to_a_value(int x)
{
  x += 1000;
}

void do_something_to_a_reference(int& x)
{
  x += 1000;
}

TEST_CASE( "References are useful to let other functions manipulate values, rather than changing their own copy of that value") {
  int a = 100;
  int b = 200;

  do_something_to_a_value(a);
  do_something_to_a_reference(b);

  CHECK(a == REPLACE_THIS_VALUE);
  CHECK(b == REPLACE_THIS_VALUE);
}

int times_copy_constructor_called = 0;

class ExpensiveObjectToCopy {
  public:
    ExpensiveObjectToCopy() {};
    ExpensiveObjectToCopy(const ExpensiveObjectToCopy& original) {
      times_copy_constructor_called++;
    };
};

void take_by_value(ExpensiveObjectToCopy c) {};
void take_by_reference(ExpensiveObjectToCopy& c) {};

TEST_CASE( "References to existing objects also save on expensive copy operations") {
  ExpensiveObjectToCopy c;

  CHECK(times_copy_constructor_called == 0);

  take_by_value(c);

  CHECK(times_copy_constructor_called == REPLACE_THIS_VALUE);

  take_by_reference(c);

  CHECK(times_copy_constructor_called == REPLACE_THIS_VALUE);
}