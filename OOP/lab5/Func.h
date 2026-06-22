#ifndef Function
#define Function
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
#include "Class.h"
class Point;
std::ostream& operator<<(std::ostream& stream, const Point& p);
class Line;
std::ostream& operator<<(std::ostream& stream, Line& l);
class Trapezoid;
class Figure;
class Rectangle;
class Ellipse;
std::ostream& operator<<(std::ostream& stream, std::shared_ptr<Trapezoid>ptr);
std::ostream& operator<<(std::ostream& stream, std::shared_ptr<Rectangle>ptr);
std::ostream& operator<<(std::ostream& stream, std::shared_ptr<Ellipse>ptr);
void KeepPoint(std::vector<Point>& points);
void KeepPoints(std::vector<Point>& points);
void KeepTrapezoids(std::vector<Point>& points, std::vector<Trapezoid>& Trapecs);
std::pair<int, float> MinSquare(std::vector<Trapezoid>Trapecs);
void hello();
void FileImport(std::vector<Point>& MyVector, const std::string& NameFile);
char Menu();
bool MenuWork(std::vector<std::shared_ptr<Figure>>& MyVec);
int Test(Point A, Point B, Point C, Point D);
std::shared_ptr<Figure> ImportRec(Point A, Point B, Point C, Point D);
std::shared_ptr<Figure> ImportTr(Point A, Point B, Point C, Point D);
std::shared_ptr<Figure> ImportEl(Point A, Point B, Point C, Point D);
void PushElements(std::vector<std::shared_ptr<Figure>>& MyVec, const int& Type);
char Push();
std::pair<int, float> BaseFunc(std::vector<std::shared_ptr<Figure>> MyVec);
#endif
