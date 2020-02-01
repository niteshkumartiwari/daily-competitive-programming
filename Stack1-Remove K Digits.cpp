/*
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    string removeKdigits(string num, int k) {
        int n = num.length();
        stack<char> st;
        int i = 0;

        if (k >= n) return "0";

        for (int i = 0; i < n; i++) {
            while (k && !st.empty() && st.top() > num[i]) {  //remove larger elem before num
                st.pop();
                k--;
            }
            st.push(num[i]);
        }

        while (k > 0) {
            st.pop();
            k--;
        }

        string ans;
        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        while (ans.size() > 1 && ans.back() == '0')
            ans.pop_back();

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    return 0;
}
