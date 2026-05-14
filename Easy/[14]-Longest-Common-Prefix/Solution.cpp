#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   string longestCommonPrefix(vector<string>& strs) {
      if (strs.empty()) return "";

      string currPrefix = strs[0];

      for (int i = 1; i < strs.size(); i++) {
         while (!currPrefix.empty() && strs[i].find(currPrefix) != 0) {
            currPrefix.pop_back();
         }

         if (currPrefix.empty()) {
            return "";
         }
      }

      return currPrefix;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<string> strs = Utils::readVector<string>(n);

   Solution sol;
   string result = sol.longestCommonPrefix(strs);

   cout << result;

   return 0;
}
