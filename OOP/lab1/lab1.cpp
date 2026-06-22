#include <iostream>
#include <cstdlib>
#include <format>
#include <iomanip>
using namespace std;
void hello() {// функция объявления создателя
  cout << "┌─ ЛР № 1 ──────────────┐\n"
          "│  Группа: 6112         │\n"
          "│   Автор: Гуцал Савва  │\n"
          "│ Вариант: 4            │\n"
          "└───────────────────────┘\n"
    ;
}
void output(int regular,int buf) {
  cout << "┌─ Ответ ─────────────────────┐\n"
    "│ Количество элементов: " << setw(6) << left << regular << "│\n"
    "│ Максимальный элемент: " << setw(6) << left << buf << "│\n"
    "└─────────────────────────────┘\n"
    ;
}
int main() {
  #if _MSC_VER
  system("chcp 65001 > nul");
#endif
  hello();
  ios_base::sync_with_stdio(false);
  int buf = 0,a=0,regular;
  cout << "Введите количество элементов последовательности: ";
  cin >> regular;
  cout << "Ввод значений:\n";
  for (int i = 0;i < regular;++i) {
    cin >> a;
    if (buf < a) {
       buf = a;
    }
  }
  output(regular,buf);
  return 0;
}
