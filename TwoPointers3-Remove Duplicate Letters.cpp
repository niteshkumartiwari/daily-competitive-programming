/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
I think this solution is really concise! But I want to add some detailed explainations to show why we do so to solve the problem, This problem is in fact similiar to the problem "Largest Rectangle under the histogram "

We need to keep the monotically decreasing substring that contains all the char in the s. So we just use a vector to mimic the stack! Just similiar to the previous many solutions that use the vector to simulate a stack.

*/

class Solution {
   public:
    string removeDuplicateLetters(string s) {
        vector<int> cnt(256, 0);
        vector<bool> visited(256, false);

        for (int i = 0; i < s.length(); i++) cnt[s[i]]++;
        /** the key idea is to keep a monotically increasing sequence if that
         character occurs again in future than pop it out**/
        string result = "0";
        for (char ch : s) {
            cnt[ch]--;
            /** to filter the previously visited elements **/
            if (visited[ch]) continue;
            while (ch < result.back() && cnt[result.back()]) {
                visited[result.back()] = false;
                result.pop_back();
            }

            result += ch;
            visited[ch] = true;
        }

        return result.substr(1);
    }
};

int main() {
    return 0;
}
