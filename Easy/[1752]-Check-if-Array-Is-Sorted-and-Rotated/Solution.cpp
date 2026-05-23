#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   bool check(vector<int>& nums) {
      int countRotate = 0;
      int n = nums.size();

      for (int i = 0; i < n; i++) {
         if (nums[i] > nums[(i + 1) % n]) {
            countRotate++;
         }
      }

      return countRotate <= 1;
   }
};

int main() {

   vector<int> nums = Utils::readVector<int>();

   Solution sol;
   cout << sol.check(nums);

   return 0;
}
