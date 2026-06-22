#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
#include"Function.h"
#include"Class.h"
using namespace std;
ostream& operator<<(ostream& stream, const Point& p) {
  stream << format("({},{})", p._x, p._y);
  return stream;
}
ostream& operator<<(ostream& stream, Line& l) {
  stream << format("<({},{})>", l.lenghtX_line(), l.lenghtY_line());
  return stream;
}
ostream& operator<<(ostream& stream, Trapezoid& T) {
  stream << "\nОснование 1: " << T._AB << "\nОснование 2: " << T._CD << "\n";
  return stream;
}
void KeepPoint(vector<Point>& points) {
  float x = 0;
  float y = 0;
  cin >> x >> y;
  Point p(x, y);
  points.push_back(p);
}
void KeepPoints(vector<Point>& points) {
  cout << "Введите 4 точки\n";
  for (int i = 0;i < 4;++i) {
    KeepPoint(points);
  }
}
void KeepTrapezoids(vector<Point>& points, vector<Trapezoid>& Trapecs) {
  while (points.size() > 3) {
    Trapezoid T(points[0], points[1], points[2], points[3]);
    Trapecs.push_back(T);
    points.erase(points.begin(), points.begin() + 4);
  }

  if (points.size() != 0) {
    cout << "Т.к. трапеция строится по 4 точкам, остались лишние, в количестве: " << points.size() << '\n';
  }

}
pair<int, float> MinSquare(vector<Trapezoid>Trapecs) {
  float MinSquare = Trapecs[0].Square();
  pair<int, float> resualt;
  for (int i = 0;i < Trapecs.size();++i) {
    if (Trapecs[i].Square() != 0) {
      MinSquare = min(MinSquare, Trapecs[i].Square());
      if (MinSquare == Trapecs[i].Square()) {
        resualt.first = i;
      }
      resualt.second = MinSquare;
    }
  }
  return resualt;
}
void hello() {
  cout << format("┌─ ЛР № {} ──────────────┐\n"
    "│  Группа: {:<13}│\n"
    "│   Автор: {:<13}│\n"
    "│ Вариант: {:<13}│\n"
    "└───────────────────────┘\n", '4', "6112", "Гуцал Савва", "4");
}
void FileImport(vector<Point>& MyVector, const string& NameFile) {
  ifstream f(NameFile);
  float x = 0;
  float y = 0;
  for (int i = 0; !f.eof(); i++) {
    f >> x;
    f >> y;
    Point p(x, y);
    MyVector.push_back(p);
  }
  MyVector.pop_back();
}
int Test(Point A, Point B, Point C, Point D) {
  Line AB(A, B);
  Line CD(C, D);
  if (AB.IsParallel(AB, CD)) {
    return 1;
  }
  Line AC(A, C);
  Line BD(B, D);
  if (AC.IsParallel(AC, BD)) {
    return -1;
  }
  return 0;
}
