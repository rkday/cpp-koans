#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "values.hpp"

TEST_CASE( "Pointers are the address in memory of the original variable") {
  int x = 4;
  int* ptr_to_x = &x;
  CHECK(*ptr_to_x == REPLACE_THIS_VALUE );
}

TEST_CASE( "Changing a pointer changes the original value") {
  int x = 4;
  int* ptr_to_x = &x;
  (*ptr_to_x)++;
  CHECK( x == REPLACE_THIS_VALUE);
}

TEST_CASE( "This is different to a normal variable copy") {
  int x = 4;
  int y = x;
  int* ptr_to_x = &x;
  (*ptr_to_x)++;

  // Delete one of these
  CHECK(x == y);
  CHECK_FALSE(x == y);
}

TEST_CASE( "All pointers to the same variable have the same value") {
  int x = 4;
  int* ptr_to_x = &x;
  int* other_ptr_to_x = &x;

  // Delete one of these
  CHECK(ptr_to_x == other_ptr_to_x);
  CHECK_FALSE(ptr_to_x == other_ptr_to_x);
}

TEST_CASE( "All pointers are the same size, whatever they point to") {
  uint64_t x = 400000000000;
  int8_t y = -2;

  // Delete one of these
  CHECK(sizeof(x) == sizeof(y));
  CHECK_FALSE(sizeof(x) == sizeof(y));

    // Delete one of these
  CHECK(sizeof(&x) == sizeof(&y));
  CHECK_FALSE(sizeof(&x) == sizeof(&y));
}
