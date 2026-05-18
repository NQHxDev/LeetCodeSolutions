#include "../../Utils/utils.h"

using namespace std;

class Solution {
public:
   int minJumps(vector<int>& arr) {
      int n = arr.size();
      if (n <= 1) return 0;

      unordered_map<int, vector<int>> valueToIndices;
      for (int i = 0; i < n; ++i) {
         valueToIndices[arr[i]].push_back(i);
      }

      vector<bool> visited(n, false);
      queue<int> q;

      q.push(0);
      visited[0] = true;
      int steps = 0;

      while (!q.empty()) {
         int levelSize = q.size();
         for (int i = 0; i < levelSize; ++i) {
            int curr = q.front();
            q.pop();

            if (curr == n - 1) return steps;

            if (curr - 1 >= 0 && !visited[curr - 1]) {
               visited[curr - 1] = true;
               q.push(curr - 1);
            }

            if (curr + 1 < n && !visited[curr + 1]) {
               visited[curr + 1] = true;
               q.push(curr + 1);
            }
            if (valueToIndices.count(arr[curr])) {
               for (int nextIdx : valueToIndices[arr[curr]]) {
                  if (!visited[nextIdx]) {
                     visited[nextIdx] = true;
                     q.push(nextIdx);
                  }
               }
               valueToIndices.erase(arr[curr]);
            }
         }
         steps++;
      }

      return -1;
   }
};

int main() {

   int n;
   if (!(cin >> n)) return 0;

   vector<int> arr = Utils::readVector<int>(n);

   Solution sol;
   cout << sol.minJumps(arr);

   return 0;
}
