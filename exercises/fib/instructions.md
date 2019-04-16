# Fibonacci numbers

In this exercise you will write a function to compute the n'th Fibonacci number defined by:

```C++
fib(0) == 0
fib(1) == 1
fib(n) == fib(n-1) + fib(n-2)
```

See also: <https://en.wikipedia.org/wiki/Fibonacci_number>

Open the source code in your preferred editor and complete the implementation of the function `fib`.

## Compile with make

You can compile the code with make

```
$ make
c++ --std=c++11    fib.cpp   -o fib
fib.cpp:8:1: warning: control may reach end of non-void function [-Wreturn-type]
}
^
fib.cpp:11:1: warning: control reaches end of non-void function [-Wreturn-type]
}
^
2 warnings generated.
```

The warnings should disappear when you have a solution.

## Run the code

The Makefile will produce an executable called `fib`, run it and it should print the first 10 Fibonacci numbers

```
$ ./fib 
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
fib(6) = 8
fib(7) = 13
fib(8) = 21
fib(9) = 34
```

## Bonus

Can you write the function in a recursive style?


