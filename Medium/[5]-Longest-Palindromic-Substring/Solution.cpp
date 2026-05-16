#include <iostream>

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
   string longestPalindrome(string s) {
      if (s.length() < 1) return "";

      int start = 0, maxLength = 0;

      for (int i = 0; i < s.length(); i++) {
         // Trường hợp 1: Tâm là 1 ký tự (Lẻ)
         int len1 = expandAroundCenter(s, i, i);

         // Trường hợp 2: Tâm là khe giữa 2 ký tự (Chẵn)
         int len2 = expandAroundCenter(s, i, i + 1);

         int len = max(len1, len2);
         if (len > maxLength) {
            maxLength = len;
            start = i - (len - 1) / 2;
         }
      }

      return s.substr(start, maxLength);
   }

private:
   int expandAroundCenter(string s, int left, int right) {
      while (left >= 0 && right < s.length() && s[left] == s[right]) {
         left--;
         right++;
      }

      return right - left - 1;
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   Solution sol;
   string result = sol.longestPalindrome(s);

   cout << result;

   return 0;
}
