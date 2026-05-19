#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int searchInsert(vector<int>& nums, int target) {
      int left = 0;
      int right = nums.size() - 1;

      while (left <= right) {
         int mid = left + (right - left) / 2;

         if (nums[mid] == target) {
            return mid;
         } else if (nums[mid] < target) {
            left = mid + 1;
         } else {
            right = mid - 1;
         }
      }

      return left;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   int target;
   if (!(cin >> target)) return 0;

   Solution sol;
   cout << sol.searchInsert(nums, target);

   return 0;
}
