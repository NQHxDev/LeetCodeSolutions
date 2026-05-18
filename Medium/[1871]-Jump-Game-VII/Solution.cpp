#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
   bool canReach(string s, int minJump, int maxJump) {
      int n = s.length();
      if (s[n - 1] != '0') return false;

      queue<int> q;
      q.push(0);
      int maxVisited = 0;

      while (!q.empty()) {
         int curr = q.front();
         q.pop();

         if (curr == n - 1) return true;

         int start = max(curr + minJump, maxVisited + 1);
         int end = min(curr + maxJump, n - 1);

         for (int j = start; j <= end; ++j) {
            if (s[j] == '0') {
               q.push(j);
            }
         }

         maxVisited = max(maxVisited, curr + maxJump);
      }

      return false;
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   int minJump, maxJump;
   if (!(cin >> minJump >> maxJump)) return 0;

   Solution solution;
   cout << (solution.canReach(s, minJump, maxJump));

   return 0;
}
