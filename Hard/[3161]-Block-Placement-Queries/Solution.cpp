#include "../../Utils/utils.h"

using namespace std;

// Segment Tree hỗ trợ quản lý khoảng trống lớn nhất giữa các chướng ngại vật
class SegmentTree {
private:
   int n;
   vector<int> tree;

public:
   SegmentTree(int size) {
      n = size;
      tree.assign(4 * n, 0);
   }

   // Cập nhật giá trị tại vị trí idx
   void update(int node, int start, int end, int idx, int val) {
      if (start == end) {
         tree[node] = val;
         return;
      }
      int mid = start + (end - start) / 2;
      if (idx <= mid) {
         update(2 * node, start, mid, idx, val);
      } else {
         update(2 * node + 1, mid + 1, end, idx, val);
      }
      tree[node] = max(tree[2 * node], tree[2 * node + 1]);
   }

   // Truy vấn giá trị lớn nhất trong đoạn [l, r]
   int query(int node, int start, int end, int l, int r) {
      if (r < start || end < l) {
         return 0;
      }
      if (l <= start && end <= r) {
         return tree[node];
      }
      int mid = start + (end - start) / 2;
      return max(query(2 * node, start, mid, l, r),
                 query(2 * node + 1, mid + 1, end, l, r));
   }
};

class Solution {
public:
   vector<bool> getResults(vector<vector<int>>& queries) {
      int max_x = 0;
      for (const auto& q : queries) {
         max_x = max(max_x, q[1]);
      }

      // Khởi tạo Segment Tree với phạm vi từ 0 đến max_x
      SegmentTree st(max_x + 1);
      
      // Tập hợp các chướng ngại vật, luôn bắt đầu với gốc tọa độ 0
      set<int> obstacles;
      obstacles.insert(0);

      vector<bool> results;
      for (const auto& q : queries) {
         int type = q[0];
         if (type == 1) {
            int x = q[1];
            auto it = obstacles.upper_bound(x);
            int prev_obs = *std::prev(it);
            
            // Nếu tồn tại chướng ngại vật phía sau x
            if (it != obstacles.end()) {
               int next = *it;
               // Cập nhật lại khoảng trống mới giữa next và x
               st.update(1, 0, max_x, next, next - x);
            }
            // Cập nhật khoảng trống giữa x và prev_obs
            st.update(1, 0, max_x, x, x - prev_obs);
            obstacles.insert(x);
         } else {
            int x = q[1];
            int sz = q[2];
            
            // Tìm chướng ngại vật lớn nhất nhỏ hơn hoặc bằng x
            auto it = obstacles.upper_bound(x);
            int prev_obs = *std::prev(it);
            
            // Tìm khoảng trống lớn nhất hoàn toàn nằm trong [0, prev_obs]
            int max_gap = st.query(1, 0, max_x, 0, prev_obs);
            
            // Khoảng trống cuối cùng kéo dài từ prev_obs đến vị trí truy vấn x
            int last_gap = x - prev_obs;
            
            // Kiểm tra xem có thể đặt được khối có kích thước sz hay không
            results.push_back(max(max_gap, last_gap) >= sz);
         }
      }
      return results;
   }
};

int main() {
   // Tối ưu hóa tốc độ nhập xuất
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int q;
   if (!(cin >> q)) return 0;

   vector<vector<int>> queries;
   for (int i = 0; i < q; ++i) {
      int type;
      if (!(cin >> type)) break;
      if (type == 1) {
         int x;
         cin >> x;
         queries.push_back({type, x});
      } else if (type == 2) {
         int x, sz;
         cin >> x >> sz;
         queries.push_back({type, x, sz});
      }
   }

   Solution sol;
   vector<bool> result = sol.getResults(queries);

   for (size_t i = 0; i < result.size(); ++i) {
      cout << (result[i] ? "true" : "false") << (i == result.size() - 1 ? "" : " ");
   }
   cout << "\n";

   return 0;
}
