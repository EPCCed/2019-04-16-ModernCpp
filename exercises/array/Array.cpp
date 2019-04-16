#include "Array.hpp"

// C'tor
Array::Array(unsigned n) : _size(n) {
  _data = new double[n];
}

// Copy c'tor
Array::Array(const Array& other) : Array(other._size) {
  std::copy(other._data, other._data + _size,
	    _data);
}

// Move c'tor
Array::Array(Array&& other) : Array() {
  std::swap(_size, other._size);
  std::swap(_data, other._data);
}

// D'tor
Array::~Array() {
  delete[] _data;
}

// Copy assignment
auto Array::operator=(const Array& other) -> Array& {
  _size = other._size;
  delete[] _data;
  _data = new double[_size];
  std::copy(other._data, other._data + _size,
	    _data);
  return *this;
}

// Move assignment
auto Array::operator=(Array&& other) -> Array& {
  std::swap(_size, other._size);
  std::swap(_data, other._data);
  return *this;
}

// Const element access
const double& Array::operator[](unsigned i) const {
  return _data[i];
}

// Non-const element access
double& Array::operator[](unsigned i) {
  return _data[i];
}
