#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int numberOfSpecialChars(string word) {
      vector<bool> has_lower(26, false);
      vector<bool> has_upper(26, false);

      for (char ch : word) {
         if (ch >= 'a' && ch <= 'z') {
            has_lower[ch - 'a'] = true;
         } else if (ch >= 'A' && ch <= 'Z') {
            has_upper[ch - 'A'] = true;
         }
      }

      int count = 0;
      for (int i = 0; i < 26; ++i) {
         if (has_lower[i] && has_upper[i]) {
            count++;
         }
      }

      return count;
   }
};

int main() {
   // Tối ưu hóa tốc độ nhập xuất của luồng dữ liệu
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   string word;
   if (!(getline(cin, word))) {
      return 0;
   }

   Solution sol;
   cout << sol.numberOfSpecialChars(word);

   return 0;
}
