#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>

class Array {
public:
  // C'tor - contains no data
  Array() : _size(0), _data(nullptr) {
    // Nothing else to do
  }
  // C'tor - has the space for n elements
  Array(unsigned n);
  // Copy c'tor - the new Array will have the same data as the input
  Array(const Array& other);
  // Move c'tor - the new Array will steal the data from the input
  Array(Array&& other);
  // D'tor - releases contained resources
  ~Array();

  // Copy assignment - frees any current resources and then copies
  // from input
  Array& operator=(const Array& other);
  // Move assignment - frees any current resources and steals data
  // from the input
  Array& operator=(Array&& other);

  // Return the number of elements in the Array
  inline unsigned size() const {
    return _size;
  }

  // Const element access
  const double& operator[](unsigned i) const;
  // Mutable element access
  double& operator[](unsigned i);

private:
  unsigned _size;
  double* _data;
};

#endif	// Include guard
