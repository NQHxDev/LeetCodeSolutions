#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   vector<int> maxValue(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return {};

      vector<int> prefixMax(n);
      prefixMax[0] = nums[0];
      for (int i = 1; i < n; ++i) {
         prefixMax[i] = max(prefixMax[i - 1], nums[i]);
      }

      vector<int> suffixMin(n);
      suffixMin[n - 1] = nums[n - 1];
      for (int i = n - 2; i >= 0; --i) {
         suffixMin[i] = min(suffixMin[i + 1], nums[i]);
      }

      vector<int> ans(n);
      int start = 0;
      for (int i = 1; i < n; ++i) {
         if (prefixMax[i - 1] <= suffixMin[i]) {
            int blockMax = prefixMax[i - 1];
            for (int j = start; j < i; ++j) {
               ans[j] = blockMax;
            }
            start = i;
         }
      }

      int blockMax = prefixMax[n - 1];
      for (int j = start; j < n; ++j) {
         ans[j] = blockMax;
      }

      return ans;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   Solution sol;
   vector<int> ans = sol.maxValue(nums);

   Utils::printVector(ans);

   return 0;
}
