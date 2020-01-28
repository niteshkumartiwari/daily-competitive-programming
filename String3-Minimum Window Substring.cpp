/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
    void shrink(string &s,int &i,int &j,int cntS[],int cntT[]){
        int n=s.length();

        while(cntS[s[i]] > cntT[s[i]] && i<j){
            cntS[s[i]]--;
            i++;
        }
    }
public:
    string minWindow(string s, string t) {
        int n=s.length(),m=t.length();
        int cntT[256]={0},cntS[256]={0};

        for(int i=0;i<m;i++)
            cntT[t[i]]++;

        int count=0,i=0,j=0;
        int startIdx=0,maxLength=n+1;
        bool flag=false;

        while(j<n){
            cntS[s[j]]++;
            if(cntS[s[j]] <= cntT[s[j]])
                count++;
            if(count==m){//got all characters
                shrink(s,i,j,cntS,cntT);
                if(maxLength > j-i+1){
                    maxLength=j-i+1;
                    startIdx=i;
                    flag=true;
                }
            }
            j++;
        }
        
        return flag?s.substr(startIdx,maxLength):"";
    }
};

int main(){
    Solution sol= Solution();

    cout<<sol.minWindow("a","aa");

    return 0;
}