#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   ListNode* getKthNode(ListNode* curr, int k) {
      while (curr && k > 0) {
         curr = curr->next;
         k--;
      }
      return curr;
   }

public:
   ListNode* reverseKGroup(ListNode* head, int k) {
      if (!head || k <= 1) return head;

      ListNode dummy(0);
      dummy.next = head;
      ListNode* groupPrev = &dummy;

      while (true) {
         ListNode* kth = getKthNode(groupPrev, k);
         if (!kth) break;

         ListNode* groupNext = kth->next;
         ListNode* prev = groupNext;
         ListNode* curr = groupPrev->next;
         ListNode* temp = groupPrev->next;

         for (int i = 0; i < k; ++i) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
         }

         groupPrev->next = prev;
         groupPrev = temp;
      }

      return dummy.next;
   }
};

int main() {
   int n, k;
   if (!(cin >> n >> k)) return 0;

   vector<int> nums = Utils::readVector<int>(n);
   ListNode* head = Utils::createList(nums);

   Solution sol;
   ListNode* result = sol.reverseKGroup(head, k);

   Utils::printList(result);
   Utils::freeList(result);

   return 0;
}
