#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   bool canJump(vector<int>& nums) {
      int n = nums.size();
      int maxReachable = 0;

      for (int i = 0; i < n; ++i) {
         if (i > maxReachable) {
            return false;
         }
         maxReachable = max(maxReachable, i + nums[i]);
         if (maxReachable >= n - 1) {
            return true;
         }
      }

      return true;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.canJump(nums);

   return 0;
}
