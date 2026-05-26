#include "../../Utils/utils.h"

using namespace std;

// Giá trị vô cùng lớn dùng để khởi tạo khoảng cách
const long long INF = 1e18;

// Cấu trúc mô tả cạnh của đồ thị
struct Edge {
   int to;
   long long weight;
};

class Solution {
private:
   // Thuật toán Dijkstra tìm khoảng cách ngắn nhất từ một nguồn tới mọi nút khác
   vector<long long> dijkstra(int n, int start_node, const vector<vector<Edge>>& adj) {
      vector<long long> dist(n + 1, INF);
      priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

      dist[start_node] = 0;
      pq.push({0, start_node});

      while (!pq.empty()) {
         auto [d, u] = pq.top();
         pq.pop();

         if (d > dist[u]) {
            continue;
         }

         for (const auto& edge : adj[u]) {
            if (dist[edge.to] > dist[u] + edge.weight) {
               dist[edge.to] = dist[u] + edge.weight;
               pq.push({dist[edge.to], edge.to});
            }
         }
      }
      return dist;
   }

public:
   // Hàm tìm lượng nước thất thoát ít nhất sau khi lắp đặt tối ưu ống nước máy bơm
   long long minWaterLoss(int n, int m, int s, int t, int k,
                         const vector<vector<Edge>>& adj,
                         const vector<vector<Edge>>& radj,
                         const vector<pair<pair<int, int>, long long>>& pumps) {
      // Chạy Dijkstra từ nguồn s trên đồ thị gốc
      vector<long long> dist_s = dijkstra(n, s, adj);

      // Chạy Dijkstra từ bồn tắm t trên đồ thị đảo ngược
      vector<long long> dist_t = dijkstra(n, t, radj);

      // Khởi tạo kết quả bằng khoảng cách ngắn nhất trực tiếp khi không dùng máy bơm
      long long ans = dist_s[t];

      // Duyệt qua từng ứng viên lắp đặt ống máy bơm
      for (const auto& pump : pumps) {
         int u = pump.first.first;
         int v = pump.first.second;
         long long q = pump.second;

         // Hướng đi: s -> u -> v -> t
         if (dist_s[u] != INF && dist_t[v] != INF) {
            ans = min(ans, dist_s[u] + q + dist_t[v]);
         }
         // Hướng đi: s -> v -> u -> t (vì ống máy bơm là hai chiều)
         if (dist_s[v] != INF && dist_t[u] != INF) {
            ans = min(ans, dist_s[v] + q + dist_t[u]);
         }
      }

      return (ans == INF) ? -1 : ans;
   }
};

int main() {
   // Tối ưu hóa tốc độ luồng nhập xuất
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n, m, k, s, t;
   if (!(cin >> n >> m >> k >> s >> t)) {
      return 0;
   }

   vector<vector<Edge>> adj(n + 1);
   vector<vector<Edge>> radj(n + 1);

   // Đọc các đường ống một chiều của đồ thị gốc
   for (int i = 0; i < m; ++i) {
      int u, v;
      long long c;
      cin >> u >> v >> c;
      adj[u].push_back({v, c});
      radj[v].push_back({u, c});
   }

   // Đọc các vị trí ứng viên lắp đặt ống máy bơm
   vector<pair<pair<int, int>, long long>> pumps;
   for (int i = 0; i < k; ++i) {
      int u, v;
      long long q;
      if (cin >> u >> v >> q) {
         pumps.push_back({{u, v}, q});
      }
   }

   Solution sol;
   cout << sol.minWaterLoss(n, m, s, t, k, adj, radj, pumps);

   return 0;
}
