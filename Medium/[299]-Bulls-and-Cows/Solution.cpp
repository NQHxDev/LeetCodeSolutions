#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   string getHint(string secret, string guess) {
      int bulls = 0;
      int cows = 0;
      vector<int> secret_counts(10, 0);
      vector<int> guess_counts(10, 0);

      int n = secret.length();
      // Duyệt qua chuỗi để đếm số Bulls và các chữ số chưa khớp ở từng vị trí
      for (int i = 0; i < n; ++i) {
         if (secret[i] == guess[i]) {
            bulls++;
         } else {
            secret_counts[secret[i] - '0']++;
            guess_counts[guess[i] - '0']++;
         }
      }

      // Cộng dồn số Cows bằng cách so khớp các số dư thừa trong hai giỏ đếm
      for (int d = 0; d < 10; ++d) {
         cows += min(secret_counts[d], guess_counts[d]);
      }

      return to_string(bulls) + "A" + to_string(cows) + "B";
   }
};

int main() {
   // Tối ưu hóa tốc độ của luồng nhập xuất
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   string secret, guess;
   if (!(getline(cin, secret))) {
      return 0;
   }
   if (!(getline(cin, guess))) {
      return 0;
   }

   Solution sol;
   cout << sol.getHint(secret, guess);

   return 0;
}
