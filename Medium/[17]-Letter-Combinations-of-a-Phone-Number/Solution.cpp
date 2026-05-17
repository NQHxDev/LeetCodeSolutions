#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   const vector<string> phoneMap = {
      "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
   };

   void backtrack(int index, const string& digits, string& current, vector<string>& result) {
      if (index == digits.length()) {
         result.push_back(current);
         return;
      }

      string letters = phoneMap[digits[index] - '0'];
      for (char c : letters) {
         current.push_back(c);
         backtrack(index + 1, digits, current, result);
         current.pop_back();
      }
   }

public:
   vector<string> letterCombinations(string digits) {
      if (digits.empty()) {
         return {};
      }

      vector<string> result;
      string current = "";
      backtrack(0, digits, current, result);
      return result;
   }
};

int main() {

   string digits;
   if (!(getline(cin, digits))) return 0;

   Solution sol;
   vector<string> result = sol.letterCombinations(digits);

   Utils::printVector(result);

   return 0;
}
