#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>

class Array {
public:
  // C'tor - contains no data
  Array() : _size(0), _data() {
    // Nothing else to do
  }
  // C'tor - has the space for n elements
  Array(unsigned n);
  // Copy c'tor - NOT ALLOWED
  // This is not strictly necessary as the default copy c'tor is
  // invalid but it explicitly tells the user (maybe you later!) that
  // this is the case!
  Array(const Array& other) = delete;
  
  // Move c'tor - the new Array will steal the data from the input
  Array(Array&& other) = default;
  // D'tor - releases contained resources
  ~Array() = default;

  // Copy assignment - NOT ALLOWED
  Array& operator=(const Array& other) = delete;
  // Move assignment - frees any current resources and steals data
  // from the input
  Array& operator=(Array&& other) = default;

  // Return the number of elements in the Array
  unsigned size() const {
    return _size;
  }

  // Const element access
  const double& operator[](unsigned i) const;
  // Mutable element access
  double& operator[](unsigned i);

private:
  unsigned _size;
  std::unique_ptr<double[]> _data;
};

// C'tor
Array::Array(unsigned n) : _size(n), _data(new double[n]) {
}

// Const element access
const double& Array::operator[](unsigned i) const {
  return _data[i];
}

// Non-const element access
double& Array::operator[](unsigned i) {
  return _data[i];
}

#endif
