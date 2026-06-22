#include <iostream>
#include "class.cpp"
#include <vector>

std::vector<int> nonRepeatingElements(const std::vector<int>& input) {
  AVLTree<int> unique;
  AVLTree<int> duplicates;
  std::vector<int> result;

  for (int x : input) {
    if (duplicates.contains(x)) {
    }
    if (unique.contains(x)) {
      unique.remove(x);
      duplicates.insert(x);
    }
    else {
      unique.insert(x);
    }
  }

  for (int x : input) {
    if (unique.contains(x)) {
      result.push_back(x);
      unique.remove(x);
    }
  }
  return result;
}

