/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3 
Explanation: transactions = [buy, sell, cooldown, buy, sell]
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

//Approach 1 : Brute-force DP space O(N) time O(n^2)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(n==0 || n==1) return 0;
        vector<vector<int>> dp(n+1,vector<int>(2,0));
        /*
            dp[i][0]:= max profit if sell stock at i
            dp[i][1]:= max profit if cooldown at i no buy/sell
        */
       for(int i=1;i<n;i++){
           for(int j=0;j<i;j++){
               int val=prices[i]-prices[j]+ ((j-1<0)?0:dp[j-1][1]);
               dp[i][0]=max(dp[i][0],val);
           }
           dp[i][1]=max(dp[i-1][0],dp[i-1][1]);
       }

       return max(dp[n-1][0],dp[n-1][1]);
    }
};

//Approach 2 : Optimized on time (read Below for details)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(n==0 || n==1) return 0;

        vector<int> buy(n+1,0),sell(n+1,0);
        /*
            buy[i] := max profit if the first "i" days end with a "buy" day
            sell[i]:= max profit if the first "i" days end with a "sell" day
        */
        buy[1]=-prices[0];

        for(int i=2;i<=n;i++){
            buy[i]=max(buy[i-1],sell[i-2]-prices[i-1]);
            sell[i]=max(sell[i-1],buy[i-1]+prices[i-1]);
        }

        return sell[n];
    }
};

int main(){
    Solution sol= Solution();
    vector<int> prices={1,2,3,0,2};

    sol.maxProfit(prices);

    return 0;
}

/*
On any i-th day, we can buy, sell or cooldown

buy[i]: The maximum profit can be made if the first i days end with buy or wait. E.g "buy, sell, buy" or "buy, cooldown, cooldown"
sell[i]: The maximum profit can be made if the first i days end with sell or wait. E.g "buy, sell, buy, sell" or "buy, sell, cooldown, cooldown"
price: prices[i - 1], which is the stock price of the i-th day

To calculate sell[i]:
If we sell on the i-th day, the maximum profit is buy[i - 1] + price, because we have to buy before we can sell.
If we cooldown on the i-th day, the maximum profit is same as sell[i - 1] since we did not do anything on the i-th day.
So sell[i] is the larger one of (buy[i - 1] + price, sell[i - 1])

To calculate buy[i]:
If we buy on the i-th day, the maximum profit is sell[i - 2] - price, because on the (i-1)th day we can only cooldown.
If we cooldown on the i-th day, the maximum profit is same as buy[i - 1] since we did not do anything on the i-th day.
So sell[i] is the larger one of (sell[i - 2] - price, buy[i - 1])
*/