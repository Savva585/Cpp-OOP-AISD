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
char Menu() {
   cout << format(
    "\n{}Хотите добавить ещё одну трапецию для обработки\n"
    "{}Хотите удалить одну трапецию перед обработкой\n"
    "{}Хотите вывести все трапеции\n"
    "{}Хотите найти минимальную по площади трапецию\n"
    "{}Хотите закончить\n"
    , "[1]", "[2]", "[3]", "[4]","[0]");
   cout << "Выберите пункт в меню: ";
   char n;
   cin >> n;
   cout << '\n';
   return n;
}
bool MenuWork(vector<Point>&points,vector<Trapezoid>& Trapecs) {
  int n = Menu();
  bool Flag = false;
  size_t index = 0;
  pair<int, float> resualt;
  switch (n)
  {
  case '1':
    KeepPoints(points);
    KeepTrapezoids(points, Trapecs);
    break;
  case '2':
    cout << "\nВведите индекс для удаления трапеции:";
    cin >> index;
    if (Trapecs.size() > index) {
      Trapecs.erase(Trapecs.begin()+index);
    }
    else {
      cout << "\nВы ввели некоректный индекс";
    }
    break;
  case '3':
    for (Trapezoid& el : Trapecs) {
      cout << el;
    }
    break;
  case '4' :
    resualt = MinSquare(Trapecs);;
    cout << "\nС минимальной площадью трапеция номер " << resualt.first << "\nЕё площадь равна " << resualt.second<<'\n';
    break;
  case '0':
    Flag = true;
    break;
  }
  return Flag;
}

