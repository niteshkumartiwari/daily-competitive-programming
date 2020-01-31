/*
Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.
Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
Note:
The string size will be in the range [1, 100].
*/

#include <bits/stdc++.h>
using namespace std;

//Approach1 : Two-Pass
/*
The first loop check sto see if we have enough '(' and '*' characters to balance out the ')' character. If balance >= 0. 
Then we have more than enough.
The second loop checks to see if we have enough ')' and '*' to balance out the '(' character
The first and second loop logic combine together and say we have enough '(', ')', '*', character so balance out both the 
'(' and ')' parens.
*/
class Solution {
   public:
    bool checkValidString(string s) {
        int bal = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '*')
                bal++;
            else if (bal-- == 0)
                return false;
        }
        if (bal == 0) return true;
        bal = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == ')' || s[i] == '*')
                bal++;
            else if (bal-- == 0)
                return false;
        }

        return true;
    }
};

//Approach 2: One-Pass
/*
Let diff be count of left parenthesis minus count of right parenthesis.

When we meet:

(, we increment diff.
), we decrement diff.
*, we have three choices which makes the diff become a range -- [diff - 1, diff + 1].
So we use maxDiff/minDiff to record the maximum/minimum diff we can get.

When we meet:

(, ++maxDiff and ++minDiff.
), --maxDiff and --minDiff.
*, ++maxDiff and --minDiff.
If maxDiff become negative, it means it's already invalid, we should return false.

Whenever minDiff falls below 0, we should force it to be 0 because we never accept negative diff during the process.

After scanning through string s, as long as minDiff is 0, this string can be a valid one.
*/

class Solution {
   public:
    bool checkValidString(string s) {
        int maxDiff = 0, minDiff = 0;
        for (char c : s) {
            maxDiff += (c == '(' || c == '*') ? 1 : -1;
            minDiff += (c == ')' || c == '*') ? -1 : 1;
            if (maxDiff < 0) return false;
            minDiff = max(0, minDiff);
        }
        return minDiff == 0;
    }
};

int main() {
    return 0;
}