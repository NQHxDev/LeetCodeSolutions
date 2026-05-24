#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   vector<int> findSubstring(string s, vector<string>& words) {
      vector<int> result;
      if (s.empty() || words.empty()) return result;

      int sLen = s.length();
      int numWords = words.size();
      int wordLen = words[0].length();
      int totalLen = numWords * wordLen;

      if (sLen < totalLen) return result;

      unordered_map<string, int> wordCount;
      for (const string& word : words) {
         wordCount[word]++;
      }

      for (int i = 0; i < wordLen; i++) {
         int left = i;
         int count = 0;
         unordered_map<string, int> currentCount;

         for (int right = i; right <= sLen - wordLen; right += wordLen) {
            string word = s.substr(right, wordLen);

            if (wordCount.count(word)) {
               currentCount[word]++;
               count++;

               while (currentCount[word] > wordCount[word]) {
                  string leftWord = s.substr(left, wordLen);
                  currentCount[leftWord]--;
                  count--;
                  left += wordLen;
               }

               if (count == numWords) {
                  result.push_back(left);
               }
            } else {
               currentCount.clear();
               count = 0;
               left = right + wordLen;
            }
         }
      }

      return result;
   }
};

int main() {
   string s;
   if (!(cin >> s)) return 0;

   int n;
   if (!(cin >> n)) return 0;

   vector<string> words(n);
   for (int i = 0; i < n; ++i) {
      cin >> words[i];
   }

   Solution sol;
   vector<int> result = sol.findSubstring(s, words);

   Utils::printVector(result);

   return 0;
}
