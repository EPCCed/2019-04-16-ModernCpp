#include <cstdio>

// Compute the n'th Fibonacci number defined by
//   fib(0) == 0
//   fib(1) == 1
//   fib(n) == fib(n-1) + fib(n-2)
// See also: https://en.wikipedia.org/wiki/Fibonacci_number
int fib(int n) {
  if (n == 0)
    return 0;
  // Handle later terms in the series

}

int fib_recursive(int n) {
}

int main(int argc, char* argv[]) {
  for (int i = 0; i < 10; ++i) {
    std::printf("fib(%d) = %d\n", i, fib(i));
  }
}
