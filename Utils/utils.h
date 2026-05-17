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
#include <iomanip>

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

   // Hàm hỗ trợ tạo danh sách liên kết từ vector
   inline ListNode* createList(const std::vector<int>& nums) {
      if (nums.empty()) return nullptr;
      ListNode* head = new ListNode(nums[0]);
      ListNode* current = head;
      for (size_t i = 1; i < nums.size(); ++i) {
         current->next = new ListNode(nums[i]);
         current = current->next;
      }
      return head;
   }

   // Hàm hỗ trợ in danh sách liên kết
   inline void printList(ListNode* head) {
      if (!head) {
         std::cout << "[]" << std::endl;
         return;
      }
      while (head) {
         std::cout << head->val << (head->next ? " -> " : "");
         head = head->next;
      }
      std::cout << std::endl;
   }

   // Hàm hỗ trợ giải phóng bộ nhớ danh sách liên kết
   inline void freeList(ListNode* head) {
      while (head) {
         ListNode* temp = head;
         head = head->next;
         delete temp;
      }
   }
}

#endif
