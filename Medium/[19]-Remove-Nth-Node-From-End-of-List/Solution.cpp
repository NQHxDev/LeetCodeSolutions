#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   ListNode* removeNthFromEnd(ListNode* head, int n) {
      ListNode* dummy = new ListNode(0, head);
      ListNode* fast = dummy;
      ListNode* slow = dummy;

      for (int i = 0; i <= n; ++i) {
         fast = fast->next;
      }

      while (fast != nullptr) {
         fast = fast->next;
         slow = slow->next;
      }

      ListNode* toDelete = slow->next;
      slow->next = slow->next->next;
      delete toDelete;

      ListNode* newHead = dummy->next;
      delete dummy;

      return newHead;
   }
};

int main() {

   int len, n;
   if (!(cin >> len >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(len);

   Solution sol;

   ListNode* listNode = Utils::createList(nums);
   ListNode* result = sol.removeNthFromEnd(listNode, n);

   Utils::printList(result);
   Utils::freeList(result);

   return 0;
}
