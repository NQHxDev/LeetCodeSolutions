#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   int findMinRecursive(vector<int>& nums, int left, int right) {
      if (left == right) return nums[left];

      int mid = left + (right - left) / 2;

      if (nums[mid] > nums[right]) {
         return findMinRecursive(nums, mid + 1, right);
      } else {
         return findMinRecursive(nums, left, mid);
      }
   }

public:
   int findMin(vector<int>& nums) {
      int left = 0, right = nums.size() - 1;

      return findMinRecursive(nums, left, right);
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   int result = sol.findMin(nums);

   cout << result;

   return 0;
}
