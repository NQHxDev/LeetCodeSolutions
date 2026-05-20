#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
      int n = A.size();
      vector<int> result(n);
      vector<int> seen(n + 1, 0);
      int commonCount = 0;

      for (int i = 0; i < n; ++i) {
         seen[A[i]]++;
         if (seen[A[i]] == 2) {
            commonCount++;
         }

         seen[B[i]]++;
         if (seen[B[i]] == 2) {
            commonCount++;
         }

         result[i] = commonCount;
      }

      return result;
   }
};

int main() {

   vector<int> numsA = Utils::readVector<int>();
   vector<int> numsB = Utils::readVector<int>();

   Solution sol;
   vector<int> result = sol.findThePrefixCommonArray(numsA, numsB);

   Utils::printVector(result);

   return 0;
}
