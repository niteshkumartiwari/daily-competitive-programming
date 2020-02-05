/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) 
such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

class Solution {
public:
    int longestSubstring(string s, int k) {
        int n=s.length();
        vector<int> cnt;

        /*
            substring with 'ch' unique chars each with cnt >= k
        */
        int res=0;
        for(int ch=1;ch<=26;ch++){//No. of unique characters
            cnt.resize(26,0);
            cnt.clear();
            int unique=0;
            int charsGreatThanEqtoK=0;
            int i=0,j=0;

            while(j<n){
                if(unique<=ch){
                    int idx=s[j]-'a';
                    if(cnt[idx]==0)
                        unique++;
                    cnt[idx]++;
                    if(cnt[idx]==k)
                        charsGreatThanEqtoK++;
                    j++;
                }
                else{//unique > ch
                    int idx=s[i]-'a';//shift left, since count exceed
                    if(cnt[idx]==k)
                        charsGreatThanEqtoK--;
                    cnt[idx]--;
                    if(cnt[idx]==0)
                        unique--;
                    i++;
                }
                
                // if we found a string where the number of unique chars equals our target
                // and all those chars are repeated at least K times then update max
                if(unique==ch && unique==charsGreatThanEqtoK)
                    res=max(res,j-i);
            }
        }

        return res;
    }
};

int main(){


    return 0;
}