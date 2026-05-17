#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   bool canReach(vector<int>& nums, int start) {
      if (start < 0 || start >= nums.size() || nums[start] < 0) {
         return false;
      }

      if (nums[start] == 0) {
         return true;
      }

      int jump = nums[start];

      nums[start] = -nums[start];

      return canReach(nums, start + jump) || canReach(nums, start - jump);
   }
};

int main() {

   int n, target;
   if (!(cin >> n >> target)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.canReach(nums, target);

   return 0;
}
