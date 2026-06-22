#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include "class.cpp"
#include "funk.cpp" 


using namespace std;
using namespace chrono;

vector<int> generateUniqueNumbers(int N, int start = 1) {
  vector<int> nums(N);
  for (int i = 0; i < N; ++i)
    nums[i] = start + i;
  random_device rd;
  mt19937 g(rd());
  shuffle(nums.begin(), nums.end(), g);
  return nums;
}

vector<int> generateRandomWithDuplicates(int size, int maxVal) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(1, maxVal);
  vector<int> v(size);
  for (int i = 0; i < size; ++i)
    v[i] = dist(gen);
  return v;
}

void demoNonRepeating() {
  cout << "\n=== Демонстрация функции nonRepeatingElements ===\n";
  vector<int> testVec = { 5, 2, 5, 3, 2, 1, 4, 4, 6, 7, 7, 8 };
  cout << "Исходный вектор: ";
  for (int x : testVec) cout << x << " ";
  cout << endl;

  vector<int> result = nonRepeatingElements(testVec);
  cout << "Элементы, встречающиеся ровно один раз: ";
  for (int x : result) cout << x << " ";
  cout << endl;

  vector<int> randomVec = generateRandomWithDuplicates(100, 10);
  cout << "\nСлучайный вектор (20 элементов, значения от 1 до 10): ";
  for (int x : randomVec) cout << x << " ";
  cout << endl;

  result = nonRepeatingElements(randomVec);
  cout << "Уникальные элементы (без повторов): ";
  for (int x : result) cout << x << " ";
  cout << endl;
}

template<typename Func>
double measureAverageTime(Func&& func, int count) {
  auto start = high_resolution_clock::now();
  for (int i = 0; i < count; ++i) func();
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count() / static_cast<double>(count);
}

double testFill(AVLTree<int>& tree, const vector<int>& data) {
  auto start = high_resolution_clock::now();
  for (int x : data) tree.insert(x);
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

double testSearchExisting(AVLTree<int>& tree, const vector<int>& data, int trials) {
  auto start = high_resolution_clock::now();
  for (int i = 0; i < trials; ++i)
    for (int x : data) tree.contains(x);
  auto end = high_resolution_clock::now();
  double total_us = duration_cast<microseconds>(end - start).count();
  return total_us / (trials * data.size());
}

double testInsertNew(AVLTree<int>& tree, const vector<int>& newData) {
  auto start = high_resolution_clock::now();
  for (int x : newData) tree.insert(x);
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count() / static_cast<double>(newData.size());
}

double testDeleteExisting(AVLTree<int>& tree, const vector<int>& data) {
  auto start = high_resolution_clock::now();
  for (int x : data) tree.remove(x);
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count() / static_cast<double>(data.size());
}

int main() {
  system("chcp 65001 > nul");
  demoNonRepeating();

  const vector<int> sizes = { 1000, 10000, 100000 };
  const int trials = 5;

  cout << fixed << setprecision(2);
  cout << "\n=== Тестирование производительности AVL-дерева ===\n\n";

  for (int N : sizes) {
    cout << "Размер дерева: " << N << "\n";

    vector<int> data = generateUniqueNumbers(N, 1);

    double fillTotal = 0.0;
    for (int t = 0; t < trials; ++t) {
      AVLTree<int> tree;
      fillTotal += testFill(tree, data);
    }
    double avgFillTotal = fillTotal / trials;
    double avgFillPerInsert = avgFillTotal / N;
    cout << "Заполнение (всего): " << avgFillTotal << " мкс\n";
    cout << "Заполнение (на вставку): " << avgFillPerInsert << " мкс\n";

    AVLTree<int> baseTree;
    testFill(baseTree, data);

    double searchExist = testSearchExisting(baseTree, data, trials);
    cout << "Поиск существующих: " << searchExist << " мкс\n";

    vector<int> newData = generateUniqueNumbers(N, N + 1);
    double insertNewAvg = 0.0;
    for (int t = 0; t < trials; ++t) {
      AVLTree<int> tree;
      testFill(tree, data);
      insertNewAvg += testInsertNew(tree, newData);
    }
    insertNewAvg /= trials;
    cout << "Вставка новых: " << insertNewAvg << " мкс\n";

    double deleteAvg = 0.0;
    for (int t = 0; t < trials; ++t) {
      AVLTree<int> tree;
      testFill(tree, data);
      deleteAvg += testDeleteExisting(tree, data);
    }
    deleteAvg /= trials;
    cout << "Удаление существующих: " << deleteAvg << " мкс\n";

    cout << "\n";
  }

  return 0;
}
