#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   int memo[31][31]; // Lưu trữ trạng thái đã tính toán: -1 (chưa tính), 0 (false), 1 (true)

   bool solve(int i, int j, const string& s, const string& p) {
      if (memo[i][j] != -1) return memo[i][j]; // Trả về kết quả nếu đã được tính toán trước đó

      bool result;
      if (j == p.length()) {
         result = (i == s.length()); // Kiểm tra khớp hết chuỗi s khi mẫu p kết thúc
      } else {
         bool first_match = (i < s.length() && (p[j] == s[i] || p[j] == '.'));

         if (j + 1 < p.length() && p[j + 1] == '*') {
            // Xử lý ký tự kế tiếp là '*': thử bỏ qua cụm "ký tự + *" hoặc khớp ký tự hiện tại
            result = (solve(i, j + 2, s, p) ||
                     (first_match && solve(i + 1, j, s, p)));
         } else {
            // So khớp ký tự thông thường và tiến lên ở cả s và p
            result = first_match && solve(i + 1, j + 1, s, p);
         }
      }

      return memo[i][j] = result;
   }

public:
   bool isMatch(string s, string p) {
      // Khởi tạo bộ nhớ đệm với giá trị mặc định -1
      for (int i = 0; i <= s.length(); ++i) {
         for (int j = 0; j <= p.length(); ++j) {
            memo[i][j] = -1;
         }
      }

      return solve(0, 0, s, p);
   }
};

int main() {

   string s;
   if (!(getline(cin, s))) return 0;

   string p;
   if (!(getline(cin, p))) return 0;

   Solution sol;
   cout << sol.isMatch(s, p);

   return 0;
}
