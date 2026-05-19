#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
   int lengthOfLastWord(string s) {
      bool isStart = false;
      int lenWord = 0;

      for (int i = s.length() - 1; i >= 0; i--) {
         if (s[i] == ' ') {
            if (isStart) return lenWord;

            continue;
         }

         if (!isStart) isStart = true;

         lenWord++;
      }

      return lenWord;
   }
};

int main() {

   string s;
   if (!getline(cin, s)) return 0;

   Solution sol;
   cout << sol.lengthOfLastWord(s);

   return 0;
}
