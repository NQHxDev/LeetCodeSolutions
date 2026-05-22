#include <iostream>

using namespace std;

class Solution {
private:
   long long countBeautiful(long long N) {
      if (N <= 0) return 0;

      return N / 4 + N / 7 + N / 11
           - N / 28 - N / 44 - N / 77
           + N / 308;
   }

public:
   long long getBeautifulNumbersCount(long long L, long long R) {
      return countBeautiful(R) - (L > 0 ? countBeautiful(L - 1) : -1);
   }
};

int main() {

   int t;
   if (cin >> t) {
      Solution sol;
      while (t--) {
         long long L, R;
         if (cin >> L >> R) {
            cout << sol.getBeautifulNumbersCount(L, R) << "\n";
         }
      }
   }

   return 0;
}
