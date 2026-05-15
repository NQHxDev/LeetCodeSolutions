#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   vector<vector<int>> threeSum(vector<int>& nums) {
      sort(nums.begin(), nums.end());

      vector<vector<int>> result;
      int len = nums.size();

      for (int i = 0; i < len - 2; i++) {
         if (i > 0 && nums[i] == nums[i - 1]) continue;

         int left = i + 1, right = len - 1;
         while(left < right) {
            int total = nums[i] + nums[left] + nums[right];

            if (total > 0) {
               right--;
            } else if (total < 0) {
               left++;
            } else {
               result.push_back({nums[i], nums[left], nums[right]});

               // Nhảy qua các phần tử trùng lặp
               while (left < right && nums[left] == nums[left + 1]) left++;
               while (left < right && nums[right] == nums[right - 1]) right--;

               left++;
               right--;
            }
         }
      }

      return result;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   vector<vector<int>> result = sol.threeSum(nums);

   for (int i = 0; i < result.size(); i++){
      Utils::printVector(result[i]);
   }

   return 0;
}
