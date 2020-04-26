#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "values.hpp"

namespace foo {
  int x = 4;
}

int x = 6;

TEST_CASE( "Referencing an ambiguous name is an error") {
  using namespace foo;
  REQUIRE( x == 4 );
}
