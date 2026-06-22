#ifndef Function
#define Function
#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
class Point;
std::ostream& operator<<(std::ostream& stream, const Point& p);
class Line;
std::ostream& operator<<(std::ostream& stream, Line& l);
class Trapezoid;
std::ostream& operator<<(std::ostream& stream, Trapezoid& T);
void KeepPoint(std::vector<Point>& points);
void KeepPoints(std::vector<Point>& points);
void KeepTrapezoids(std::vector<Point>& points, std::vector<Trapezoid>& Trapecs);
std::pair<int, float> MinSquare(std::vector<Trapezoid>Trapecs);
void hello();
void FileImport(std::vector<Point>& MyVector, const std::string& NameFile);
char Menu();
bool MenuWork(std::vector<Point>& points, std::vector<Trapezoid>& Trapecs);
int Test(Point A, Point B, Point C, Point D);
#endif
