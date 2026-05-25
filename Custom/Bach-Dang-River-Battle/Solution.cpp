#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Cấu trúc Disjoint Set Union để quản lý các tập hợp liên thông
struct DSU {
   vector<int> parent;
   vector<int> rank;

   DSU(int n) {
      parent.resize(n);
      for (int i = 0; i < n; ++i) parent[i] = i;
      rank.assign(n, 0);
   }

   int find(int u) {
      if (u == parent[u]) return u;
      return parent[u] = find(parent[u]); // Nén đường (path compression)
   }

   bool unite(int u, int v) {
      int root_u = find(u);
      int root_v = find(v);
      if (root_u != root_v) {
         if (rank[root_u] < rank[root_v]) {
            swap(root_u, root_v);
         }
         parent[root_v] = root_u;
         if (rank[root_u] == rank[root_v]) {
            rank[root_u]++;
         }
         return true;
      }
      return false;
   }

   bool isConnected(int u, int v) {
      return find(u) == find(v);
   }
};

// Cấu trúc mô tả thông tin của một cọc gỗ
struct Pile {
   int id;        // Chỉ số ban đầu của cọc (1-indexed)
   long long x;   // Tọa độ x
   long long y;   // Tọa độ y
   long long h;   // Độ cao cọc

   // Sắp xếp cọc gỗ theo độ cao giảm dần để xử lý khi mực nước rút
   bool operator<(const Pile& other) const {
      return h > other.h;
   }
};

int main() {
   // Tối ưu hóa tốc độ nhập xuất
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n;
   long long w, d;
   if (!(cin >> n >> w >> d)) return 0;

   vector<Pile> piles(n);
   for (int i = 0; i < n; ++i) {
      piles[i].id = i + 1;
      cin >> piles[i].x >> piles[i].y >> piles[i].h;
   }

   // Nếu sông quá hẹp cho thuyền, mặc định bị chặn từ đầu
   if (w < d) {
      // In ra mực nước cao vô hạn (hoặc giá trị độ cao tối đa của cọc gỗ)
      // Trong thực tế dữ liệu đảm bảo W >= D, nhưng ta xử lý phòng hờ
      cout << -1 << "\n";
      return 0;
   }

   // Sắp xếp các cọc gỗ theo độ cao giảm dần
   sort(piles.begin(), piles.end());

   // Khởi tạo DSU với N + 2 phần tử:
   // - Đỉnh 0: bờ sông phía nam (y = 0)
   // - Đỉnh N + 1: bờ sông phía bắc (y = W)
   // - Đỉnh 1 đến N: các cọc gỗ (tương ứng id của cọc)
   DSU dsu(n + 2);

   // Mảng đánh dấu các cọc đã nhô lên mặt nước
   vector<bool> active(n + 2, false);
   vector<Pile> active_piles;

   long long d_sq = d * d;

   for (int i = 0; i < n; ++i) {
      const auto& p = piles[i];

      // Kích hoạt cọc hiện tại
      active[p.id] = true;

      // 1. Kiểm tra liên kết với bờ nam (y = 0)
      if (p.y < d) {
         dsu.unite(p.id, 0);
      }

      // 2. Kiểm tra liên kết với bờ bắc (y = W)
      if (w - p.y < d) {
         dsu.unite(p.id, n + 1);
      }

      // 3. Kiểm tra liên kết với các cọc đã nhô lên trước đó
      for (const auto& ap : active_piles) {
         long long dx = p.x - ap.x;
         long long dy = p.y - ap.y;
         long long dist_sq = dx * dx + dy * dy;

         // Nếu khoảng cách bình phương nhỏ hơn D^2, gộp nhóm chúng
         if (dist_sq < d_sq) {
            dsu.unite(p.id, ap.id);
         }
      }

      // Thêm cọc hiện tại vào danh sách các cọc đã hoạt động
      active_piles.push_back(p);

      // Nếu bờ nam (0) và bờ bắc (N+1) đã được kết nối thông suốt
      if (dsu.isConnected(0, n + 1)) {
         cout << p.h << "\n";
         return 0;
      }
   }

   // Nếu duyệt qua toàn bộ cọc vẫn không thể chặn được sông
   cout << -1 << "\n";

   return 0;
}
