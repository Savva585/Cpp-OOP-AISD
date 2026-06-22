#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "class.cpp"

void count_duplicates(const std::vector<int>& vec) {
    hashtable<int> freq_table;  
    
    for (int num : vec) {
        int* count = freq_table.search(num);
        if (count == nullptr) {
            freq_table.insert(num, 1);
        } else {
            int new_count = (*count) + 1; 
            freq_table.insert_or_assign(num, new_count);
        }
    }
    
    std::vector<int> processed;
    
    for (int num : vec) {
        bool already_printed = false;
        for (int p : processed) {
            if (p == num) {
                already_printed = true;
                break;
            }
        }
        
        if (!already_printed) {
            int* count = freq_table.search(num);
            if (count != nullptr && *count > 1) {
                std::cout << "Number " << num << " - " << *count << std::endl;
            }
            processed.push_back(num);
        }
    }
}

int main() {
    size_t vector_size = 20;
    int min_val = 0;
    int max_val = 10;  
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(min_val, max_val);
    
    std::vector<int> vec;
    std::cout << "Vector: ";
    for (size_t i = 0; i < vector_size; i++) {
        vec.push_back(dist(gen));
        std::cout << vec.back() << " ";
    }
    std::cout << std::endl << std::endl;
    
    count_duplicates(vec);
    
    return 0;
}