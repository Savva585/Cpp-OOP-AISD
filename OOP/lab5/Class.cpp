#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
#include"Class.h"
using namespace std;
float Point::XTop() const {
  return _x;
}
float Point::YTop() const {
  return _y;
}
void Point::Reset() {
  _x = 0.0;
  _y = 0.0;
}
float Line::lenghtX_line() {
  float lenght = 0.0;
  float lenX = 0.0;
  float lenY = 0.0;
  if (lenX == 0) {
    lenX = _A.XTop() - _B.XTop();
  }
  return lenX;
}
float Line::lenghtY_line() {
  float lenY = 0.0;
  lenY = _A.YTop() - _B.YTop();
  return lenY;
}
float Line::Lenght_line(Line AB) {
  float lenX = AB.lenghtX_line();
  float lenY = AB.lenghtY_line();
  return sqrt((lenX * lenX) + (lenY * lenY));
}
bool Line::IsAbscissaParallel(Line AB) {
  if (AB.lenghtY_line() == 0) {
    return 1;
  }
  return 0;
}
bool Line::IsOrdinateParallel(Line AB) {
  if (AB.lenghtX_line() == 0) {
    return 1;
  }
  return 0;
}
bool Line::IsParallel(Line AB, Line CD) {
  if (((AB.lenghtX_line() == CD.lenghtX_line()) + (AB.lenghtY_line() == CD.lenghtY_line())) >= 1) {
    return 1;
  }
  return 0;
}
float Line::ScalarProduct(Line AB, Line CD) {
  float resualt = (AB.lenghtX_line() * CD.lenghtX_line()) + (AB.lenghtY_line() * CD.lenghtY_line());
  return resualt;
}
float Line::CosLines(Line AB, Line CD) {
  float cosinus = 0.0;
  cosinus = ScalarProduct(AB, CD) / (Lenght_line(AB) + Lenght_line(CD));
  return cosinus;
}
bool Line::IsPerpendicular(Line AB, Line CD) {
  if (CosLines(AB, CD) == 0) {
    return 1;
  }
  return 0;
}
int Line::ComparingOfLengths(Line AB, Line CD) {
  if (Lenght_line(AB) > Lenght_line(CD)) { return 1; }
  else if (Lenght_line(AB) < Lenght_line(CD)) { return -1; }
  else { return 0; }
}
float Line::HeightDifference(Line AB, Line CD) {
  if (IsParallel(AB, CD)) {
    float difference = 0.0;
    difference = (AB._A._y - CD._A._y);
    return abs(difference);
  }
  return -1;
}
float Trapezoid::Perimeter() {
  float grounds = _AB.Lenght_line(_AB) + _CD.Lenght_line(_CD);
  float edges_first = 0.0;
  float edges_second = 0.0;
  Line AC(_AB._A, _CD._A);
  Line BD(_AB._B, _CD._B);
  edges_first = AC.Lenght_line(AC) + BD.Lenght_line(BD);
  Line AD(_AB._A, _CD._B);
  Line BC(_AB._B, _CD._A);
  edges_second = AD.Lenght_line(AD) + BC.Lenght_line(BC);
  if (edges_first > edges_second) {
    return edges_second + grounds;
  }
  return edges_first + grounds;
}
float Figure::Perimeter() {
  return 0;
}
float Figure::Square() {
  return 0;
}
float Figure::MinRectangle() {
  return 0;
}
float Trapezoid::Square() {
  if (_AB.IsParallel(_AB, _CD) == 0) {
    return 0;
  }
  float square = 0.0;
  float height = _AB.HeightDifference(_AB, _CD);
  if (height > 0) {
    square = (_AB.Lenght_line(_AB) + _CD.Lenght_line(_CD)) * (height / 2);
    return square;
  }
  return 0;
}
float Trapezoid::MinRectangle(){
  float buf = _AB.HeightDifference(_AB, _CD);
  if (_AB.Lenght_line(_AB) > _CD.Lenght_line(_CD)) {
    return _AB.Lenght_line(_AB) * buf;
  }
  return _CD.Lenght_line(_CD) * buf;
}
float Rectangle::Perimeter() {
  float grounds = _AB.Lenght_line(_AB) + _CD.Lenght_line(_CD);
  float edges_first = 0.0;
  float edges_second = 0.0;
  Line AC(_AB._A, _CD._A);
  Line BD(_AB._B, _CD._B);
  edges_first = AC.Lenght_line(AC) + BD.Lenght_line(BD);
  Line AD(_AB._A, _CD._B);
  Line BC(_AB._B, _CD._A);
  edges_second = AD.Lenght_line(AD) + BC.Lenght_line(BC);
  if (edges_first > edges_second) {
    return edges_second + grounds;
  }
  return edges_first + grounds;
}
float Rectangle::Square() {
  float square = _AB.Lenght_line(_AB) * abs(_AB.HeightDifference(_AB, _CD));
  return square;
}
float Rectangle::MinRectangle() {
  return Square();
}
float Ellipse::Perimeter() {
  float len1 = _AB.Lenght_line(_AB) / 2;
  float len2 = _CD.Lenght_line(_CD) / 2;
  float buf = PI * sqrt(2 * (len1 * len1 + len2 * len2));
  return buf;
}
float Ellipse::Square() {
  float len1 = _AB.Lenght_line(_AB) / 2;
  float len2 = _CD.Lenght_line(_CD) / 2;
  float buf = PI * len1 * len2;
  return buf;
}
float Ellipse::MinRectangle() {
  Point X(_AB._A._x, _CD._A._y), Y(_AB._B._x, _CD._A._y), Z(_AB._A._x, _CD._B._y), W(_AB._B._x, _CD._B._y);
  Rectangle buf(X, Y, Z, W);
  return buf.Square();
}

