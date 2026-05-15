#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   bool isOpenBracket(char ch) {
      return ch == '(' || ch == '{' || ch == '[';
   }

   bool isMatch(char open, char close) {
      if (open == '(') return close == ')';
      if (open == '{') return close == '}';
      if (open == '[') return close == ']';

      return false;
   }

public:
   bool isValid(string s) {
      stack<char> parenthesesStack;

      for (char ch : s) {
         if (isOpenBracket(ch)) {
            parenthesesStack.push(ch);
            continue;
         }

         if (parenthesesStack.empty() || !isMatch(parenthesesStack.top(), ch)) {
            return false;
         }
         parenthesesStack.pop();
      }

      return parenthesesStack.empty();
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   Solution sol;
   cout << sol.isValid(s);

   return 0;
}
