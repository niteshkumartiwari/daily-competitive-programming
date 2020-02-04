/*
Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

class Solution {
    int getLPS(string str){
        int n=str.length();
        vector<int> lps(n,0);

        int len=0,i=1;
        while(i<n){
            if(str[i]==str[len])
                lps[i++]=++len;
            else{
                if(len!=0)
                    len=lps[len-1];
                else
                    lps[i++]=0;
                
            }
        }

        return lps[n-1];
    }
public:
    string shortestPalindrome(string s) {
        int n=s.length();
        string temp= s, combo;
        reverse(temp.begin(),temp.end());
        combo=s+"$"+temp;

        //find largest palindrome substring starting from idx 0 
        int idx=getLPS(combo);
        temp=s.substr(idx);
        reverse(temp.begin(),temp.end());

        return temp+s;
    }
};

int main(){


    return 0;
}

/*
This problem asks us to add string before the input so the result string will be a palindrome.
We can convert it to an alternative problem"find the longest palindrome substring starts from index 0".
If we can get the length of such substring, then we can easily build a palindrome string by inserting the reverse part of substring after such substring before the original string.

Example:

input string:

abacd

longest palindrome substring starts from 0:

aba

Insert the reverse part of substring after palindrome substring before the head:

dcabacd

Now the problem becomes how to find the longest palindrome substring starts from 0.
We can solve it by using a trick + KMP.

The trick is to build a temp string like this:

s + "#" + reverse(s)

Then we run KMP on it, the value in last cell will be our solution. In this problem, we don't need to use KMP
to match strings but instead we use the lookup table in KMP to find the palindrome.

We add "#" here to force the match in reverse(s) starts from its first index
What we do in KMP here is trying to find a match between prefix in s and a postfix in reverse(s). The match part will be palindrome substring.

Example:
input:

catacb

Temp String:

catacb # bcatac

KMP table:

c a t a c b # b c a t a c

0 0 0 0 1 0 0 0 1 2 3 4 5

In the last cell, we got a value 5. It means in s we have a substring of length 5 that is palindrome.
*/