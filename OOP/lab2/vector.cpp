
#include"vector.h"

using namespace std;
void hello() {
  cout << format("┌─ ЛР № {} ──────────────┐\n"
    "│  Группа: {:<13}│\n"
    "│   Автор: {:<13}│\n"
    "│ Вариант: {:<13}│\n"
    "└───────────────────────┘\n",'2', "6112", "Гуцал Савва", "4");
}
void output(int regular, int buf) {
  cout << format("┌─ Ответ ────────────────────────┐\n"
    "│ Количество элементов: {:<9}│\n"
    "│ Максимальный элемент: {:<9}│\n"
    "└────────────────────────────────┘\n",regular,buf);
}
int checking_value() {
  int choose=0;
  cout << "Каким способом задать вектор чисел(1-рандом,0-клавиатура): \n";
  cin >> choose;
  while (choose > 1 || choose < 0) {
    cout << "Введите корректное значение: \n";
    cin >> choose;
  }
  return choose;
}
void vec_rand(vector <int>& vec, int seed, int start, int stop, int n) {
  default_random_engine engine(seed);
  uniform_int_distribution dist(min(start, stop), max(start, stop));
  for (size_t i = 0;i < n;++i) {
    vec.push_back(dist(engine));
  }
}
void vec_clau(vector <int>& vec, int n) {
  int buf=0;
  for (size_t i = 0;i < n;++i) {
    cin >> buf;
    vec.push_back(buf);
  }
}
void choosing_method(vector <int>& vec, int n) {
  int chose = checking_value();
  if (chose == 1) {
    int start = 0;
    int end = 0;
    int seed = 0;
    cout << "Введите нижнюю и верхнюю границу пробега rand и ядро: \n";
    cin >> start >> end >> seed;
    vec_rand(vec, seed, start, end, n);
  }
  if (chose == 0) {
    cout << "Начинайте вводить значения \n";
    vec_clau(vec, n);
  }
}
void print_vec(vector<int> &vec) {
  cout << "Вектор: \n";
  for (size_t i = 0;i < vec.size();++i) {
    cout << vec[i] << "  ";
  }
  cout << "\n";
}
int element_max(vector<int> &vec) {
  int buf = vec[0];
  for (size_t i = 1;i < vec.size();++i) {
    if (vec[i] > buf) {
      buf = vec[i];
    }
  }
  return buf;
}
