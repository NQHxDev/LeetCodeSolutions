#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
      unordered_set<int> prefixes;

      for (int num : arr1) {
         while (num > 0) {
            prefixes.insert(num);
            num /= 10;
         }
      }

      int resultLongest = 0;

      for (int num : arr2) {
         int len = 0;
         int temp = num;
         while (temp > 0) {
            len++;
            temp /= 10;
         }

         while (num > 0) {
            if (len <= resultLongest) {
               break;
            }

            if (prefixes.count(num)) {
               resultLongest = len;
               break;
            }

            num /= 10;
            len--;
         }
      }

      return resultLongest;
   }
};

int main() {

   vector<int> nums1 = Utils::readVector<int>();
   vector<int> nums2 = Utils::readVector<int>();

   Solution sol;
   cout << sol.longestCommonPrefix(nums1, nums2);

   return 0;
}
