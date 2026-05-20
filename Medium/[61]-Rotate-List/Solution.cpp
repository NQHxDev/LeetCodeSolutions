#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   ListNode* rotateRight(ListNode* head, int k) {
      if (!head || !head->next || k == 0) {
         return head;
      }

      int len = 1;
      ListNode* tail = head;
      while (tail->next) {
         tail = tail->next;
         len++;
      }

      k = k % len;
      if (k == 0) {
         return head;
      }

      tail->next = head;

      ListNode* newTail = tail;
      for (int i = 0; i < len - k; ++i) {
         newTail = newTail->next;
      }

      ListNode* newHead = newTail->next;
      newTail->next = nullptr;

      return newHead;
   }
};

int main() {

   int n, k;
   if (!(cin >> n >> k)) return 0;

   vector<int> nums = Utils::readVector<int>(n);
   ListNode* listNode = Utils::createList(nums);

   Solution sol;
   ListNode* result = sol.rotateRight(listNode, k);

   Utils::printList(result);
   Utils::freeList(result);

   return 0;
}
