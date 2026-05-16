#include <iostream>

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
   string convert(string s, int numRows) {
      int len = s.length();

      if (numRows == 1 || len <= numRows) {
         return s;
      }

      vector<string> rows(numRows);
      int currentRow = 0;
      bool goingDown = false;

      for (char c : s) {
         rows[currentRow] += c;

         if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
         }

         currentRow += goingDown ? 1 : -1;
      }

      string result = "";
      for (const string& row : rows) {
         result += row;
      }

      return result;
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   Solution sol;
   cout << sol.convert(s, 3) << endl;

   return 0;
}
