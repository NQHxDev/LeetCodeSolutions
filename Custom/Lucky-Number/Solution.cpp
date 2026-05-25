#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int countLuckyNumbers(int n) {
      vector<long long> luckyNumbers;
      queue<long long> q;
      q.push(4);
      q.push(7);
      
      while (!q.empty()) {
         long long curr = q.front();
         q.pop();
         
         luckyNumbers.push_back(curr);
         
         long long next1 = curr * 10 + 4;
         long long next2 = curr * 10 + 7;
         
         if (next1 <= 1000000000LL) {
            q.push(next1);
         }
         if (next2 <= 1000000000LL) {
            q.push(next2);
         }
      }
      
      sort(luckyNumbers.begin(), luckyNumbers.end());
      
      auto it = upper_bound(luckyNumbers.begin(), luckyNumbers.end(), n);
      return distance(luckyNumbers.begin(), it);
   }
};

int main() {
   int n;
   if (cin >> n) {
      Solution sol;
      cout << sol.countLuckyNumbers(n) << endl;
   }
   return 0;
}
