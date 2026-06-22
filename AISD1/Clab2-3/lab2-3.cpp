#include <iostream>
#include<random>
#include<vector>
#include"my_list.cpp"
using namespace std;
void swap_nodes(Node<int>* a, Node<int>* b, stats& result) {
  if (!a || !b || a == b) return;

  int temp = a->_value;
  a->_value = b->_value;
  b->_value = temp;

  result.copy_count += 3;
}

stats sort_bubble(Node<int>* head) {
  stats result;
  if (!head) return result;
  size_t n = 0;
  Node<int>* counter = head;
  do {
    n++;
    counter = counter->next;
  } while (counter != head);
  bool swapped;
  for (size_t i = 0; i < n - 1; i++) {
    swapped = false;
    Node<int>* current = head;
    for (size_t j = 0; j < n - i - 1; j++) {
      result.comparison_count++;

      if (current->_value > current->next->_value) {
        swap_nodes(current, current->next, result);
        swapped = true;
      }
      current = current->next;
    }
    if (!swapped) break;
  }
  return result;
}

stats sort_selection(Node<int>* head) {
  stats result;
  if (!head) return result;
  Node<int>* current = head;
  do {
    Node<int>* minNode = current;
    Node<int>* temp = current->next;
    while (temp != head) {
      result.comparison_count++;
      if (temp->_value < minNode->_value) {
        minNode = temp;
      }
      temp = temp->next;
    }

    if (minNode != current) {
      swap_nodes(minNode, current, result);
    }
    current = current->next;
  } while (current != head && current->next != head);

  return result;
}

void generator(vector<int>&arr, size_t n, int start, int end){
  if (n == 0) return;
  random_device device;
  uniform_int_distribution<int> distr(min(start, end), max(start, end));

  for (size_t i = 0; i < n; i++) {
    arr.push_back(distr(device));
  }
}

stats sort_shaker(vector<int>& arr) {
  stats resualt;
  bool swapper = true;
  int start = 0;
  int end = arr.size() - 1;
  while (swapper) {
    swapper = false;
    for (size_t i = start;i < end-1;++i) {
      if (arr[i] > arr[i + 1]) {
        swapper = true;
        resualt.comparison_count++;
        swap(arr[i], arr[i + 1]);
        resualt.copy_count += 3;
      }
    }

    if (!swapper) break;
    swapper = false;
    end--;

    for (size_t i = end;i > start;i--) {
      if (arr[i] < arr[i - 1]) {
        swapper = true;
        resualt.comparison_count++;
        swap(arr[i], arr[i - 1]);
        resualt.copy_count += 3;
      }
    }
    start++;
  }
  return resualt;
}

stats comb_sort(vector<int>& arr) {
  stats resualt;
  int n = arr.size();
  if (n <= 1) return resualt;
  int coef = n;
  bool swapped = true;

  while (coef > 1 || swapped) {
    coef = coef / 1.3;
    if (coef < 1) coef = 1;
    swapped = false;
    for (int i = 0; i < n - coef; ++i) {
      if (arr[i] > arr[i + coef]) {
        resualt.comparison_count++;
        swap(arr[i], arr[i + coef]);
        resualt.copy_count += 3;
        swapped = true;
      }
    }
  }
  return resualt;
}



void distribute_sequences(const vector<int>& input, vector<int>& fileA, vector<int>& fileB, stats& s) {
  if (input.empty()) return;
  bool write_to_A = true;
  size_t i = 0;

  while (i < input.size()) {
    vector<int> current_sequence;
    current_sequence.push_back(input[i]);
    i++;
    s.copy_count++;
    while (i < input.size()) {
      s.comparison_count++;
      if (input[i] >= current_sequence.back()) {
        current_sequence.push_back(input[i++]);
        s.copy_count++;
      }
      else {
        break;
      }
    }
    if (write_to_A) {
      fileA.insert(fileA.end(), current_sequence.begin(), current_sequence.end());
    }
    else {
      fileB.insert(fileB.end(), current_sequence.begin(), current_sequence.end());
    }
    s.copy_count += current_sequence.size();
    write_to_A = !write_to_A;
  }

}

