#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   vector<vector<int>> fourSum(vector<int>& nums, int target) {
      sort(nums.begin(), nums.end());

      vector<vector<int>> result;
      int len = nums.size();

      for (int i = 0; i < len - 3; i++) {
         // Nhảy qua các phần tử trùng lặp cho i
         if (i > 0 && nums[i] == nums[i - 1]) continue;

         // Tối ưu (Pruning): Nếu 4 số nhỏ nhất đã lớn hơn target thì dừng luôn
         if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
         // Tối ưu (Pruning): Nếu i cộng với 3 số lớn nhất vẫn nhỏ hơn target thì bỏ qua i này
         if ((long long)nums[i] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target) continue;

         for (int j = i + 1; j < len - 2; j++) {
            // Nhảy qua các phần tử trùng lặp cho j
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            // Tối ưu tương tự cho j
            if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
            if ((long long)nums[i] + nums[j] + nums[len - 2] + nums[len - 1] < target) continue;

            int left = j + 1, right = len - 1;
            while (left < right) {
               long long total = (long long)nums[i] + nums[j] + nums[left] + nums[right];

               if (total < target) {
                  left++;
               } else if (total > target) {
                  right--;
               } else {
                  result.push_back({nums[i], nums[j], nums[left], nums[right]});

                  // Nhảy qua các phần tử trùng lặp
                  while (left < right && nums[left] == nums[left + 1]) left++;
                  while (left < right && nums[right] == nums[right - 1]) right--;

                  left++;
                  right--;
               }
            }
         }
      }

      return result;
   }
};

int main() {

   int n, target;
   if (!(cin >> n >> target)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   vector<vector<int>> result = sol.fourSum(nums, target);

   for (int i = 0; i < result.size(); i++) {
      Utils::printVector(result[i]);
   }

   return 0;
}
