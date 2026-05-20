#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   bool isGood(int num) {
      bool hasChangedDigit = false;
      while (num > 0) {
         int digit = num % 10;
         if (digit == 3 || digit == 4 || digit == 7) {
            return false;
         }
         if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
            hasChangedDigit = true;
         }
         num /= 10;
      }
      return hasChangedDigit;
   }

public:
   int rotatedDigits(int n) {
      int count = 0;
      for (int i = 1; i <= n; ++i) {
         if (isGood(i)) {
            count++;
         }
      }

      return count;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   Solution sol;
   cout << sol.rotatedDigits(n) << endl;

   return 0;
}
