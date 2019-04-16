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
  // Copy c'tor - the new Array will share the same data as the input
  Array(const Array& other) = default;
  // Move c'tor - the new Array will steal the reference from the input
  Array(Array&& other) = default;
  // D'tor - will release if last owner
  ~Array() = default;

  // Copy assignment - frees any current references and then shares
  // data with other
  Array& operator=(const Array& other) = default;
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
  std::shared_ptr<double[]> _data;
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
