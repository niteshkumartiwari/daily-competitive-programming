/*
Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2
Example 3:

Input: A = "abac", B = "baca"
Output: 2
Example 4:

Input: A = "aabc", B = "abca"
Output: 2
Note:

1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
*/
#include <bits/stdc++.h>
#include <unordered_set>
#define ll long long
using namespace std;

class Solution {
   public:
    int kSimilarity(string A, string B) {
        if (A == B) return 0;
        queue<string> q;
        unordered_set<string> visited;
        q.push(A);
        visited.insert(A);

        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto s = q.front();
                q.pop();
                if (s == B) return steps;
                int i = 0;
                while (s[i] == B[i]) i++;
                for (int j = i + 1; j < s.length(); j++) {
                    if (s[j] == B[j] || s[j] != B[i]) continue;
                    swap(s[i], s[j]);

                    if (visited.count(s) == 0) {
                        q.push(s);
                        visited.insert(s);
                    }

                    swap(s[i], s[j]);  //back for next loop
                }
            }
            ++steps;
        }

        return steps;
    }
};

int main() {
    return 0;
}
