#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "values.hpp"

TEST_CASE( "Const values cannot be changed") {
  const int x = 4;
  x = 5;
}

TEST_CASE( "Values cannot be changed through const pointers to them") {
  int x = 4;

  const int* ptr1 = &x;
  int* ptr2 = &x;
  
  x++;
  (*ptr2)++;
  (*ptr1)++;
}

// Functions that take const references cannot modify those values
void function_that_takes_const_reference(const std::string& x)
{
    x += "fin";
}

// Functions that take const references can call methods that don't modify them
void function_that_takes_const_reference2(const std::string& x)
{
    x.size();
}

// When defining a class, you can declare methods as 'const', i.e. safe to call
// on const objects.
class MyClass {
    public:
    void x() {};
    void y() const {};
};

void function_that_takes_const_reference3(const MyClass& c)
{
    c.y();
    c.x();
}

// Const methods must not modify the object.
class MyClass2 {
    public:
    void x() {};
    void y() const { mynum++; };
    private:
    
    int mynum;
};

// Sometimes, though, const methods need to modify member variables (e.g. taking
// a lock). The 'mutable' keyword indicates a member variable that can be
// mutated by a const method without making the object logically non-const.
class MyClass2 {
    public:
    void x() {};
    void y() const { mynum++; };
    private:
    
    mutable int mynum;
};
