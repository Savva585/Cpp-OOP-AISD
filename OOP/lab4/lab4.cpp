#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <map>
#include <fstream>
#include "Function.h"
#include "Class.h"
using namespace std;
int main()
{
#if _MSC_VER
  system("chcp 65001 > nul");
#endif
  hello();
  vector<Point>points;
  string File = "C:\\1\\lab40.txt";
  FileImport(points, File);
  vector<Trapezoid>Trapecs;
  KeepTrapezoids(points, Trapecs);
  cout << "На данный момент имеется 4 трапеции, взятые из тестового файла\n";
  bool Flag = false;
  while (!Flag) {
    Flag=MenuWork(points, Trapecs);
  }
}
