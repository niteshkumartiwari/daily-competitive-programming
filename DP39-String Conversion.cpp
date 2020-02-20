/*
You are given a string S in the input. Assume that you have another string R of size same as S and all the characters of R are '.' . 
You need to tell the minimum number of operations to convert the string R to string S. An operation is defined as following: 
1) Take two indexes in the string R. 
2) Replace all the characters between these two indices(inclusive) with a new character of your choice 
(all the indexes must be filled with same character)
Note:
Input string (String S) contains only the lowercase English alphabets.
Constraints: 1 <= Size of input string <= 700 Example:
Input : "aabbca"
Output: 3

Explanation:
Initial string: "......"
First we fill whole string with 'a'.  ---> "aaaaaa"
Then from index 2 to index 3 we fill with 'b'.  ---> "aabbaa"
Then at index 4 we fill with 'c' ---> "aabbca"
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

int solve(string A) {
    int n=A.length();
    vector<vector<int>> dp(n,vector<int>(n,INT_MAX));
    //dp[i][j]:= min. no. of operations needed to convert S[i..j] to R[i...j]

    for(int i=0;i<n;i++)
        dp[i][i]=1;
    
    for(int i=0;i<n-1;i++)
        if(A[i]==A[i+1]) dp[i][i+1]=1;
        else dp[i][i+1]=2;
    
    for(int len=3;len<=n;len++){
        for(int i=0;i<n-len+1;i++){
            int j=i+len-1;

            if(A[i]==A[j])
                dp[i][j]=min({1+dp[i+1][j-1],dp[i+1][j],dp[i][j-1]});
            
            for(int k=i;k<j;k++)
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
        }
    }

    return dp[0][n-1];
}


int main(){
    string A="aabbca";

    cout<<solve(A);

    return 0;
}