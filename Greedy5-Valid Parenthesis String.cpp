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

#include<bits/stdc++.h>
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
        int bal=0;
        for(int i=0;i<s.length();i++){
            if(s[i]=='(' || s[i]=='*')bal++;
            else if(bal--==0) return false;
        }
        if(bal==0)return true;
        bal=0;
        for(int i=s.length()-1;i>=0;i--){
            if(s[i]==')' || s[i]=='*')bal++;
            else if(bal--==0) return false;
        }

        return true;
    }
};

//Approach 2: One-Pass
/*
low : take '*' as ')', if there are some '(' not matched
high : take '*' as '('

if high < 0 means too much ')'
if low > 0 , after the count finished, means too much '('

since low take '*' as ')', there might be too much ')', so that low might less than 0. That's why low-- should happen only low>0. This can thought as, low only take as much as '(''s ')' and ignore other ')' s. This will not cause problem since :

'*' can be treated as empty
high has deal with the situation that too much ')' exist
*/

class Solution {
public:
    bool checkValidString(string s) {
        int low=0,high=0;

        for(int i=0;i<s.length();i++){
            if(s[i]=='('){
                low++;
                high++;
            }
            else if(s[i]==')'){
                if(low>0)low--;
                high--;
            }
            else{
                if(low>0)low--;
                high++;
            }
            if(high<0)
                return false;
        }

        return low==0;
    }
};

int main(){


    return 0;
}