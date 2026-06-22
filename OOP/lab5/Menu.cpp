#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include"Func.h"
#include"Class.h"
using namespace std;
ostream& operator<<(ostream& stream, shared_ptr<Figure>ptr) {
  stream << "\nОснование 1: " << ptr->_AB << "\nОснование 2: " << ptr->_CD << "\n";
  return stream;
}
char Menu() {
  cout << format(
    "\n{}Хотите добавить ещё одну фигуру для обработки\n"
    "{}Хотите удалить одну фигуру перед обработкой\n"
    "{}Хотите вывести все фигуры\n"
    "{}Хотите найти фигуру с минимальным обрамляющим прямоугольником\n"
    "{}Хотите найти площадь фигуры по индексу\n"
    "{}Хотиту найти периметр фигуры по индексу\n"
    "{}Хотите закончить\n"
    , "[1]", "[2]", "[3]", "[4]","[5]","[6]", "[0]");
  cout << "Выберите пункт в меню: ";
  char n;
  cin >> n;
  cout << '\n';
  return n;
}
char Push() {
  cout << format(
    "\n{}Хотите добавить трапецию\n"
    "{}Хотите добавить прямоугольник\n"
    "{}Хотите добавить эллипс\n"
    , "[1]", "[2]", "[3]");
  cout << "Выберите пункт в меню: ";
  char m;
  cin >> m;
  cout << '\n';
  return m;
}
bool MenuWork(vector<shared_ptr<Figure>>& MyVec) {
  char n = Menu();
  char m;
  bool Flag = false;
  size_t index = 0;
  pair<int, float> resualt;
  switch (n)
  {
  case '1':
    m = Push();
    PushElements(MyVec, m);
    break;
  case '2':
    cout << "\nВведите индекс для удаления фигуры:";
    cin >> index;
    if (MyVec.size() > index) {
      MyVec.erase(MyVec.begin() + index);
    }
    break;
  case '3':
    for (const shared_ptr<Figure>& elements : MyVec) {
      char c = elements->Type;
      if (c == 'r') {
        cout << "\nПрямоугольник ";
      }
      if (c == 't') {
        cout << "\nТрапеция ";
      }
      if(c=='e') { cout << "\nЭллипс "; }
      cout << elements;
    }
    break;
  case '4':
    resualt = BaseFunc(MyVec);
    cout << "\nМинимальный обрамляющий прямоугольник у фигуры " << resualt.first << " и его площадь равна " << resualt.second << '\n';
    break;
  case '5':
    cout << "\nВведите индекс фигуры:";
    cin >> index;
    if (MyVec.size() > index) {
      cout << "Площадь " << MyVec[index]->Square() << '\n';
    }
    break;
  case '6':
    cout << "\nВведите индекс фигуры:";
    cin >> index;
    if (MyVec.size() > index) {
      cout << "Периметр " << MyVec[index]->Perimeter() << '\n';
    }
    break;
  case '0':
    Flag = true;
    break;
  }
  return Flag;
}

