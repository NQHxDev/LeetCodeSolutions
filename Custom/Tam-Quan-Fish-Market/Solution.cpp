#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
   long long x;
   double d_slope;
   bool is_query;
   bool operator<(const Event& other) const {
      if (x != other.x) return x < other.x;
      if (is_query != other.is_query) return is_query < other.is_query;
      return d_slope < other.d_slope;
   }
};

class Solution {
public:
   long long maxFish(int n, long long k, const vector<long long>& T, const vector<long long>& F, const vector<long long>& D) {
      vector<Event> events;
      events.reserve(5 * n + 1);

      for (int i = 0; i < n; ++i) {
         long long A = T[i];
         long long B = T[i] + D[i];
         double R = (double)F[i] / D[i];

         events.push_back({A - k, R, false});
         events.push_back({A, -R, false});
         events.push_back({B - k, -R, false});
         events.push_back({B, R, false});

         // Thêm điểm truy vấn tại T_i
         events.push_back({A, 0.0, true});
      }

      // Thêm điểm truy vấn tại 0
      events.push_back({0, 0.0, true});

      sort(events.begin(), events.end());

      double cur_val = 0.0;
      double cur_slope = 0.0;
      double max_val = 0.0;
      long long prev_x = events[0].x;

      for (const auto& ev : events) {
         long long delta_x = ev.x - prev_x;
         cur_val += cur_slope * delta_x;
         if (ev.is_query && ev.x >= 0) {
            max_val = max(max_val, cur_val);
         }
         cur_slope += ev.d_slope;
         prev_x = ev.x;
      }

      return (long long)(max_val + 1e-9);
   }
};

int main() {

   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   int n;
   long long k;
   if (!(cin >> n >> k)) return 0;

   vector<long long> T(n), F(n), D(n);
   for (int i = 0; i < n; ++i) {
      cin >> T[i] >> F[i] >> D[i];
   }

   Solution sol;
   cout << sol.maxFish(n, k, T, F, D);

   return 0;
}
