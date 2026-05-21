#include <iostream>

using namespace std;

class Solution {
public:
   int divide(int dividend, int divisor) {
      if (dividend == INT_MIN && divisor == -1) {
         return INT_MAX;
      }

      bool isNegative = (dividend < 0) ^ (divisor < 0);

      if (dividend > 0) {
         dividend = -dividend;
      }
      if (divisor > 0) {
         divisor = -divisor;
      }

      int quotient = 0;

      while (divisor >= dividend) {
         int tempDivisor = divisor;
         int tempQuotient = -1;

         while (tempDivisor >= INT_MIN - tempDivisor && tempDivisor + tempDivisor >= dividend) {
            tempDivisor += tempDivisor;
            tempQuotient += tempQuotient;
         }

         dividend -= tempDivisor;
         quotient += tempQuotient;
      }

      return isNegative ? quotient : -quotient;
   }
};

int main() {

   int dividend, divisor;
   if (!(cin >> dividend >> divisor)) return 0;

   Solution sol;
   cout << sol.divide(dividend, divisor);

   return 0;
}
