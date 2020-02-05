/*
Given a string str, find the longest repeating non-overlapping substring in it. 
In other words find 2 identical substrings of maximum length which do not overlap. 
If there exists more than one such substring return any of them.

Examples:

Input : str = "geeksforgeeks"
Output : geeks

Input : str = "aab"
Output : a

Input : str = "aabaabaaba"
Output : aaba

Input : str = "aaaaaaaaaaa"
Output : aaaaa

Input : str = "banana"
Output : an 
         or na
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

//TIP
/*
Longest Dublicate Substring 
banana =>ana
is solved using binary search + robin karp
*/


string LRS(string str){//O(n^3)
    int n=str.length();
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    //dp[i][j]:= max repeating substring ending with i & j

    int maxLen=0,index=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(str[i-1]==str[j-1] && (j-i) > dp[i-1][j-1]){//for non overlapping, since substring of j start from j-dp[i-1][j-1] this may overlap with ending of substring i, i < j-dp[i-1][j-1]  
                dp[i][j]=dp[i-1][j-1]+1;

                if(dp[i][j]>maxLen){
                    maxLen=dp[i][j];
                    index=max(i,index);
                }
            }
            else
                dp[i][j]=0;
            
        }
    }

    string res;
    if(maxLen > 0)
        for(int i=index-maxLen+1;i<=maxLen;i++)
            res+=str[i-1];

    return res;
}

int main(){
    string A="geeksforgeeks";

    cout<<LRS(A);

    return 0;
}