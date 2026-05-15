#include "../../Utils/utils.h"

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
   ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
      ListNode* dummyHead = new ListNode(0);
      ListNode* current = dummyHead;

      while (list1 != nullptr && list2 != nullptr) {
         if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
         } else {
            current->next = list2;
            list2 = list2->next;
         }
         current = current->next;
      }

      if (list1 != nullptr) {
         current->next = list1;
      }

      if (list2 != nullptr) {
         current->next = list2;
      }

      ListNode* result = dummyHead->next;

      delete dummyHead;

      return result;
   }
};

ListNode* createList(const vector<int>& nums) {
   if (nums.empty()) return nullptr;
   ListNode* head = new ListNode(nums[0]);
   ListNode* current = head;
   for (size_t i = 1; i < nums.size(); ++i) {
      current->next = new ListNode(nums[i]);
      current = current->next;
   }
   return head;
}

void printList(ListNode* head) {
   if (!head) {
      cout << "[]" << endl;
      return;
   }
   while (head) {
      cout << head->val << (head->next ? " -> " : "");
      head = head->next;
   }
   cout << endl;
}

int main() {
   Solution sol;

   // Test case 1: [1, 2, 4], [1, 3, 4]
   cout << "Test 1: L1 = [1, 2, 4], L2 = [1, 3, 4]" << endl;
   ListNode* l1 = createList({1, 2, 4});
   ListNode* l2 = createList({1, 3, 4});
   ListNode* res1 = sol.mergeTwoLists(l1, l2);
   cout << "Result: ";
   printList(res1);

   // Test case 2: [], []
   cout << "\nTest 2: L1 = [], L2 = []" << endl;
   ListNode* l3 = createList({});
   ListNode* l4 = createList({});
   ListNode* res2 = sol.mergeTwoLists(l3, l4);
   cout << "Result: ";
   printList(res2);

   // Test case 3: [], [0]
   cout << "\nTest 3: L1 = [], L2 = [0]" << endl;
   ListNode* l5 = createList({});
   ListNode* l6 = createList({0});
   ListNode* res3 = sol.mergeTwoLists(l5, l6);
   cout << "Result: ";
   printList(res3);

   return 0;
}
