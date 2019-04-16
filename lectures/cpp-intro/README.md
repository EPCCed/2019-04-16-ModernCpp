template: titleslide

# A brief introduction to C++
## Rupert Nash
## r.nash@epcc.ed.ac.uk

---

template: titleslide
# Introduction

---
# Assumptions

- You are a decent programmer in another language

- You know how to use the shell

- You have access to a terminal in front of you with a C++ compiler

---
# What this is not!

Writing efficient software, more than anything, requires you to choose
an appropriate algorithmic approach for your problem.

<!-- For lots on how to do this well, consider the Parallel Design Patterns course. -->

Here we want to take a lower-level approach and talk about how to
implement patterns efficiently using C++.

---
# What is "scientific computing"?

Both HPC and data science, when you actually come to running a
program, are about getting a large amount of data from memory to a
core, doing something useful to it, and storing it again.

This is why FORTRAN is still relevant!

But it does force you to confront this all time.

I've mentioned previously than C++ is all about building abstractions
and composing them.

![:thumb](I will talk about a few and give some suggestions of
default rules)

---
# These few lectures

We could spend a whole semester going in depth on C++, so we've picked
a handful of features to cover that you really need to write C++ for
technical computing.

<!-- - Basic syntax and concepts of the language -->

<!-- - References and memory -->

<!-- - Overloading -->

<!-- - Classes -->

<!-- - Templates -->

---
# The misunderstood monster

.center[![:scale_img 30%](frank_mon.jpg)]

By Universal Studios - Dr. Macro, Public Domain,
https://commons.wikimedia.org/w/index.php?curid=3558176

---
# The misunderstood monster

- Large: the C++17 standard is about 1600 pages

- Composed of many parts: C, classes, generics, functional
  programming, exceptions, the vast library, ...

- Inspires dread in those do not understand it

- Dangerous:
> "C makes it easy to shoot yourself in the foot;
> C++ makes it harder, but when you do it blows your whole leg
> off." - Bjarne Stroustrup

- "Expert friendly"

---
#Octopus vs Swiss Army knife

> "C++ is an octopus made by nailing extra legs onto a dog" - Steve Taylor

.center[![:scale_img 40%](octodog.jpg) ![:scale_img 40%](sak.jpg)]

But you can cut off some extra legs to get the right dog for your
program!

---
# The philosophy of C++

-   General purpose

-   Flexible by allowing developers to build abstractions (and provides
    a large number through the library)

-   Performance and efficiency are always targeted "You only pay for
    what you use"

-   Use the powerful type system to express intent.

---

# References
-   Bjarne Stroustrup, "Programming: Principles and Practice Using C++"
    (2nd Ed.). Assumes very little but it's long

-   Bjarne Stroustrup, "A Tour of C++". Assumes you're an experience
    programmer and is quite brief - recently updated for C++17

-   Best online *reference* is <http://en.cppreference.com/>
    (comes in other human languages too!)

-   Scott Meyers, "Effective Modern C++", 2014. This is *the* book to
    get once you know your way around C++, but you want to improve.
    Teaches lots of techniques and rules of thumb for writing correct,
    idiomatic, maintainable code.

-   [stackoverflow.com](stackoverflow.com) has a lot of good questions
    about C++ (look for ones with at least 100 up-votes).

---
template: titleslide
# But first\...

---
name: hello
# Hello!

```C++
#include <iostream>

int main(int argc, char* argv[]) {
  // Write a greeting to the terminal.
  std::cout << "Hello, world!" << std::endl;
}
```

---
template: hello

```
$ g++ --std=c++11 hello.cpp -o hello
$ ./hello 
Hello, world!
```

---
template: hello

- The C preprocessor is run before the compiler.

- The `#include` directive copies the contents of another file into
  the current compilation unit.

- The angle brackets `<...>` tell it to look only in system
  directories.

- This includes the `iostream` standard library header which gives us
  a way to communicate with the file system

---
template: hello

- Every program must have exactly one main function.

- The compiler and OS arrange for this to be called when you run it.

- Number of command line arguments supplied as first argument

- The array of argument strings are supplied as second

---
template: hello

`std` is the standard library namespace.

- A namespace allows scoping of names (much like a filesystem has
  directories).

- The scope resolution operator `::` lets us access a declaration from
  inside a namespace.

- `cout` represents console output (i.e. stdout)

---
template: hello

- The standard library uses the bitwise left shift operator (`<<`) to mean
  stream insertion

- I.e. output the right hand side to the left.

- Every statement in C++ must be terminated with a semicolon (`;`)

---
template: hello

- The `return` statement exits the current function.

- The value must be (convertible to) the declared return type of your
  function.

- The `main` function should return a status code to the shell (zero
  being success)

---

template: titleslide
# Variables

---
# Variables

A variable is

- an object

or

- a reference (we'll come back to these)

that is declared to have a name.

---

# Objects

An object is a region of storage that has:

- type
- size
- value
- lifetime

---

template: titleslide
# Types

---
# What is a type?

> "Objects, references, functions (including function template
> specializations), and expressions have a property called type, which
> both restricts the operations that are permitted for those entities
> and provides semantic meaning to the otherwise generic sequences of
> bits." -- <https://en.cppreference.com>

---
# Fundamental types

