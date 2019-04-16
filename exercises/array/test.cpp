#include <cassert>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "Array.hpp"
#include "util.hpp"

// Exercise 2.1 - array

// This program tests your array implementation by generating some
// random data and inserting it into a list, keeping it sorted.  It
// needs one command line argument, an integer, which is the number of
// elements to generate.  It will check they are indeed sorted and
// print the time it took.

// I have provided a partial implemenation (Array.h / Array.cpp)


int main(int argc, char** argv) {
  
  // Requires one argument, the size of the list to generate
  assert(argc == 2);
  int size = std::atoi(argv[1]);
  
  // We are going to fill this list with some random integers
  Array data(size);
  
  // Measure the time
  Timer t;
  for (unsigned i = 0; i != size; ++i) {
    // Get a random in [0,1000]
    auto x = rand(1000);
    
    // find insertion point
    auto j = std::lower_bound(&data[0], &data[0]+i, x) - &data[0];
    
    // Shift all elements [j, i) up one (starting at the back to avoid
    // overwriting
    std::copy_backward(&data[j], &data[i], &data[i+1]);
    // Add the new value
    data[j] = x;
  }
  
  std::cout << "Time to store " << size << " integers = " << t.GetSeconds() << " s" << std::endl;
  
  // Check they are ordered
  // Note starting from 1 and less-than to avoid len(data)==0 bug
  for(unsigned i = 1; i < data.size(); ++i) {
    assert(data[i-1] <= data[i]);
  }
  std::cout << "Were correctly ordered" << std::endl;

  return 0;
}
