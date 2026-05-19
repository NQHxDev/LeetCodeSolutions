#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int removeElement(vector<int>& nums, int val) {
      int len = nums.size();
      int i = 0;
      for (int j = 0; j < len; j++) {
         if (nums[j] != val) {
            nums[i] = nums[j];
            i++;
         }
      }

      return i;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   int val;
   if (!(cin >> val)) return 0;

   Solution sol;
   cout << sol.removeElement(nums, val);

   return 0;
}
