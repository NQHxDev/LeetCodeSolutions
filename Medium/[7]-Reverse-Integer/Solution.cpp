#include <iostream>

#include <climits>

using namespace std;

class Solution {
public:
   int reverse(int x) {
      int reversed_num = 0;
      while (x != 0) {
         int pop = x % 10;

         if (reversed_num > INT_MAX / 10 || (reversed_num == INT_MAX / 10 && pop > 7)) {
            return 0;
         }

         if (reversed_num < INT_MIN / 10 || (reversed_num == INT_MIN / 10 && pop < -8)) {
            return 0;
         }

         reversed_num = reversed_num * 10 + pop;
         x /= 10;
      }

      return reversed_num;
   }
};

int main() {

   int x;
   if (!(cin >> x)) return 0;

   Solution sol;
   cout << sol.reverse(x);

   return 0;
}
