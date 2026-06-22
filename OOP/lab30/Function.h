#ifndef Function
#define Function
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <format>
#include <unordered_set>
#include <unordered_map>
void hello();
void PrintResult(const std:: set<std::string>& res);
void Normalize(std::vector<std::string>& MyVector, std::vector<std::string>& MyVectorNormalize);
std::pair<size_t, std::set<std::string> > MaxCount(const std::vector<std::string>& vec, const std::unordered_set<std::string>& n_words);
size_t UniqNumber(std::vector<std::string>& MyVector, std::vector<std::string>& MyVectorWords);
void FileImport(std::vector<std::string>& MyVector, const std::string& NameFile);
#endif
