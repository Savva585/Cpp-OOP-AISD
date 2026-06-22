#include <iostream>
#include <cstdlib>
#include <memory>
#include <format>
#include "Class.h"
#include <string>
#include "Func.h"
using namespace std;
int main() {
  #if _MSC_VER
  system("chcp 65001 > nul");
#endif
  ios_base::sync_with_stdio(false);
  vector<shared_ptr<Figure>> MyVec;
  bool flag=false;
  while (!flag) {
   flag=MenuWork(MyVec);
  }
}
