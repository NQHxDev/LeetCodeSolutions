#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int lengthOfLongestSubstring(string s) {

      unordered_map<char, int> lastSeen;
      int left = 0, maxLen = 0;

      for (int i = 0; i < s.length(); i++) {
         char curChar = s[i];

         if (lastSeen.find(curChar) != lastSeen.end()) {
            left = max(left, lastSeen[curChar] + 1);
         }

         lastSeen[curChar] = i;

         maxLen = max(maxLen, i - left + 1);
      }

      return maxLen;
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   Solution sol;
   int result = sol.lengthOfLongestSubstring(s);

   cout << result << endl;

   return 0;
}
