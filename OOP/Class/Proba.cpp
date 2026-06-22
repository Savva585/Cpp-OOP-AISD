#include<iostream>
#include<cmath>
#include <vector>
#include <format>

using namespace std;
class Point {
private:
  double _x = 0.0;
  double _y = 0.0;
public:
  Point(double x,double y) {
    _x = x;
    _y = y;
  }
  double Xvershina(Point po) const {
    return _x;
  }
  double Yvershina(Point po) const {
    return _y;
  }
  void Reset() {
    _x = 0.0;
    _y = 0.0;
  }
};
//ostream& operator<<(ostream& stream, const Point& p) {
//  stream << format("{} {}", p.x, p.y);
//  return stream;
//}

class Matrix {
public:
  Matrix(size_t rows, size_t cols) :
    _data(rows* cols),
    _rows(rows),
    _cols(cols)
  {
  }

  size_t rows() const {
    return _rows;
  }

  size_t cols() const {
    return _cols;
  }

  float get_value(size_t row, size_t col) const {
    return _data[row * _cols + col];
  }

  void set_value(size_t row, size_t col, float value) {
    _data[row * _cols + col] = value;
  }

private:
  vector<float> _data;
  size_t _rows;
  size_t _cols;
};

Matrix operator +=(const Matrix& lhs, const Matrix& rhs) {
  const size_t rows = lhs.rows();
  const size_t cols = lhs.cols();

  if (rows != rhs.rows() || cols != rhs.cols()) {
    // Пока что так, но по-хорошему надо генерировать исключение
    Matrix empty(0, 0);
    return empty;
  }

  Matrix r(rows, cols);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      const float value = lhs.get_value(i, j) + rhs.get_value(i, j);
      r.set_value(i, j, value);
    }
  }

  return r;
}

void print(const Matrix& m) {
  for (size_t i = 0; i < m.rows(); ++i) {
    for (size_t j = 0; j < m.cols(); ++j) {
      cout << m.get_value(i, j) << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}
int main() {
  Point T(3,4);
  cout << T.Xvershina(T) << " " << T.Yvershina(T) << "\n";
}
