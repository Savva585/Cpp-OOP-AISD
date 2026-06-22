#ifndef MY_VECTOR
#define MY_VECTOR
#include <iostream>
#include <vector>
#include <cstdlib>
#include <format>
#include <random>
void hello();
void output(int regular, int buf);
int checking_value();
void vec_rand(std::vector <int>& vec, int seed, int start, int stop, int n);
void vec_clau(std::vector <int>& vec, int n);
void choosing_method(std::vector <int>& vec, int n);
void print_vec(std::vector<int> &vec);
int element_max(std::vector<int>& vec);
#endif 

