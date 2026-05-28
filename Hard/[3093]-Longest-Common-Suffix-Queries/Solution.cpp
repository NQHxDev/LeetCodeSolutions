#include "../../Utils/utils.h"

using namespace std;

struct TrieNode {
   TrieNode* children[26];
   int best_index;

   TrieNode() {
      for (int i = 0; i < 26; ++i) {
         children[i] = nullptr;
      }
      best_index = -1;
   }

   ~TrieNode() {
      for (int i = 0; i < 26; ++i) {
         if (children[i]) {
            delete children[i];
         }
      }
   }
};

class Solution {
private:
   TrieNode* root;

   // Chèn một từ vào Trie theo thứ tự đảo ngược
   void insert(const string& word, int idx, const vector<string>& wordsContainer) {
      TrieNode* curr = root;
      int len = word.length();
      
      // Duyệt từ cuối lên đầu của từ
      for (int i = len - 1; i >= 0; --i) {
         int char_idx = word[i] - 'a';
         if (!curr->children[char_idx]) {
            curr->children[char_idx] = new TrieNode();
         }
         curr = curr->children[char_idx];
         
         // Cập nhật chỉ số tốt nhất tại nút hiện tại
         if (curr->best_index == -1) {
            curr->best_index = idx;
         } else {
            int curr_best = curr->best_index;
            if (word.length() < wordsContainer[curr_best].length()) {
               curr->best_index = idx;
            }
         }
      }
   }

   // Tìm kiếm hậu tố chung dài nhất và trả về chỉ số tốt nhất
   int query(const string& word) {
      TrieNode* curr = root;
      int len = word.length();
      
      // Duyệt từ cuối lên đầu của từ truy vấn
      for (int i = len - 1; i >= 0; --i) {
         int char_idx = word[i] - 'a';
         if (!curr->children[char_idx]) {
            break;
         }
         curr = curr->children[char_idx];
      }
      return curr->best_index;
   }

public:
   vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
      root = new TrieNode();
      int n = wordsContainer.size();
      
      // Tìm từ có độ dài ngắn nhất và xuất hiện sớm nhất để làm mặc định tại root
      int default_best = 0;
      for (int i = 1; i < n; ++i) {
         if (wordsContainer[i].length() < wordsContainer[default_best].length()) {
            default_best = i;
         }
      }
      root->best_index = default_best;

      // Xây dựng cây tiền tố Trie từ các từ trong wordsContainer
      for (int i = 0; i < n; ++i) {
         insert(wordsContainer[i], i, wordsContainer);
      }

      vector<int> result;
      result.reserve(wordsQuery.size());
      
      // Thực hiện tìm kiếm cho từng truy vấn
      for (const string& q : wordsQuery) {
         result.push_back(query(q));
      }

      delete root;
      return result;
   }
};

int main() {

   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n, m;
   if (!(cin >> n >> m)) return 0;

   vector<string> wordsContainer = Utils::readVector<string>(n);
   vector<string> wordsQuery = Utils::readVector<string>(m);

   Solution sol;
   vector<int> result = sol.stringIndices(wordsContainer, wordsQuery);

   Utils::printVector(result);

   return 0;
}
