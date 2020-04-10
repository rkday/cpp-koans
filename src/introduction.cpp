#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "values.hpp"

TEST_CASE( "One plus one") {
  REQUIRE( 1 + 1 == REPLACE_THIS_VALUE );
}
