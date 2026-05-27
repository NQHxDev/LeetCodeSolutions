#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int numberOfSpecialChars(string word) {
      vector<int> last_lower(26, -1);
      vector<int> first_upper(26, -1);

      // Ghi nhận chỉ số cuối cùng của chữ thường và chỉ số đầu tiên của chữ hoa
      for (int i = 0; i < word.length(); ++i) {
         char ch = word[i];
         if (ch >= 'a' && ch <= 'z') {
            last_lower[ch - 'a'] = i;
         } else if (ch >= 'A' && ch <= 'Z') {
            if (first_upper[ch - 'A'] == -1) {
               first_upper[ch - 'A'] = i;
            }
         }
      }

      int count = 0;
      // Đếm số lượng chữ cái thỏa mãn tất cả chữ thường xuất hiện trước chữ hoa đầu tiên
      for (int i = 0; i < 26; ++i) {
         if (last_lower[i] != -1 && first_upper[i] != -1 && last_lower[i] < first_upper[i]) {
            count++;
         }
      }

      return count;
   }
};

int main() {
   // Tối ưu hóa tốc độ nhập xuất luồng dữ liệu
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   string word;
   if (!(getline(cin, word))) {
      return 0;
   }

   Solution sol;
   cout << sol.numberOfSpecialChars(word) << "\n";

   return 0;
}
