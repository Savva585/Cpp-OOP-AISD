#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include <random>
#include <algorithm>


using namespace std;

template <typename T>
class polynomial {
  size_t _degree;
  size_t _capacity;
  T* _vector;
  inline static const double _epsilon = 0.001;
public:
  polynomial() = delete;

  polynomial(const size_t degree) : _degree(degree), _capacity(degree+5) {
    _vector = new T[_capacity];
    for (size_t i = 0;i < _capacity;++i) {
      _vector[i] = T(0);
    }

  }
  size_t degree() const {
    return _degree;
  }
  polynomial(T* coefficients, size_t degree) :  _degree(degree), _capacity(degree + 5) {
    _vector = new T[_capacity];
    for (size_t i = 0; i < _degree; ++i) {
      _vector[i] = coefficients[i];
    }
    for (size_t i = _degree;i < _capacity;++i) {
      _vector[i] = T(0);
    }
  }

  polynomial(size_t degree, T start, T end) : _capacity(degree + 10), _degree(degree){
    _vector = new T[_capacity];
    random_device device;
    uniform_real_distribution distr(std::min(start, end), std::max(start, end));

    for (size_t i = 0; i < _degree; i++)
    {
      _vector[i] = static_cast<T>(distr(device));
    }

  }

  polynomial(polynomial<T>& object) {
    _degree = object._degree;
    _capacity = object._capacity;
    _vector = new T[_capacity];
    for (size_t i = 0; i < _degree; ++i) {
      _vector[i] = object._vector[i];
    }
  }

  ~polynomial() {
    delete[] _vector;
  }

  T& operator[](size_t i) const {
    if (i > _degree) {
      throw std::out_of_range(
        "Error:  " + std::to_string(i) + ">" +std::to_string(_degree) + ".\n" );
    }
    return _vector[i];
  }
  void expand(const size_t degree) {
    if (_capacity > degree)
    {
      return;
    }
    _capacity = degree + 5;
    T* new_vector = new T[_capacity];
    for (size_t i = 0; i < _degree; ++i) {
      new_vector[i] = _vector[i];
    }
    for (size_t i = _degree;i < _capacity;++i) {
      new_vector[i] = T(0);
    }
    delete[] _vector;
    _vector = new_vector;
  }

  void set(const size_t degree, const T& coeff) {
    if (degree > _capacity) {
      this->expand(degree);
    }
    _vector[degree] = coeff;
  }

  polynomial<T>& operator+=(const polynomial<T>& second_poly) {
    if (_degree < second_poly._degree) {
      this->expand(second_poly._degree+1);
      _degree = second_poly._degree;
    }
    for (size_t i = 0;i < _degree;++i) {
      _vector[i] += second_poly._vector[i];
    }
    return *this;
  }

  polynomial<T>& operator+(polynomial<T>& second_poly) {
    second_poly += *this;
    return second_poly;
  }

  polynomial<T>& operator-=(const polynomial<T>& second_poly) {
    if (_degree < second_poly._degree) {
      this->expand(second_poly._degree + 1);
      _degree = second_poly._degree;
    }
    for (size_t i = 0;i < _degree;++i) {
      _vector[i] -= second_poly._vector[i];
    }
    return *this;
  }

  polynomial<T>& operator-(polynomial<T>& second_poly) {
    second_poly -= *this;
    return second_poly;
  }

  polynomial<T>& operator*=(const T& scalar) {
    for (size_t i = 0;i < _degree;++i) {
      _vector[i] *= scalar;
    }
    return *this;
  }

  polynomial<T> operator*( T scalar) {
    polynomial<T> new_poly = *this;
    new_poly *= scalar;
    return new_poly;
  }
  friend polynomial<T> operator*(const T scalar, polynomial<T>& poly)
  {
    return poly * scalar;
  }