| Type     | Description |
|----------|-------------|
| `void`   | Nothing - used to indicate a function returns no value.|
| `bool`   | `true` or `false` |
| `char`   | Smallest addressable integer that can hold an ASCII character, may be signed or unsigned. *Usually* 8 bits unsigned.|
| `short`  | *Signed* integer of *at least* 16 bits |
| `int`    | Standard *signed* integer for your machine. *At least* 16 bits. *Usually* 32 bits.|
| `long`   | Long signed integer of at least 32 bits. *Usually* 64 bits.|
| `float`  | Single-precision floating point. *Usually* an IEEE 754 32 bit number.|
| `double` |   Double-precision floating point. *Usually* an IEEE 754 64 bit number.|

All integer types can be modified with the `signed` or `unsigned`.

The header `<cstdint>` provides fixed-width integer types available on
your implementation: e.g. `std::int32_t` and `std::uint64_t`.

---
# Class types

Called "class types" formally - can be defined with either the `class`
or `struct` keyword.

```C++
struct Complex {
  double real;
  double imag;
};
```

This style of type is often called a "plain old data" (POD) type, a
trivial type, or a C-style type (if the members are also trivial).

This simply aggregates together several *members* which have a name
and type. You can then pass them around together and access the data.

---
# Class types

Creating trivial types:

```C++
Complex mk_imaginary_unit() {
  Complex sqrt_m1;
  sqrt_m1.real = 0;
  sqrt_m1.imag = 1;
  return sqrt_m1;
}
```

Alternatively:
```C++
Complex mk_imaginary_unit() {
  Complex sqrt_m1 = {0, 1};
  return sqrt_m1;
}
```

---
# Class types

Using trivial types:

```C++
void test() {
  Complex z = mk_imaginary_unit();
  assert(z.real == 0);
  assert(z.imag == 1);
}
```

Any piece of code can access the member variables inside the object.

---
# Value

For integers, very easy: the pattern of bits

For class types this can be subtle and user-defined...

Roughly: the Platonic ideal of the class

What does this program print?

```C++
int global;

int main(int argv, char* argv[]) {
  int automatic;
  std::cout << "Global int = " << global << std::endl;
  std::cout << "Local int = " << automatic << std::endl;
}
```
--
```
Global int = 0
Local int = -10023527
```

---
# Lifetime

All objects have lifetime: they are allocated and deallocated.

This can be bounded by the _storage duration_

- automatic: aka local variables- have storage allocated for the scope
  of the enclosing scope (i.e. `{` enclosed `}` block).

- static: allocated before main is called and deallocated after it
  returns, only one object exists.

- thread: exists for the lifetime of the thread - only copy per thread
  
- dynamic: storage is allocated and deallocated on request


---
template: titleslide
# Control statements

---
# if

```C++
if (condition)
  statement-or-block-if-true
else
  statement-or-block-if-false
```

---
# while

```C++
while (condition)
  statement-or-block
```
The condition is evaluated before each iteration of the loop body.

---
# for

```C++
for (init-clause; condition; next)
  statement-or-block
```
  
This is equivalent to

```C++
{
  init-clause;
  while (condition) {
	statement-or-block
	next;
}
```

---
# for

The traditional way to do something `N` times is

```C++
for (int i = 0; i < N; ++i) {
  // Do something with i
}
```

Note:
- `i` will take the values from `0` up to but not including `N`
- `i` will go out of scope at the end of the loop
- We use the "pre-increment" operator `++i`
- You might prefer to use `i != N` as the condition

---
# switch

```C++
switch (expression-of-integer-type) {
  case const-expression-1:
	statements

  case const-expression-2:
	statements

  default:
	statements

}
```

Note that execution will "fall through" to subsequent cases unless you
say break!

---
# switch

```C++
switch (expression-of-integer-type) {
  case const-expression-1:
	statements
	break;
  case const-expression-2:
	statements
	break;
  default:
	statements
	break;
}
```

Always add `break;` unless you are *really sure* you want to fall
through - then leave a comment!

---

template: titleslide
# Functions

---
# Functions

A function encapsulates a piece of code and gives it a name so
you can reuse it later.

```C++
void hello() {
  std::cout << "Hello, world!" << std::endl;
}

int main(int argc, char* argv[]) {
  // call the function
  hello();
}
```


---
# Functions

You must declare the return type and argument types.

Arguments are local variables that are initialised by the caller.

Return a value with the `return` statement - the type of the
expression must be (convertible to) the declared return type.

```C++
int sum(int a, int b) {
  return a + b;
}
```

Can alse use trailing return type (aka "east end functions"):
```C++
auto sum(int a, int b) -> int {
  return a + b;
}
```

---
# Function overloading

You can have multiple functions with the **same
name** but **different arguments**.
```C++
int sum(int a, int b) {
  return a + b;
}
double sum(double a, double b) {
  return a + b;
}
```

When you call `sum`, the compiler knows the types of the arguments and
will try to find the best match from all the candidates with the name.

The compiler will also try to use any built-in or user-defined
conversion rules.

---

# What happens here?
```C++
int i1 = 1;
int i2 = 2;
double d1 = 1.0;
double d2 = 2.0;
unsigned u42 = 42;

std::cout << sum(i1, i2) << std::endl;
std::cout << sum(3, 72) << std::endl;
std::cout << sum(i1, u42) << std::endl;
std::cout << sum(d2, d1) << std::endl;
std::cout << sum(d2, i1) << std::endl;
std::cout << sum(d2, 1.0f) << std::endl;
```
---

# Operators are functions

C++ operators, for the non-fundamental types, are just functions with odd
names, e.g.:
```C++
Complex operator+(const Complex&, const Complex&);
```

You can then use the natural syntax when manipulating these in other
code:

```C++
Vector c = a + b;
```

We'll come back to this.


