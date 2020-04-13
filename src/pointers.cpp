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

TEST_CASE( "All pointers to the same variable have the same value (same memory address)") {
  int x = 4;
  int* ptr_to_x = &x;
  int* other_ptr_to_x = &x;

  // Delete one of these
  CHECK(ptr_to_x == other_ptr_to_x);
  CHECK_FALSE(ptr_to_x == other_ptr_to_x);
}

TEST_CASE( "Pointers to different variables have different values (different memory address)") {
  int x = 4;
  int y = 4;
  int* ptr_to_x = &x;
  int* ptr_to_y = &y;

  // Delete one of these
  CHECK(ptr_to_x == ptr_to_y);
  CHECK_FALSE(ptr_to_x == ptr_to_y);


  // Delete one of these
  CHECK(*ptr_to_x == *ptr_to_y);
  CHECK_FALSE(*ptr_to_x == *ptr_to_y);
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

TEST_CASE( "Pointers can be reassigned - which changes the value of the pointer but not the thing pointed to.") {
  int32_t a = 100;
  int32_t b = 200;

  int32_t* x = &a;

  CHECK(*x == REPLACE_THIS_VALUE);
  
  x = &b;

  CHECK(*x == REPLACE_THIS_VALUE);
  CHECK(a == REPLACE_THIS_VALUE);
  CHECK(b == REPLACE_THIS_VALUE);
}

TEST_CASE( "The -> operator can be used to call methods through a pointer") {
  std::string x = "Hello world";
  std::string* ptr_to_x = &x;

  // Delete one of these
  CHECK((*ptr_to_x).size() == ptr_to_x->size());
  CHECK_FALSE((*ptr_to_x).size() == ptr_to_x->size());

  // Delete one of these
  CHECK(x.size() == ptr_to_x->size());
  CHECK_FALSE(x.size() == ptr_to_x->size());
}

void do_something_to_a_value(int x)
{
  x += 1000;
}

void do_something_to_a_pointer(int* x)
{
  *x += 1000;
}

TEST_CASE( "Pointers are useful to let other functions manipulate values, rather than changing their own copy of that value") {
  int a = 100;
  int b = 200;

  do_something_to_a_value(a);
  do_something_to_a_pointer(&b);

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
void take_by_ptr(ExpensiveObjectToCopy* c) {};

TEST_CASE( "Pointers to existing objects also save on expensive copy operations") {
  ExpensiveObjectToCopy c;

  CHECK(times_copy_constructor_called == 0);

  take_by_value(c);

  CHECK(times_copy_constructor_called == REPLACE_THIS_VALUE);

  take_by_ptr(&c);

  CHECK(times_copy_constructor_called == REPLACE_THIS_VALUE);
}

int double_it(int x)
{
  return x * 2;
}

int halve_it(int x)
{
  return x / 2;
}

bool are_they_the_same(int x, int y)
{
  return x == y;
}

TEST_CASE( "As well as pointers to values, you can have pointers to functions.") {
  // Declare a function pointer that returns an int, is called 'fp', and takes one int argument.
  int (*fp)(int) = nullptr;

  // Make fp point to the double_it function
  fp = &double_it;

  // Call it
  CHECK((*fp)(5) == REPLACE_THIS_VALUE);

  // The & is optional for pointers to functions
  fp = halve_it;

  // Call it
  CHECK((*fp)(400) == REPLACE_THIS_VALUE);

  // Declare a function pointer that returns a bool, is called 'fp2', and takes two int arguments.
  bool (*fp2)(int, int) = &are_they_the_same;

  CHECK((*fp2)(2, REPLACE_THIS_VALUE));
}

int do_two_things(int x, int (*func1)(int), int (*func2)(int))
{
  int intermediate = (*func1)(x);
  return (*func2)(intermediate);
}

TEST_CASE( "You can have functions that accept pointers to functions, allowing the user to control their behaviour.") {
  CHECK(do_two_things(100, double_it, double_it) == REPLACE_THIS_VALUE);
  CHECK(do_two_things(100, halve_it, halve_it) == REPLACE_THIS_VALUE);
  CHECK(do_two_things(100, halve_it, double_it) == REPLACE_THIS_VALUE);
  CHECK(do_two_things(100, double_it, halve_it) == REPLACE_THIS_VALUE);
}

TEST_CASE( "You can have pointers to pointers.") {
  int x = 4;

  int* y = &x;

  int** z = &y;

  CHECK(*y == REPLACE_THIS_VALUE);
  CHECK(**z == REPLACE_THIS_VALUE);

  // Delete one of these
  CHECK((void*)z == (void*)y);
  CHECK_FALSE((void*)z == (void*)y);

  int a = 5;

  *z = &a;

  CHECK(x == REPLACE_THIS_VALUE);
  CHECK(a == REPLACE_THIS_VALUE);
  CHECK(*y == REPLACE_THIS_VALUE);
}

void create_me_an_int(int** x)
{
  int* myvar = new int(17);
  *x = myvar;
}

TEST_CASE( "Pointers to pointers are commonly used so that a function can allocate some memory and tell you where it is.") {
  int* y = nullptr;

  create_me_an_int(&y);

  // Delete one of these
  CHECK(y == nullptr);
  CHECK_FALSE(y == nullptr);

  CHECK(*y == REPLACE_THIS_VALUE);

  delete y;
}

TEST_CASE( "void* are generic pointers that don't record what type their memory is") {
  const char* c = "Hello world";
  int y = 4;
  int* x = &y;

  // Any pointer type can be cast to void
  void* void_ptr_1 = (void*)c;

  void* void_ptr_2 = (void*)x;

  // Delete one of these
  CHECK(void_ptr_1 == void_ptr_2);
  CHECK_FALSE(void_ptr_1 == void_ptr_2);

  // You can cast back to the original pointer type

  CHECK(*(int*)void_ptr_2 == REPLACE_THIS_VALUE);
  CHECK(strlen((const char*)void_ptr_1) == REPLACE_THIS_VALUE);

  // But you need to make sure you get this right - because you've lost the type information, the compiler can't check your cast is correct
  
  // Delete one of these
  CHECK(*(int*)void_ptr_1 == y);
  CHECK_FALSE(*(int*)void_ptr_1 == y);
}

TEST_CASE( "Pointers are 'just numbers' and you can add to them. This is useful when working with arrays, to advance through the array.") {
  int32_t array_of_ints[2];

  array_of_ints[0] = 100;
  array_of_ints[1] = 200;

  int32_t* x = &array_of_ints[0];

  CHECK(*x == REPLACE_THIS_VALUE);
  
  x += 1;

  CHECK(x == &array_of_ints[1]);

  CHECK(*x == REPLACE_THIS_VALUE);
  CHECK(array_of_ints[0] == REPLACE_THIS_VALUE);
  CHECK(array_of_ints[1] == REPLACE_THIS_VALUE);
}

TEST_CASE( "In fact, because pointers are 'just numbers' you can set them to anything. This will usually crash.") {
  int32_t* x = (int32_t*)5;

  // This will probably crash; comment this line out once you've seen it crash.
  CHECK(*x == 0);
}
