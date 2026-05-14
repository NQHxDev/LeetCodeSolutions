#include "../../utils/utils.h"

using namespace std;

class Solution {
public:
   vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> prevNums;
      for (int i = 0; i < nums.size(); i++) {
         int complement = target - nums[i];
         if (prevNums.find(complement) != prevNums.end()) {
            return {prevNums[complement], i};
         }
         prevNums[nums[i]] = i;
      }

      return {};
   }
};

int main() {
   int n, target;
   if (!(cin >> n >> target)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   vector<int> result = sol.twoSum(nums, target);

   Utils::printResult(result);

   return 0;
}