void merge_files(const vector<int>& fileA, const vector<int>& fileB, vector<int>& output, stats& s) {
  size_t i = 0, j = 0;

  while (i < fileA.size() && j < fileB.size()) {
    size_t startA = i, startB = j;
    while (i + 1 < fileA.size() && fileA[i] <= fileA[i + 1]) {
      s.comparison_count++;
      i++;
    }
    size_t endA = i;
    while (j + 1 < fileB.size() && fileB[j] <= fileB[j + 1]) {
      s.comparison_count++;
      j++;
    }
    size_t endB = j;
    i = startA;
    j = startB;
    while (i <= endA && j <= endB) {
      s.comparison_count++;
      if (fileA[i] <= fileB[j]) {
        output.push_back(fileA[i++]);
      }
      else {
        output.push_back(fileB[j++]);
      }
      s.copy_count++;
    }
    while (i <= endA) {
      output.push_back(fileA[i++]);
      s.copy_count++;
    }
    while (j <= endB) {
      output.push_back(fileB[j++]);
      s.copy_count++;
    }
    i = endA + 1;
    j = endB + 1;
  }
  while (i < fileA.size()) {
    output.push_back(fileA[i++]);
    s.copy_count++;
  }
  while (j < fileB.size()) {
    output.push_back(fileB[j++]);
    s.copy_count++;
  }
}

stats sort_natural_two_way_merge(vector<int>& arr) {
  stats result;
  if (arr.size() <= 1) return result;
  vector<int> current = arr;

  while (true) {
    vector<int> fileA, fileB;
    distribute_sequences(current, fileA, fileB, result);
    if (fileB.empty()) {
      arr = fileA;
      break;
    }
    vector<int> merged;
    merge_files(fileA, fileB, merged, result);
    current = merged;
  }
  return result;
}

void demostration() {
  int arr[4] = { 100000 };
  float middle_comp_list=0;
  float middle_copy_list=0;
  float middle_comp_vec1=0;
  float middle_copy_vec1=0;
  float middle_comp_vec2=0;
  float middle_copy_vec2=0;
  for (const int value : arr) {
    vector<int> vec;
    list<int> lister(value, 1, 3000);
    generator(vec, value, 1, 3000);
    //stats lists=sort_bubble(lister.front());
    /*middle_comp_list += lists.comparison_count;
    middle_copy_list += lists.copy_count;*/
    stats vecs1=sort_shaker(vec);
    middle_comp_vec1 += vecs1.comparison_count;
    middle_copy_vec1 += vecs1.copy_count;
    /*stats vecs2 = sort_natural_two_way_merge(vec);
    middle_comp_vec2 += vecs2.comparison_count;
    middle_copy_vec2 += vecs2.copy_count;*/
    /*cout << "\n\nList sort(sise: " << value << ") comparation and copy: \n" << lists.comparison_count << " \n" << lists.copy_count;*/
    cout << "\n\nVector sort shaker(size: " << value << ") comparation and copy: \n" << vecs1.comparison_count << " \n" << vecs1.copy_count;
    /*cout << "\n\nVector sort natural(size: " << value << ") comparation and copy: \n" << vecs2.comparison_count << " \n" << vecs2.copy_count;*/
    lister.clear();
    vec.clear();
  }
  /*cout << "\n\n Middle values list: " << middle_comp_list / 4 << " " << middle_copy_list /4;*/
  cout << "\n\n Middle values vec1: " << middle_comp_vec1 / 4 << " " << middle_copy_vec1 / 4;
  //cout << "\n\n Middle values vec2: " << middle_comp_vec2 / 4 << " " << middle_copy_vec2 / 4;
}

int main() {
  demostration();
}
