#ifndef Class
#define Class
#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
class Point {
public:
  float _x = 0.0;
  float _y = 0.0;
  Point() = default;
  Point(float x, float y) {
    _x = x;
    _y = y;
  }
  float XTop()const;
  float YTop()const;
  void Reset();
};
class Line {
public:
  Point _A;
  Point _B;
  Line() = default;
  Line(Point A, Point B) : _A(A), _B(B) {}
  float lenghtX_line();
  float lenghtY_line();
  float Lenght_line(Line AB);
  bool IsAbscissaParallel(Line AB);
  bool IsOrdinateParallel(Line AB);
  bool IsParallel(Line AB, Line CD);
  float ScalarProduct(Line AB, Line CD);
  float CosLines(Line AB, Line CD);
  bool IsPerpendicular(Line AB, Line CD);
  int ComparingOfLengths(Line AB, Line CD);
  float HeightDifference(Line AB, Line CD);
};
class Trapezoid {
public:
  Line _AB;
  Line _CD;
  Trapezoid() = default;
  Trapezoid(Line AB, Line CD) {
    if (AB.IsParallel(AB, CD)) {
      _AB = AB;
      _CD = CD;
    }
  }
  Trapezoid(Point A, Point B, Point C, Point D) {
    Line AB(A, B), CD(C, D);
    _AB = AB;
    _CD = CD;
  }
  float Perimeter();
  float Square();
};
#endif
