#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

namespace Utils {
   // Hàm nhập mảng với n phần tử
   template <typename T>
   std::vector<T> readVector(int n) {
      std::vector<T> vec(n);
      for (int i = 0; i < n; ++i) {
         std::cin >> vec[i];
      }
      return vec;
   }

   // Hàm xuất mảng với ký tự phân cách
   template <typename T>
   void printVector(const std::vector<T>& vec, const std::string& separator = " ") {
      for (size_t i = 0; i < vec.size(); ++i) {
         std::cout << vec[i] << (i == vec.size() - 1 ? "" : separator);
      }
      std::cout << std::endl;
   }

   // Hàm xuất kết quả dạng đơn giản
   template <typename T>
    void printResult(const std::vector<T>& result) {
        if (result.empty()) {
            std::cout << "No solution found!" << std::endl;
            return;
        }
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
}

#endif
