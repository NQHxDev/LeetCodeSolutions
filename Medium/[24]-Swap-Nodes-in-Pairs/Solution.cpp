#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   ListNode* swapPairs(ListNode* head) {
      ListNode dummy(0);
      dummy.next = head;
      ListNode* prev = &dummy;

      while (prev->next != nullptr && prev->next->next != nullptr) {
         ListNode* first = prev->next;
         ListNode* second = prev->next->next;

         first->next = second->next;
         second->next = first;
         prev->next = second;
         prev = first;
      }

      return dummy.next;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();
   ListNode* head = Utils::createList(nums);

   Solution sol;
   ListNode* result = sol.swapPairs(head);

   Utils::printList(result);
   Utils::freeList(result);

   return 0;
}
