#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   void nextPermutation(vector<int>& nums) {
      int len = nums.size();
      int pivot = -1;

      for (int i = len - 2; i >= 0; i--) {
         if (nums[i] < nums[i + 1]) {
            pivot = i;
            break;
         }
      }

      if (pivot != -1) {
         int pointChange = -1;
         for (int i = len - 1; i > pivot; i--) {
            if (nums[i] > nums[pivot]) {
               pointChange = i;
               break;
            }
         }
         swap(nums[pivot], nums[pointChange]);
      }

      int left = pivot + 1;
      int right = len - 1;
      while (left < right) {
         swap(nums[left], nums[right]);
         left++;
         right--;
      }
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   Solution sol;
   sol.nextPermutation(nums);

   for (int i = 0; i < nums.size(); i++) {
      cout << nums[i] << (i == nums.size() - 1 ? "" : " ");
   }

   return 0;
}
