# cpp-koans

These are programming koans - short pieces of code which you can fix errors in and improve your knowledge of C++.

This is inspired by the more popular http://rubykoans.com/, which has a lot written about it - see e.g. https://pragmaticstudio.com/blog/2005/03/18/ruby-learning-test-1-are-you-there-world for the concept of a "learning test".

## Running them

If you have Clang and Python3 installed, you can run these with:

```
./koan_runner.py
```

If not, you can run them in a Docker container:

```
docker build -t cpp-koans .
docker run -it --rm cpp-koans
```

## Your first koan

```
$ ./koan_runner.py  
=== Compiling koan introduction.cpp ===
=== Running koan introduction.cpp ===

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
introduction is a Catch v2.11.3 host application.
Run with -? for options

-------------------------------------------------------------------------------
One plus one
-------------------------------------------------------------------------------
src/introduction.cpp:5
...............................................................................

src/introduction.cpp:6: FAILED:
  REQUIRE( 1 + 1 == REPLACE_THIS_VALUE )

===============================================================================
test cases: 1 | 1 failed
assertions: 1 | 1 failed




0 out of 2 koans ran successfully
Koan src/introduction.cpp failed
Check the output above and fix up the file to proceed
```

If you fix this by editing `src/introduction.cpp` to read:

```
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "values.hpp"

TEST_CASE( "One plus one") {
  REQUIRE( 1 + 1 == 2 );
}
```

then the `introduction.cpp` koan will start passing and the runner will move onto the next koan:

```
$ ./koan_runner.py  
=== Compiling koan introduction.cpp ===
=== Running koan introduction.cpp ===
===============================================================================
All tests passed (1 assertion in 1 test case)

=== Compiling koan pointers.cpp ===
=== Running koan pointers.cpp ===

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pointers is a Catch v2.11.3 host application.
Run with -? for options

-------------------------------------------------------------------------------
Pointers are the address in memory of the original variable
-------------------------------------------------------------------------------
src/pointers.cpp:6
...............................................................................

src/pointers.cpp:9: FAILED:
  CHECK( *ptr_to_x == REPLACE_THIS_VALUE )

===============================================================================
test cases: 1 | 1 failed
assertions: 1 | 1 failed




1 out of 2 koans ran successfully
Koan src/pointers.cpp failed
Check the output above and fix up the file to proceed
```

You can also just run a specific koan:

```
$ ./koan_runner.py introduction.cpp
=== Compiling koan introduction.cpp ===
=== Running koan introduction.cpp ===
===============================================================================
All tests passed (1 assertion in 1 test case)
```

## Compilation failures

Some concepts deal with compiler errors - e.g. the 'const' koan demonstrates that various operations on const variables are forbidden and do not compile.

These generally have '_compile' in the koan name.

Because these demonstrate things forbidden by the language, you will generally progress through these koans by removing the offending code.

## Topics

### C++ language fundamentals

- [x] Pointers
- [x] References
- [ ] The 'static' keyword
- [x] The 'const' keyword
- [ ] Control loops
- [ ] Default arguments
- [ ] Namespaces
- [ ] Exceptions
- [ ] enum/enum class
- [ ] Integer conversion
- [ ] Template programming

### OOP

- [ ] Classes and structs
- [ ] Constructors and destructors
- [ ] Subclassing and virtual functions
- [ ] Operator overloading

### C++ standard library

- [ ] Data structures
- [ ] Algorithms (e.g. sorting)
- [ ] Time
- [ ] IO streams
- [ ] Filesystem
- [x] std::optional
- [ ] Type-safe unions

### Multithreading

- [ ] Threads
- [ ] Thread-local variables
- [ ] Locks
- [ ] Condition variables

### Modern C++

- [ ] Lambdas
- [ ] Structured binding
- [ ] Smart pointers
- [ ] Move semantics
- [ ] Copy and move constructors
- [ ] Uniform initialization
- [ ] constexpr
- [ ] static_assert
- [ ] C++-style casts

### C++ patterns

- [ ] RAII
- [ ] SFINAE