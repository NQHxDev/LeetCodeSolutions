#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int countTernaryStrings(int n) {
      if (n == 0) return 1;
      if (n == 1) return 3;
      
      const int MOD = 1e9 + 7;
      long long prev2 = 1; // S_0
      long long prev1 = 3; // S_1
      long long curr = 0;
      
      for (int i = 2; i <= n; ++i) {
         curr = (2 * prev1 + 2 * prev2) % MOD;
         prev2 = prev1;
         prev1 = curr;
      }
      
      return curr;
   }
};

int main() {
   int n;
   if (cin >> n) {
      Solution sol;
      cout << sol.countTernaryStrings(n) << endl;
   }
   return 0;
}
