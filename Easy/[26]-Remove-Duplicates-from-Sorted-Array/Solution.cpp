#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int removeDuplicates(vector<int>& nums) {
      int n = nums.size();
      int i = 0;

      for (int j = 1; j < n; j++) {
         if (nums[i] != nums[j]) {
            i++;
            nums[i] = nums[j];
         }
      }

      return i + 1;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   Solution sol;
   cout << sol.removeDuplicates(nums);

   return 0;
}
