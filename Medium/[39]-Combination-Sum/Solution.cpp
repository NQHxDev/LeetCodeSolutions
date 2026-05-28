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

         current.push_back(candidates[i]);
         // Tiếp tục đệ quy tại vị trí i để cho phép chọn lại chữ số đó
         backtrack(candidates, target - candidates[i], i, current, result);
         // Quay lui: bỏ phần tử vừa chọn để thử phương án khác
         current.pop_back();
      }
   }

public:
   vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      vector<vector<int>> result;
      vector<int> current;

      // Sắp xếp tăng dần để hỗ trợ tối ưu hóa cắt tỉa nhánh cận
      sort(candidates.begin(), candidates.end());

      backtrack(candidates, target, 0, current, result);
      return result;
   }
};

int main() {

   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   vector<int> candidates = Utils::readVector<int>();

   int target;
   if (!(cin >> target)) return 0;

   Solution sol;
   vector<vector<int>> result = sol.combinationSum(candidates, target);

   for (const auto& comb : result) {
      cout << "[";
      for (size_t i = 0; i < comb.size(); ++i) {
         cout << comb[i] << (i == comb.size() - 1 ? "" : ",");
      }
      cout << "]\n";
   }

   return 0;
}
