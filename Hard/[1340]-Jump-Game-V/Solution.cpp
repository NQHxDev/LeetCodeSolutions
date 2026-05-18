#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   int n;
   vector<int> memo;

   int solve(int i, const vector<int>& arr, int d) {
      if (memo[i] != -1) return memo[i];

      int maxSteps = 1;

      for (int j = i + 1; j <= min(i + d, n - 1); ++j) {
         if (arr[j] >= arr[i]) break;
         maxSteps = max(maxSteps, 1 + solve(j, arr, d));
      }

      for (int j = i - 1; j >= max(0, i - d); --j) {
         if (arr[j] >= arr[i]) break;
         maxSteps = max(maxSteps, 1 + solve(j, arr, d));
      }

      return memo[i] = maxSteps;
   }

public:
   int maxJumps(vector<int>& arr, int d) {
      n = arr.size();
      if (n == 0) return 0;

      memo.assign(n, -1);
      int maxVisited = 0;

      for (int i = 0; i < n; ++i) {
         maxVisited = max(maxVisited, solve(i, arr, d));
      }

      return maxVisited;
   }
};

int main() {

   int n, d;
   if (!(cin >> n >> d)) return 0;

   vector<int> arr = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.maxJumps(arr, d);

   return 0;
}
