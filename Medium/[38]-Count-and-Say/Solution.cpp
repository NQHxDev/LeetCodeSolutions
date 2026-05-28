#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   string countAndSay(int n) {
      if (n == 1) {
         return "1";
      }

      string current = "1";
      // Lặp lại n - 1 lần để sinh ra chuỗi thứ n
      for (int step = 2; step <= n; ++step) {
         string next_str = "";
         int i = 0;
         int len = current.length();

         // Duyệt và gom nhóm các chữ số giống nhau liên tiếp
         while (i < len) {
            char curr_char = current[i];
            int count = 0;

            // Đếm số lần xuất hiện liên tiếp của chữ số hiện tại
            while (i < len && current[i] == curr_char) {
               count++;
               i++;
            }

            // Ghép số lượng và chữ số tương ứng vào chuỗi kết quả mới
            next_str += to_string(count) + curr_char;
         }
         current = next_str;
      }

      return current;
   }
};

int main() {

   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n;
   if (!(cin >> n)) return 0;

   Solution sol;
   cout << sol.countAndSay(n) << "\n";

   return 0;
}
