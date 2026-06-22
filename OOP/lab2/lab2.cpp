#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include "vector.h"

using namespace std;

int main() {
  #if _MSC_VER
  system("chcp 65001 > nul");
#endif
  hello();
  ios_base::sync_with_stdio(false);
  vector <int> vector_my;
  int n=0;
  cout << "Сколько элементов хотите ввести: \n";
  cin >> n;
  choosing_method(vector_my, n);
  print_vec(vector_my);
  output(n, element_max(vector_my));
  return 0;
}
