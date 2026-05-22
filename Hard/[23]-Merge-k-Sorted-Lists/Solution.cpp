#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   ListNode* mergeKLists(vector<ListNode*>& lists) {
      if (lists.empty()) return nullptr;

      int k = lists.size();
      while (k > 1) {
         for (int i = 0; i < k / 2; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[k - 1 - i]);
         }
         k = (k + 1) / 2;
      }

      return lists[0];
   }

private:
   ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      ListNode dummy(0);
      ListNode* tail = &dummy;

      while (l1 != nullptr && l2 != nullptr) {
         if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
         } else {
            tail->next = l2;
            l2 = l2->next;
         }
         tail = tail->next;
      }

      tail->next = (l1 != nullptr) ? l1 : l2;
      return dummy.next;
   }
};

int main() {

   int k;
   if (!(cin >> k)) return 0;

   vector<ListNode*> lists(k, nullptr);
   for (int i = 0; i < k; ++i) {
      int len;
      if (cin >> len) {
         vector<int> nums = Utils::readVector<int>(len);
         lists[i] = Utils::createList(nums);
      }
   }

   Solution sol;
   ListNode* result = sol.mergeKLists(lists);

   Utils::printList(result);
   Utils::freeList(result);

   return 0;
}
