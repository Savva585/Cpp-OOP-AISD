#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <format>
#include <unordered_set>
#include <unordered_map>
#include "Function.h"
using namespace std;
void hello() {
  cout << format("┌─ ЛР № {} ──────────────┐\n"
    "│  Группа: {:<13}│\n"
    "│   Автор: {:<13}│\n"
    "│ Вариант: {:<13}│\n"
    "└───────────────────────┘\n", '3', "6112", "Гуцал Савва", "4");
}
void PrintResult(const set<string>& res)
{
  for (auto& i : res)
  {
    cout << format("\"{}\" ", i);
  }
  cout << "\n";
}

void Normalize(vector<string>& MyVector, vector<string>& MyVectorNormalize) {
  string buf;
  for (const string& words : MyVector) {
    for (unsigned char ab : words) {
      if (isalpha(ab)) {
        buf += tolower(ab);
      }
    }
    MyVectorNormalize.push_back(buf);
    buf = "";
  }
}
pair<size_t, set<string>> MaxCount(const vector<string>& MyVector, const unordered_set<string>& n_words)
{
  unordered_map<string, size_t> UniqCount;
  size_t MaxCount = 0;
  for (auto& str : MyVector)
  {
    if (!n_words.contains(str))
    {
      if (!UniqCount.contains(str))
        UniqCount[str] = 1;
      else
        ++UniqCount[str];
      MaxCount = max(UniqCount[str], MaxCount);
    }
  }
  pair<size_t, set<string> > res;
  res.first = MaxCount;
  for (auto& i : UniqCount)
  {
    if (i.second == MaxCount)
    {
      res.second.insert(i.first);
    }
  }
  return res;
}
size_t UniqNumber(vector<string>& MyVector, vector<string>& MyVectorWords) {
  unordered_set<string> unique_words(MyVector.begin(), MyVector.end());
  size_t count = 0;
  for (const auto& words : MyVectorWords) {
    if (unique_words.contains(words)) {
      count++;
    }
  }
  size_t n = unique_words.size();
  return n - count;
}
void FileImport(vector<string>& MyVector, const string& NameFile) {
  string buf;
  ifstream f(NameFile);
  for (int i = 0; !f.eof(); i++) {
    f >> buf;
    MyVector.push_back(buf);
  }
}
