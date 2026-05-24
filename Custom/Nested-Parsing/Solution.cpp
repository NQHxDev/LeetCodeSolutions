#include "../../Utils/utils.h"

using namespace std;

using ll = long long;

class Solution {
private:
   // Hàm chạy quy hoạch động để kiểm tra xem một giá trị k có tạo thành k-quote hợp lệ hay không
   bool checkWithK(const vector<int>& a, int k, int s_0) {
      int n = a.size();

      // Tiền tính toán giá trị f(x) đại diện cho tổng số dấu nháy khi mở/đóng x cấp liên tiếp
      vector<ll> F(k + 1);
      for (int i = 0; i <= k; ++i) {
         F[i] = (ll) i * k - (ll) i * (i - 1) / 2;
      }

      vector<int> active_states;
      active_states.push_back(s_0); // Khởi tạo với kích thước ngăn xếp s_0 tương ứng của ứng viên k

      for (int i = 1; i < n; i++) {
         long long val = a[i];
         vector<bool> reached(k + 1, false);

         // Ở các bước trung gian (i < n - 1), ngăn xếp không được phép rỗng (si >= 1)
         // Ở bước cuối cùng (i == n - 1), ngăn xếp bắt buộc phải trở về rỗng (si = 0)
         int min_si = (i < n - 1) ? 1 : 0;
         int max_si = (i < n - 1) ? k : 0;

         for (int s : active_states) {
            for (int si = min_si; si <= max_si; si++) {
               ll target = F[s] + F[si] - val;
               if (target % 2 != 0) continue; // Phép toán đóng/mở bên trong phải có số nháy chẵn

               ll x = target / 2;
               int min_sp = 0;

               if (x > 0) {
                  auto it = lower_bound(F.begin(), F.end(), x);
                  if (it == F.end()) continue;
                  min_sp = distance(F.begin(), it);
               }

               int limit_sp = min(s, si);
               for (int sp = min_sp; sp <= limit_sp; sp++) {
                  ll diff = val - (F[s] + F[si] - 2 * F[sp]);
                  if (diff == 0) {
                     reached[si] = true;
                     break;
                  } else if (sp < k) {
                     int max_state = max(s, si);
                     int yO = min(max_state, k - 1);
                     ll min_required = (ll) (k - yO) * (k - yO + 1);
                     if (diff >= min_required) {
                        reached[si] = true;
                        break;
                     }
                  }
               }
            }
         }

         active_states.clear();
         for (int s = 0; s <= k; s++) {
            if (reached[s]) {
               active_states.push_back(s);
            }
         }

         if (active_states.empty()) {
            return false;
         }
      }

      for (int s : active_states) {
         if (s == 0) return true;
      }

      return false;
   }

public:
   string getQuoteLevel(const vector<int>& a) {
      int n = a.size();
      if (n < 1) return "no-quote";

      // Trường hợp đặc biệt: N = 1 (toàn bộ chuỗi chỉ có 1 nhóm dấu nháy duy nhất, không có văn bản)
      if (n == 1) {
         ll val = a[0];
         if (val % 2 != 0) return "no-quote";

         ll k = (-1.0 + sqrt(1.0 + 4.0 * val)) / 2.0;
         if (k * (k + 1) <= val) {
            return to_string(k);
         }
         return "no-quote";
      }

      ll sum_a = 0;
      for (int val : a) {
         sum_a += val;
      }

      // Giới hạn trên của k dựa trên tổng số dấu nháy và nhóm đầu/cuối
      ll max_k_limit = (-1.0 + sqrt(1.0 + 4.0 * sum_a)) / 2.0;
      ll K_max = min({(long long)a[0], (long long)a[n - 1], max_k_limit});

      // Duyệt trực tiếp k từ K_max xuống 1
      for (int k = K_max; k >= 1; --k) {
         vector<long long> F(k + 1);
         for (int x = 0; x <= k; ++x) {
            F[x] = (long long)x * k - (long long)x * (x - 1) / 2;
         }

         // Tìm tất cả các s0 hợp lệ cho a[0] dưới dạng s0 cấp mở đầu tiên
         vector<int> valid_s0;
         for (int s0 = 1; s0 <= k; ++s0) {
            if (F[s0] <= a[0]) {
               long long diff = a[0] - F[s0];
               if (diff % 2 == 0) {
                  bool ok = true;
                  if (diff > 0) {
                     int y_opt = min(s0, k - 1);
                     long long min_required = (long long)(k - y_opt) * (k - y_opt + 1);
                     if (diff < min_required) ok = false;
                  }
                  if (ok) {
                     valid_s0.push_back(s0);
                  }
               }
            }
         }

         if (valid_s0.empty()) continue;

         // Kiểm tra xem có s_n hợp lệ cho a[n-1] (bước đóng cuối cùng) hay không
         bool has_valid_sn = false;
         for (int sn = 1; sn <= k; ++sn) {
            if (F[sn] <= a[n - 1]) {
               long long diff = a[n - 1] - F[sn];
               if (diff % 2 == 0) {
                  bool ok = true;
                  if (diff > 0) {
                     int y_opt = min(sn, k - 1);
                     long long min_required = (long long)(k - y_opt) * (k - y_opt + 1);
                     if (diff < min_required) ok = false;
                  }
                  if (ok) {
                     has_valid_sn = true;
                     break;
                  }
               }
            }
         }

         if (!has_valid_sn) continue;

         // Chạy DP cho từng s0 hợp lệ
         for (int s0 : valid_s0) {
            if (checkWithK(a, k, s0)) {
               return to_string(k);
            }
         }
      }

      return "no-quote";
   }
};

int main() {
   int n;
   if (!(cin >> n)) return 0;

   vector<int> a = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.getQuoteLevel(a);

   return 0;
}
