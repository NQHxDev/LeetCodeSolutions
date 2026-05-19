#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int getCommon(vector<int>& nums1, vector<int>& nums2) {
      int i = 0;
      int j = 0;
      int n1 = nums1.size();
      int n2 = nums2.size();

      while (i < n1 && j < n2) {
         if (nums1[i] == nums2[j]) {
            return nums1[i];
         }
         if (nums1[i] < nums2[j]) {
            i++;
         } else {
            j++;
         }
      }

      return -1;
   }
};

int main() {

   int n, m;
   if (!(cin >> n >> m)) return 0;

   vector<int> nums1 = Utils::readVector<int>(n);
   vector<int> nums2 = Utils::readVector<int>(m);

   Solution sol;
   cout << sol.getCommon(nums1, nums2);

   return 0;
}
