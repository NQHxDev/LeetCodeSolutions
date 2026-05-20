#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   bool rotateString(string s, string goal) {
      if (s.length() != goal.length()) return false;

      string circleString = s + s;

      return circleString.find(goal) != string::npos;
   }
};

int main() {

   string s, goal;
   if (!getline(cin, s) || !getline(cin, goal)) return 0;

   Solution sol;
   cout << sol.rotateString(s, goal);

   return 0;
}
