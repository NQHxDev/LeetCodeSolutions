#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   void backtrack(int open, int close, int n, string& current, vector<string>& result) {
      if (current.length() == 2 * n) {
         result.push_back(current);
         return;
      }

      if (open < n) {
         current.push_back('(');
         backtrack(open + 1, close, n, current, result);
         current.pop_back();
      }

      if (close < open) {
         current.push_back(')');
         backtrack(open, close + 1, n, current, result);
         current.pop_back();
      }
   }

public:
   vector<string> generateParenthesis(int n) {
      vector<string> result;
      string current = "";
      backtrack(0, 0, n, current, result);
      return result;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   Solution sol;
   vector<string> result = sol.generateParenthesis(n);

   Utils::printVector(result);

   return 0;
}
