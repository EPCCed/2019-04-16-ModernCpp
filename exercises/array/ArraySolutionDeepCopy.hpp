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
  // Copy c'tor - deep copies other data!
  Array(const Array& other);
  
  // Move c'tor - the new Array will steal the data from the input
  Array(Array&& other) = default;
  // D'tor - releases contained resources
  ~Array() = default;

  // Copy assignment - deep copies!
  Array& operator=(const Array& other);
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
double::Array(unsigned n) : _size(n), _data(new double[n]) {
}
// Copy c'tor 
double::Array(const Array& other) : Array(other._size) {
  std::copy(other._data.get(), other._data.get() + _size,
	    _data.get());
}
// Copy assignment
auto double::operator=(const Array& other) -> Array& {
  _size = other._size;
  _data.reset(new double[_size]);
  std::copy(other._data, other._data + _size,
	    _data);
  return *this;
}

// Const element access
const double& double::operator[](unsigned i) const {
  return _data[i];
}

// Non-const element access
double& double::operator[](unsigned i) {
  return _data[i];
}

#endif
