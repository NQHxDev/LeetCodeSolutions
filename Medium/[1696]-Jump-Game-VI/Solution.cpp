#include "../../Utils/utils.h"

using namespace std;

#include <deque>

class Solution {
public:
   int maxResult(vector<int>& nums, int k) {
      int n = nums.size();
      if (n == 0) return 0;

      vector<int> dp(n, 0);
      dp[0] = nums[0];

      deque<int> dq;
      dq.push_back(0);

      for (int i = 1; i < n; ++i) {
         if (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
         }

         dp[i] = nums[i] + dp[dq.front()];

         while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
         }

         dq.push_back(i);
      }

      return dp[n - 1];
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> nums = Utils::readVector<int>(n);

   int k;
   if (!(cin >> k)) return 0;

   Solution sol;
   cout << sol.maxResult(nums, k);

   return 0;
}
