template: titleslide
# Templates and auto
## Rupert Nash
## r.nash@epcc.ed.ac.uk

---
# Templates 101

Templates are a method of doing *metaprogramming*: a
program that writes a program.

An easy example:

```C++
int sum(int a, int b) {
  return a+b;
}
double sum(double a, double b) {
  return a+b;
}
```

What if we need this for `float` and `unsigned`?

Going to get boring and hard to maintain quickly!

---
# Templates 101

```C++
template<typename T>
T sum(T a, T b) {
  return a+b;
}
```

When you use it later, the compiler will substitute the types you supply
for `T` and then try to compile the template.

```C++
std::cout << "add unsigned=" << sum(1U, 4U) << endl;
std::cout << "add floats=" << sum(1.0f, 4e-2f) << endl;
```

---

# Template classes

You can define a template class - i.e. a template that will produce a
class when you instatiate it.

Let's extend our `Array` type to hold any type instead of just `double`s

```C++
template<class T>
class Array {
  unsigned _size;
  T* _data;
public:
  Array();
  Array(unsigned n);
  ~Array();
  unsigned size() const;
  const T& operator[](unsigned i) const;
  T& operator[](unsigned i);
};
```

---

# Where to put your implementation?

Templates are *not* executable code - they tell the compiler how to
create it.

So the definition must be available to the user of your template -
i.e. typically in a header file.

You can define the functions in place like:

```C++
template<class T>
class Array {
public:
  Array() : _size(0), _data(nullptr) {}
};
```

Or at the end of the header (or equivalently in another file that you
include at the end of your header)

```C++
template<class T>
Array<T>::Array(unsigned n) : _size(n) {
  _data = new T[n];
}
```


---
# Templates and type deduction

Recall:
```C++
template<class T>
T sum(T a, T b) {
  return a+b;
}
```

We then used this without specifying, explicitly, what type `T` was - e.g.:
```C++
int x = 1, y = 2;
auto z = sum(x, y);
```

The compiler is doing template argument deduction.

This means it examines the types of the expressions given as arguments
to the function and then tries to choose a `T` such that the type of
the argument and the expected type match.

---
# Templates and type deduction

Important to note that the template parameter `T` and the type of
function arguments might be different (but related)

```C++
template<class T>
void f(T x);

template<class T>
void g(T& x);

template<class T>
void h(const T& x);
```

---
# Templates and type deduction

Full rules are quite complex

See Meyer's Effective Modern C++ chapter 1 - free online
https://www.safaribooksonline.com/library/view/effective-modern-c/9781491908419/ch01.html


![:thumb]( But usually you can ignore these and just think about:
1. Whether you want to copy the argument or not  - if you don't want a
copy add a reference `&`
2. Whether you can handle a const argument - if so add a `const` qualifier)

---
# Auto

The `auto` keyword follows very nearly the same rules as template
argument deduction but can trip you up more easily. :(

Even more important to express your intent:

- Use `auto x` when you want to copy

- Use `auto &x` when you want a reference to original item and may
  modify it

- Use `auto const &x` when you want a reference to original item and
  will not modify it

![:thumb](Use the last whenever possible)

