#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int threeSumClosest(vector<int>& nums, int target) {
      sort(nums.begin(), nums.end());

      int len = nums.size();
      int closestSum = nums[0] + nums[1] + nums[2];

      for (int i = 0; i < len - 2; i++) {
         if (i > 0 && nums[i] == nums[i - 1]) continue;

         int left = i + 1, right = len - 1;

         while (left < right) {
            int currentSum = nums[i] + nums[left] + nums[right];

            if (currentSum == target) {
               return currentSum;
            }

            if (abs(currentSum - target) < abs(closestSum - target)) {
               closestSum = currentSum;
            }

            if (currentSum < target) {
               left++;
            } else {
               right--;
            }
         }
      }

      return closestSum;
   }
};

int main() {

   int n, target;
   if (!(cin >> n >> target)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.threeSumClosest(nums, target);

   return 0;
}