  bool operator==(const polynomial<T>& second_poly) {
    if (_degree != second_poly._degree) {
      return false;
    }
    for (size_t i = 0;i < _degree;++i) {
      double diff = abs(static_cast<double>(_vector[i]) - static_cast<double>(second_poly._vector[i]));
      if (diff >= _epsilon) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const polynomial<T>& second_poly) {
    return !(second_poly == *this);
  }

  bool operator>(const polynomial<T>& second_poly) {
    return _degree>second_poly._degree;
  }

  bool operator<(const polynomial<T>& second_poly) {
    return _degree < second_poly._degree;
  }

  T& calculation(T& x) {
    T answer=T(0);
    for (size_t i = 0;i < _degree;++i) {
      answer += _vector[i] * (pow(x, i));
    }
    return answer;
  }
  void shrink_to_fit() {
    size_t degree = _capacity;
    while (!_vector[degree--]) {}
    T* new_vector = new T[degree];
    for (size_t i = 0; i < degree; i++)
    {
      new_vector[i] = _vector[i];
    }
    delete[] _vector;
    _vector = new_vector;
  }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const polynomial<T>& p)
{
  for (size_t i = 0; i < p.degree() - 1; i++)
  {
    os << p[i] << "*x^" << i << " + ";
  }
  os << p[p.degree() - 1] << "*x^" << p.degree() - 1 << "\n";
  return os;
}
template<>
bool polynomial<std::complex<float> >::operator==(const polynomial<std::complex<float> >& second_poly){
  if (_degree != second_poly._degree) {
    return false;
  }
  for (size_t i = 0;i < _degree;++i) {
    double first_dif = abs(_vector[i].real() - second_poly._vector[i].real());
    double second_dif = abs(_vector[i].imag() - second_poly._vector[i].imag());
    if (first_dif > _epsilon || second_dif > _epsilon) {
      return false;
    }
  }
  return true;
}

template<>
bool polynomial<std::complex<double> >::operator==(const polynomial<std::complex<double> >& second_poly) {
  if (_degree != second_poly._degree) {
    return false;
  }
  for (size_t i = 0;i < _degree;++i) {
    double first_dif = abs(_vector[i].real() - second_poly._vector[i].real());
    double second_dif = abs(_vector[i].imag() - second_poly._vector[i].imag());
    if (first_dif > _epsilon || second_dif > _epsilon) {
      return false;
    }
  }
  return true;
}

template <>
inline polynomial<int>::polynomial(size_t degree, int start,int end) : _capacity(degree + 10), _degree(degree)
{
  _vector = new int[_capacity];
  random_device device;
  uniform_int_distribution distr_re(min(start,end),max(start,end));

  for (size_t i = 0; i < _degree; i++)
  {
    _vector[i] = distr_re(device);
  }

}

template <>
inline polynomial<complex<float> >::polynomial(size_t degree, complex<float> start, complex<float> end) : _capacity(degree + 10), _degree(degree)
{
  _vector = new complex<float>[_capacity];
  random_device device;
  uniform_real_distribution distr_re(min(start.real(), end.real()), max(start.real(), end.real()));
  uniform_real_distribution distr_im(min(start.imag(), end.imag()), max(start.imag(), end.imag()));

  for (size_t i = 0; i < _degree; i++)
  {
    _vector[i] = complex<float>(distr_re(device), distr_im(device));
  }

}
template <>
inline polynomial<complex<double> >::polynomial(size_t degree, complex<double> start, complex<double> end) : _capacity(degree + 10), _degree(degree)
{
  _vector = new complex<double>[_capacity];
  random_device device;
  uniform_real_distribution distr_re(min(start.real(), end.real()), max(start.real(), end.real()));
  uniform_real_distribution distr_im(min(start.imag(), end.imag()), max(start.imag(), end.imag()));

  for (size_t i = 0; i < _degree; i++)
  {
    _vector[i] = complex<double>(distr_re(device), distr_im(device));
  }

}

template<typename T>
polynomial<T> indefinite_integral(const polynomial<T>& object) {
  polynomial<T> buffer(object.degree() + 1); 
  buffer.set(0, T(0));
  for (int i = 0; i < object.degree() + 1; ++i){
    T value= object[i];
    buffer[i + 1] =  value* (1.0 / (i + 1));
  }

  return buffer;
}

int main() {
  double example_first[] = { 1.2,2.5,3.5,8 };
  double x = 7;
  polynomial<double> p(4, 1.2, 7);
  polynomial<double> p1(example_first,4);
  cout << "First: " << p << "Second: " << p1 << "Sum: ";
  cout<<p + p1 << '\n' << "Diff: " << p1 - p << '\n';
  cout <<"\nSum[0]: "<< p1[0];
  cout << "\nCalcul: " << p.calculation(x);
  cout << "\nIntegr: " << indefinite_integral(p);
}
