/*
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        int pa = -1, pb = -1, pc = -1;
        int res = 0;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'a')
                pa = j;
            else if (s[j] == 'b')
                pb = j;
            else if (s[j] == 'c')
                pc = j;
            if (pa == -1 || pb == -1 || pc == -1) continue;
            res += 1 + min({pa, pb, pc});
        }

        return res;
    }
};

int main() {
    return 0;
}
