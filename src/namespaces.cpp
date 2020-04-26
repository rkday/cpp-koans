#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "values.hpp"

namespace foo {
  int x = 4;
  int m = 50;
}

namespace bar {
  int x = 5;
  int y = 10;
}

int x = 6;
int y = 11;

TEST_CASE( "Namespaces let you reuse the same variable name without clashing") {
  CHECK( x == REPLACE_THIS_VALUE );
  CHECK( foo::x == REPLACE_THIS_VALUE );
  CHECK( bar::x == REPLACE_THIS_VALUE );
}

namespace foo {

TEST_CASE( "Within a namespace, unqualified variables are assumed to refer to other things in the namespace") {
  REQUIRE( x == REPLACE_THIS_VALUE );
}

TEST_CASE( "...but if there is no variable with that name in the namespace, they refer to the global variable") {
  REQUIRE( y == REPLACE_THIS_VALUE );
}

TEST_CASE("You can explicitly refer to the non-namespaced variable using ::") {
  REQUIRE( ::x == REPLACE_THIS_VALUE );
} 
}

TEST_CASE("'using' a namespace will bring all its variables into scope, so you can refer to them without the namespace, as long as they don't clash") {
  using namespace foo;
  REQUIRE( m == REPLACE_THIS_VALUE );
}

TEST_CASE("You can also use 'using' to bring just part of a namespace into scope") {
  using bar::y;
  REQUIRE( x == REPLACE_THIS_VALUE );
  REQUIRE( y == REPLACE_THIS_VALUE );
}

namespace bar {
  namespace baz {
    int z = 100;
  }
}

TEST_CASE("Namespaces can be nested") {
  REQUIRE( bar::baz::z == REPLACE_THIS_VALUE );
}

namespace foo {
  inline namespace abcd {
    int z = 200;
  }
}

TEST_CASE("Inline namespaces are also visible in their parent namespace scope") {
  REQUIRE( foo::z == REPLACE_THIS_VALUE );
  REQUIRE( foo::abcd::z == REPLACE_THIS_VALUE );
}
