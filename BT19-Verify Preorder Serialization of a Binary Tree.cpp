/*
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: "1,#"
Output: false
Example 3:

Input: "9,#,#,1"
Output: false
*/
#include <bits/stdc++.h>

#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll long long
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 20005
const int MOD = 1e9 + 7;

/*----START CODING FROM HERE-------*/

class Solution {
    vector<string> getString(string pre) {
        int n = pre.length();
        string curr = "";
        vector<string> res;

        for (int i = 0; i < n; i++) {
            if (pre[i] == ',') {
                res.push_back(curr);
                curr = "";
            } else
                curr += pre[i];
        }

        if (curr != "") res.push_back(curr);

        return res;
    }

   public:
    bool isValidSerialization(string preorder) {
        vector<string> str = getString(preorder);

        int cnt = 1;
        for (string s : str) {
            cnt--;
            if (cnt < 0) return false;
            if (s != "#") cnt += 2;
        }

        return cnt == 0;
    }
};

int main() {
    Solution sol = Solution();

    string s = "#,7,6,9,#,#,#";
    cout << sol.isValidSerialization(s);

    return 0;
}
