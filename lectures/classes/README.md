template: titleslide
# Classes in C++
## Rupert Nash, EPCC
## r.nash@epcc.ed.ac.uk

---
template: titleslide
# Preliminary concepts

---
# Const-ness

Types can be qualified with the `const` keyword

- objects marked with `const` cannot be modified

- compiler will give errors if you try 

```C++
struct Foo {
 const int i;
};

int main() {
  Foo foo{42};
  std::cout << foo.i << std::endl;
  // prints 42

  foo.i += 10;
  // compiler error
}
```

---
# References

C++ has the concept of a *reference*.

- A reference is variable that aliases an already existing object.

- A reference must but initialised (function arguments are initialised
  by calling)


```C++
int main() {
  double& x = GetElementFromArray(i);
  x *= 10;
  std::cout << GetElementFromArray(i) << std::endl;
}
```

---
# References and Const

You can have a reference to const:

```C++
double Sum(const BigArray& data) {
  double ans = 0;
  for (const double& x: data)
    ans += x;

  return ans;
}
```

---
# References: whys and whens

References have simpler syntax than pointers

References are safer than pointers: a reference cannot be null and
cannot be reseated (must be bound when it's defined)

```C++
double pi = 3.14;
double& pr = pi;
double twopi = 6.24;
pr = twopi; \\ Error will not compile
```

And you can rely on it being valid, unless there is an evil coder
around:
```C++
char& get() {
  char x = '!';
  return x;
  // Many compilers will warn about this
}
```

Use a reference by default, until you need a pointer. (E.g. need to
reseat or interface with C.)

---
template:titleslide
# Classes

---
# Classes and structs

You define a class using either the `struct` or `class` keywords -
technically the difference is only the default visibility of members.

As well as *data members*, instantiations of classes (i.e. objects) can
have *member functions*.

```C++
struct Complex {
  double magnitude() const;
  Complex& operator+(const Complex&);

  double real;
  double imag;
};
```

---
# Member functions

Typically these are declared in the class definition and defined out of line:

```C++
double Complex::magnitude() const {
  return std::sqrt(real*real + imag*imag);
}
```
-   The `const` at the end of the declaration says that this function
    will not alter the instance it is working on. Add this whenever
    possible!

-   We can access the members by just giving their names.

-   The instance that the function is working on is also available as a
    pointer, called `this`, so could rewrite as:

```C++
double Complex::magnitude() const {
  return sqrt(this->real*this->real + this->imag*this->imag);
}
```

---
# Member functions

```C++
Complex& Complex::operator+=(const Complex& increment) {
  real += increment.real;
  imag += increment.imag;
  return *this;
}
```

- The `const` on the argument means that this function will not modify it.

- We return a reference to the updated object

---
# Creating instances 

Often you want to control the creation of instances of your classes.

You do this with _constructors_ - these are special member functions
with the same name as the class

```C++
struct Complex {
  Complex();
  Complex(double re, double im);
  Complex(const Complex&) = default;

  double real;
  double imag;
};
```

Note we provide three overloads:
- a *default constructor* which needs no arguments
- one that initialises with a value.
- tell the compiler to create a *default copy constructor* for us.

---
# Constructors

- Constructors are not directy callable
- Constructors do not return a value
- Constructors can do initialisation of member variables before the body begins execution


```C++
// Default c'tor
Complex::Complex() : real(0), imag(0) {
}

// Value c'tor
Complex::Complex(double re, double im) : real(re), imag(im) {
}

// Explicitly defaulted copy c'tor
// This is roughly what the compiler will create for us
// Complex::Complex(const Complex& c) :
//   real(c.real), imag(c.imag) {
// }
```

---
# Creating complexes

We can now create complex numbers different ways
```C++
Complex zero;
Complex sqrt_minus_one{0, 1};
Complex copy_of_i{imaginary_unit};
```

---
# More on operator overloading

Complex numbers have the usual arithmetic operations: `\(+-\times\div\)`

We have to provide operator overloads, like:

```C++
Complex operator+(const Complex& a, const Complex& b) {
  return Complex{a.real+b.real, a.imag+b.imag};
}
```

This is just a function (with an unusual name) that takes two complex
numbers and returns one.


---
template: titleslide
# Declaration and Definition

---
# Declarations vs Definitions

C++ distinguishes between *declaration* and *definition*.

A **declaration** tells the compiler that a name exists, what kind of
entity it refers to and its type. For most uses this is all the compiler
needs. Declarations can be repeated, as long as they match *exactly*.

A **definition** tells the compiler everything it needs to create
something in its entirety. A definition is also a declaration. The
one-definition rule says that definitions must not be repeated (with
an exception).

---
# Examples

.columns[
.col[
**Declaration**
```C++
extern int foo;
int GetAnswer();
struct Point;
```
]
.col[
**Definition**
```C++
int foo;
// Or
int foo = 0;
int GetAnswer() {
  return 42;
}
struct Point {
  float x;
  float y;
};
```
]
]

---
# Where to put these

Conventionally, one puts declarations in a header file (.h suffix) and
defintions in implementation files (.cpp suffix).

Headers can be be included into other files that need to use the types
and function declared there.

---
# Where to put these

E.g. Complex.h:

```C++
#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex {
  Complex();
  Complex(double re, double im);
  Complex(const Complex&) = default;
  // etc...
  double real;
  double imag;
};

Complex operator+(const Complex& a, const Complex& b);
// Etc...

#endif
```

---
# Where to put these

E.g. Complex.cpp

```C++
#include "Complex.h"
#include <cmath>

// Default c'tor
Complex::Complex() : real(0), imag(0) {
}
// Value c'tor
Complex::Complex(double re, double im) : real(re), imag(im) {
}

Complex operator+(const Complex& a, const Complex& b) {
  return Complex{a.real+b.real, a.imag+b.imag};
}

double Complex::magnitude() const {
  return std::sqrt(real*real + imag*imag);
}
```

---
# Destructors

You can also control what happens when your objects reach the end of
their lifetime - typically releasing any resources that are owned by
the object.

For a class `Name` they are declared like:

```C++
struct Name {
  ~Name();
};
```

It's important to note that you should **never call this directly** -
the compiler will call it for you when your objects are deallocated.

So far we have not seen anything that would need this - let's
introduce a resource to you.

---
template: titleslide
# Memory and pointers

---
# Pointers

C++ inherits the concept of pointers from C

A pointer is just a number - it specifies the memory address of an object.

You declare one by qualifying a type with `*`:

```C++
double* data = nullptr;
```

Here we are using the special keyword `nullptr` which indicates that the pointer is invalid.

---
# Dereferencing pointers

To get the value that is pointed to, you "dereference" the pointer with `operator*`;

```C++
void double_in_place(int n, double* data) {
  for (int i=0; i < n; ++i) {
    *data *= 2.0;
  }
}
```

---
# Dynamic memory - allocation

You can dynamically allocate memory using the `new` operator.

```C++
double* x = new double;

Complex* z = new Complex{0, 1};
```

The runtime gets enough memory to store an object of that type (from
the OS) an then calls the constructor for you to initialise the
memory.

You can also allocate an array of objects:

```C++
int n = 100;
double* data = new double[n];
```

This gets enough memory to store `n` objects and initialises each one (which may be a no-op).

---
# Dynamic memory - deallocation

You the programmer are responsible for telling the runtime when you
are finished with dynamically allocated memory.

Do this with the `delete` operator:

```C++
delete x;
delete z;
```

Dereferencing the pointer after deleting it is undefined behaviour - typically a crash or corrupted values.

Slightly different for arrays - you must use the `delete[]` operator:
```C++
delete[] data;
```

---
# A note for C programmers

![:thumb](Do not mix `malloc` and `free` with `new` and `delete`)

The `malloc`/`free` pair do not understand constructors and
destructors and so will not work with class types that use this
behaviour.

![:thumb](In general, you should not use `malloc` and `free` in modern C++)

---
template: titleslide
## Now you should (almost) never use these

---
# Resource allocation is instantiation

A very important pattern in C++ is **RAII**: resource allocation is
instantiation.

Also known as constructor acquires, destructor releases (CADRe).

This odd name is trying to communicate that any resource you have
should be tied to the lifetime of an object.

So the when the compiler destroys your object it will release the
resource (e.g. memory).

---
# Example: An array class

Let's build something almost useful, like a simple array class.

```C++
class Array {
  unsigned size_;
  double* data_;
public:
  Array();
  Array(unsigned n);
  ~Array();
  unsigned size() const;
  const double& operator[](unsigned i) const;
  double& operator[](unsigned i);
};
```

---
# Example: An array class

Constructors:
```C++
Array::Array() : size_(0), data_(nullptr) {
}

Array::Array(unsigned n) : size__(n) {
  data_ = new double[n];
}
```

Destructor:
```C++
Array::~Array() {
  delete[] data_;
}
```

---
# Example: An array class

Example use:

```C++
void do_simulation(Parameters& p) {
  Array work_array(p.problemsize_);
  initial_condition(work_array);
  for(int i=0; i < p.timesteps; ++i) {
    do_timestep(work_array);
  }
  write_output(p.outfile, work_array);
}
```

The explicit memory management is encapsulated by the `Array` type
and, since the language rules require that the destructor be called
when `work_array` goes out of scope, the memory is freed when the
function returns.

---
template: titleslide
# Copying and Moving

---
# Copy vs move

When you assign a variable, call a function/constructor, or return a
value from a function, you are conceptually copying or moving.

For the fundamental types like `int`, copying is the same as moving
and simple: you end up with the source and destination objects holding
the same pattern of bits.

But for more complex types such as our `Array` you might want different semantics.

---
# Two ways to copy

C++ has two ways to copy a value:

1. Copy assignment:
```C++
void foo(Array& dest, const Array& src) {
  dest = src;
}
```

2. Copy construction:
```C++
void bar(const Array& src) {
  Array local = src;
  // do something with local
}
```

(The distinction is because in the assignment case you may need to release some resources)

---
# Naive `Array` copy

Let's define copying of `Array` objects to be simple copying of the data members:
```C++
class Array {
  unsigned size_;
  double* data_;
public:
  Array(const Array& other) : size_(other.size_), data_(other.data_) {
  }
  Array& operator=(const Array& other) {
    size_ = other.size_;
    data_ = other.data_;
  }
};
```

(Note: could have just written:
```C++
  Array(const Array& other) = default;
  Array& operator=(const Array& other) = default;
```
and the compiler would have generated simple member-wise copies for us.)

---
# Naive `Array` copy

```C++
void function(unsigned n) {
  Array x{n};
  Array y{x};
  y[0] = 0.999;

}
```

- What is the value of `x[0]`?

- What happens when the function returns?

---
# Array deep copy

```C++
class Array {
  unsigned size_;
  double* data_;
public:
  Array(const Array& other) : Array(other.size_) {
    std::memcpy(data_, other.data_, size_);
  }
  Array& operator=(const Array& other) {
    size_ = other.size_;
    delete[] data_;
	data_ = new double[other.size_];
    std::memcpy(data_, other.data_, size_);
  }
};
```

---
# Using the deep copy

```C++
void function(unsigned n) {
  Array x{n};
  Array y{x}; // This now does an allocation and memcpy
  y[0] = 0.999;
}
```

However this will now do an expensive allocation and copy operation
implicitly when our intuition says assignment is cheap.

---
# Deleting operations

We could instead declare the copy constructor and assignment operator
to be deleted:

```C++
class Array {
  unsigned size_;
  double* data_;
public:
  Array(const Array& other) = delete;
  Array& operator=(const Array& other) = delete;

  Array copy() const {
    Array ans(size_);
    std::memcpy(ans.data_, data_, size_);
	return ans;
  }
};
```

While providing an explicit `copy` member function to do the expensive operation of deep copying.

---
# Moving

Since C++11, the language has supported the concept of *moving* from
objects which the compiler knows (or the programmer asserts) will not
be used any more.

Examples are:
- temporaries (i.e. the result of a function call)
- automatic variables that are going out of scope
- the result of calling `std::move` on an object

The destination object "steals" the contained resources from the
source object and sets the source to a valid but undefined state -
typically the only operations you can perform on a moved-from object
are destruction and assignment.

---
# Moveable Array

```C++
class Array {
  unsigned size_;
  double* data_;
public:
  Array(Array&& other) : size_(other.size_), data_(other.data_) {
    other.data_ = nullptr;
    other.size_ = 0;
  }
  Array& operator=(const Array& other) {
    std::swap(size_, other.size_);
	std::swap(data_, other.data_);
  }
};
```

The double ampersand indicates an "r-value reference".

The compiler will only use this when the argument is a temporary value
that is going to be destructed - you can safely take ownership of its resources.

---
# The Rule of Five

This says that if you define or delete one of the following:
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator
- destructor

then you should probably do so for all five.

---
# The Rule of Zero

This suggests that unless your class is dealing with ownership then it
should define none of the five special functions.

This is really a corollary of the principle of single responsibility:
you should split your class into a resource manager with all five
functions and a user class that has none.

---
template: titleslide

# Object oriented C++
---

# OOP

Object oriented programming is one of the major paradigms supported by
C++

> OOP is based on the concept of "objects", which may contain data and
> code. A feature of objects is that an object's procedures can access
> and often modify the data of the object with which they are
> associated.

Last time we briefly covered how to create classes - here we'll go a
little deeper.

---

# Inheritance

-   Inheritance is a method for deriving a new, related class from
    another one (called the base class, parent class, or super class).

-   This relationship says that the derived object also *is* an object
    of the base class too!

-   The new class (derived, child, sub) has all the data and function
    members of its parent, but you can add new ones and *override*
    existing ones.

-   The derived class member functions can access the base class members
    that are public, but not the private ones. There is a third access
    specifier `protected` that allows derived classes to access the
    member.

-   It's use should be minimal as you are promising to all subclasses
    that this interface will not change!
---

# Inheritance

Suppose you had to process a lot of image files. You might start with
a JPEG file:

```C++
class JpegFile {
  string _fn;
  int _nx, _ny;
  unique_ptr<char> _pixeldata;
public:
  JpegFile(string fn) : _fn(fn) {
	 // read _nx/_ny/_ncols from header
	_pixeldata = new char[_nx*_ny*3];
	// decompress data from file
  }
  char& GetPixel(int x, int y) {
	return _pixeldata[x*_ny + y];
  }
};
```
---

# Inheritance

But then you have to add PNG, and GIF, and \...

Might want to do the same for each one, but:

-   code duplication :(

-   the types are totally unrelated :(
---

# Inheritance

So instead create a base class and several derived classes

```C++
class ImageFile {
  string _fn;
protected:
  int _nx;
  int _ny;
  unique_ptr<char> _pixeldata;
public:
  ImageFile(string fn);
  char& GetPixel(int x, int y);
};
```

---

# Inheritance

So instead create a base class and several derived classes
```C++
class JpegFile : public ImageFile {
public:
  JpegFile(string fn) : ImageFile(fn) {
	// read _nx/_ny/_ncols from header
	_pixeldata = new char[_nx*_ny*3];
	// decompress data from file
  }
};

class PngFile : public ImageFile {
public:
  PngFile(string fn);
};
```

---

# Pointers to base class

One important thing to know is that a pointer to a derived class
(`JpegFile*`) is *type compatible* with a pointer to the base class
(`ImageFile*`).

```C++
JpegFile jpg("cat.jpg");
ImageFile* img = &jpg;
// also works with references
ImageFile& im_ref = jpg;
```
---

# Dynamic polymorphism

-   What if we have some behaviour, like writing the image data to file,
    that varies between the subclasses?

-   We ideally want to have a uniform interface and when we call it as
    run time the pointer-to-base knows which subclass method to call.

-   Enter virtual functions!

---

# Dynamic polymorphism
```C++
class ImageFile {
public:
 virtual void Write(string fn} = 0;
};

class JpegFile : public ImageFile {
public:
	virtual void Write(string fn) {
	  // write header
	  // compress + write data
	}
};
ImageFile* img = new JpegFile("cat.jpg");
img->Write("notdog.jpg");
```

---

# How does this work?

-   Through a virtual function table.

-   Each class has a static table of function pointers that point to the
    code of its virtual functions.

-   Each instance of the class has a pointer to the table that belongs
    to its actual class (filled in by the compiler in the constructor).

-   To call, the object's "vtable" pointer is followed, the offset for
    the method added, and the function called by pointer. Clearly slower
    than a simple function call by compile-time constant! Worse it make
    inlining of the function impossible.

-   You really don't want to use virtual functions in an inner loop!
	(By all means use them outside!)
