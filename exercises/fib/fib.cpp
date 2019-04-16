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
  if (n == 1)
    return 1;
  int last1 = 1;
  int last2 = 0;
  int ans = last1 + last2;

  for (int i = 2; i < n; ++i) {
    last2 = last1;
    last1 = ans;
    ans = last1 + last2;
  }
  return ans;
}

int fib_recursive(int n) {
  return n < 2 ? n : fib(n-1) + fib(n-2);
}

int main(int argc, char* argv[]) {
  for (int i = 0; i < 10; ++i) {
    std::printf("fib(%d) = %d\n", i, fib(i));
  }
}
