#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   pair<long long, long long> calculateInitialSums(const vector<int>& nums) {
      long long totalSum = 0;
      long long initialF = 0;
      long long n = nums.size();
      for (long long i = 0; i < n; ++i) {
         totalSum += nums[i];
         initialF += i * nums[i];
      }

      return {totalSum, initialF};
   }

public:
   int maxRotateFunction(vector<int>& nums) {
      long long n = nums.size();
      pair<long long, long long> initialSums = calculateInitialSums(nums);
      long long totalSum = initialSums.first;
      long long currentF = initialSums.second;
      long long maxF = currentF;

      for (int i = 1; i < n; ++i) {
         currentF = currentF + totalSum - n * nums[n - i];
         maxF = max(maxF, currentF);
      }

      return maxF;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   Solution sol;
   cout << sol.maxRotateFunction(nums);

   return 0;
}
