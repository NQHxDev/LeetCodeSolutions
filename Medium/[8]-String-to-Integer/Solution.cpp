#include <iostream>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
   int myAtoi(string s) {
      int index = 0;
      int n = s.length();

      while (index < n && s[index] == ' ') {
         index++;
      }

      int sign = 1;
      if (index < n && (s[index] == '+' || s[index] == '-')) {
         if (s[index] == '-') {
            sign = -1;
         }
         index++;
      }

      int result = 0;
      while (index < n && s[index] >= '0' && s[index] <= '9') {
         int digit = s[index] - '0';
         if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
            return (sign == 1) ? INT_MAX : INT_MIN;
         }

         result = result * 10 + digit;
         index++;
      }

      return result * sign;
   }
};

int main() {

   string str;
   if (!(getline(cin, str))) return 0;

   Solution sol;
   cout << sol.myAtoi(str) << endl;

   return 0;
}
