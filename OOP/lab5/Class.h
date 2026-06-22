#ifndef Class
#define Class
#include <iostream>
#include <vector>
#include <string>
#include <format>
#define PI 3.141592
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
class Figure {
public:
  Line _AB;
  Line _CD;
  char Type=' ';
  Figure(Line AB, Line CD, const char& t) : _AB(AB), _CD(CD), Type(t) {}
  Figure(Point A, Point B, Point C, Point D,const char& t) {
    Line AB(A, B), CD(C, D);
    _AB = AB;
    _CD = CD;
    Type = t;
  }
  virtual float Perimeter();
  virtual float Square();
  virtual float MinRectangle();
  virtual ~Figure() = default;
};
class Trapezoid:public Figure {
public:
  Trapezoid(Line AB, Line CD) : Figure(AB, CD,'t') {}
  Trapezoid(Point A, Point B, Point C, Point D) : Figure(A, B, C, D,'t') {}
  float Perimeter()override;
  float Square()override;
  float MinRectangle()override;
};
class Rectangle : public Figure {
public:
  Rectangle(Line AB, Line CD) : Figure(AB, CD, 'r') {}
  Rectangle(Point A, Point B, Point C, Point D) : Figure(A, B, C, D, 'r') {}
  float Perimeter() override;
  float Square() override;
  float MinRectangle()override;
};
class Ellipse : public Figure {
public:
  Ellipse(Line AB, Line CD) : Figure(AB, CD, 'e') {}
  Ellipse(Point A, Point B, Point C, Point D) : Figure(A, B, C, D, 'e') {}
  float Perimeter() override;
  float Square()override;
  float MinRectangle()override;
};
#endif
