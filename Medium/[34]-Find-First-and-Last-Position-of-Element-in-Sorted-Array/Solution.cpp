#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   int findBound(const vector<int>& nums, int target, bool isFirst) {
      int n = nums.size();
      int left = 0, right = n - 1;
      int bound = -1;

      while (left <= right) {
         int mid = left + (right - left) / 2;

         if (nums[mid] == target) {
            bound = mid;
            if (isFirst) {
               right = mid - 1;
            } else {
               left = mid + 1;
            }
         } else if (nums[mid] > target) {
            right = mid - 1;
         } else {
            left = mid + 1;
         }
      }

      return bound;
   }

public:
   vector<int> searchRange(vector<int>& nums, int target) {
      int first = findBound(nums, target, true);
      int last = findBound(nums, target, false);
      return {first, last};
   }
};

int main() {
   int n, target;
   if (!(cin >> n >> target)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   vector<int> result = sol.searchRange(nums, target);

   Utils::printVector(result);

   return 0;
}
