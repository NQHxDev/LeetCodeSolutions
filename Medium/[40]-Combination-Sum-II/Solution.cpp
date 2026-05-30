#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   void backtrack(const vector<int>& candidates, int target, int idx, vector<int>& current, vector<vector<int>>& result) {
      if (target == 0) {
         result.push_back(current);
         return;
      }

      for (int i = idx; i < candidates.size(); ++i) {
         // Nhánh cận: dừng tìm kiếm nếu phần tử hiện tại lớn hơn mục tiêu còn lại
         if (candidates[i] > target) {
            break;
         }

         // Bỏ qua các phần tử trùng lặp ở cùng một cấp độ đệ quy
         if (i > idx && candidates[i] == candidates[i - 1]) {
            continue;
         }

         current.push_back(candidates[i]);
         // Đi tới phần tử tiếp theo (i + 1) để tránh tái sử dụng phần tử hiện tại
         backtrack(candidates, target - candidates[i], i + 1, current, result);
         // Quay lui: bỏ phần tử vừa thêm
         current.pop_back();
      }
   }

public:
   vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
      vector<vector<int>> result;
      vector<int> current;

      // Sắp xếp tăng dần để nhóm các phần tử trùng lặp và phục vụ cắt tỉa nhánh cận
      sort(candidates.begin(), candidates.end());

      backtrack(candidates, target, 0, current, result);
      return result;
   }
};

int main() {

   vector<int> candidates = Utils::readVector<int>();

   int target;
   if (!(cin >> target)) return 0;

   Solution sol;
   vector<vector<int>> result = sol.combinationSum2(candidates, target);

   cout << "[";
   for (int i = 0; i < result.size(); i++) {
      cout << "[";
      Utils::printVector(result[i]);
      cout << "]" << endl;
   }
   cout << "]";

   return 0;
}
