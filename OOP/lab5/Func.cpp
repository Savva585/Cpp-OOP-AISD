#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
#include"Func.h"
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
shared_ptr<Figure> ImportRec(Point A,Point B,Point C,Point D) {
  Line AB(A, B);
  Line CD(C, D);
  shared_ptr<Figure> ptr = make_shared<Rectangle>(AB, CD);
  return ptr;
}
shared_ptr<Figure> ImportTr(Point A, Point B, Point C, Point D) {
  Line AB(A, B);
  Line CD(C, D);
  shared_ptr<Figure> ptr = make_shared<Trapezoid>(AB, CD);
  return ptr;
}
shared_ptr<Figure> ImportEl(Point A, Point B, Point C, Point D) {
  Line AB(A, B);
  Line CD(C, D);
  shared_ptr<Figure> ptr = make_shared<Ellipse>(AB, CD);
  return ptr;
}
void PushElements(vector<shared_ptr<Figure>>& MyVec, const int& Type) {
  vector<Point> point;
  float x = 0;
  float y = 0;
  cout << "Введите четыре точки по координатам\n";
  for (int i = 0;i < 4;++i) {
    cin >> x >> y;
    Point buf(x, y);
    point.push_back(buf);
  }
  switch (Type) {
  case '1':
    MyVec.push_back(ImportTr(point[0], point[1], point[2], point[3]));
    break;
  case '2':
    MyVec.push_back(ImportRec(point[0], point[1], point[2], point[3]));
    break;
    cout << MyVec.size();
  case '3':
  MyVec.push_back(ImportEl(point[0], point[1], point[2], point[3]));
  break;
  }
}
pair<int, float> BaseFunc(vector<shared_ptr<Figure>> MyVec) {
  float buf = 1000;
  int num = 0;
  pair<int, float> resualt;
  for (shared_ptr<Figure> elements : MyVec) {
    num++;
    if (elements->MinRectangle() < buf && elements->MinRectangle()!=0) {
      resualt.first = num;
      resualt.second = elements->MinRectangle();
    }
  }
  return resualt;
}
