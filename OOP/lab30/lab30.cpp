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

int main()
{
#if _MSC_VER
  system("chcp 65001 > nul");
#endif
  hello();
  vector<string>MyVector;
  vector<string>MyVectorWords;
  string NameFile = "C://1//pride_and_prejudice_by_jane_austen.txt";
  cout << "Считывания текста из файла\n" << NameFile << "\n";
  string NameFileWords = "C://1//words.txt";
  FileImport(MyVector, NameFile);
  FileImport(MyVectorWords, NameFileWords);
  vector<string>MyVectorNormalize;
  Normalize(MyVector, MyVectorNormalize);
  unordered_set<string>n_words(MyVectorWords.begin(), MyVectorWords.end());
  cout << "Общее количество слов в тексте: " << MyVectorNormalize.size() << "\n";
  cout << "Незначимые слова:\n";
  for (string& words : MyVectorWords) {
    cout << words << " ";
  }
  cout << "\nКоличество уникальных слов: "<<UniqNumber(MyVectorNormalize,MyVectorWords)<<"\n";
  auto result=MaxCount(MyVectorNormalize, n_words);
  cout <<"Количество вхождения самого популярного слова: "<< result.first<<"\nСамое популярное слово:\n";
  PrintResult(result.second);
}
