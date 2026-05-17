#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int maxArea(vector<int>& height) {
      int max_area = 0;
      int left = 0;
      int right = height.size() - 1;

      while (left < right) {
         int h = min(height[left], height[right]);
         int w = right - left;
         int current_area = h * w;

         max_area = max(max_area, current_area);

         if (height[left] < height[right]) {
            left++;
         } else {
            right--;
         }
      }

      return max_area;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> height = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.maxArea(height);

   return 0;
}
