#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int strStr(string haystack, string needle) {
      int lenHay = haystack.length(), lenNeed = needle.length();
      if (lenHay < lenNeed) return -1;

      for (int i = 0; i <= lenHay - lenNeed; i++) {
         bool isMatch = true;
         for (int j = 0; j < lenNeed; j++) {
            if (haystack[i + j] != needle[j]) {
               isMatch = false;
               break;
            }
         }

         if (isMatch) {
            return i;
         }
      }

      return -1;
   }
};

int main() {

   string haystack, needle;
   if (!(getline(cin, haystack))) return 0;
   if (!(getline(cin, needle))) return 0;

   Solution sol;
   cout << sol.strStr(haystack, needle);

   return 0;
}
