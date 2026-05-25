#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int longestValidParentheses(string s) {
      int maxLength = 0;
      stack<int> st;
      st.push(-1);

      for (int i = 0; i < s.length(); ++i) {
         if (s[i] == '(') {
            st.push(i);
         } else {
            st.pop();
            if (st.empty()) {
               st.push(i);
            } else {
               maxLength = max(maxLength, i - st.top());
            }
         }
      }

      return maxLength;
   }
};

int main() {
   string s;
   if (cin >> s) {
      Solution sol;
      cout << sol.longestValidParentheses(s);
   } else {
      cout << 0;
   }
   return 0;
}
