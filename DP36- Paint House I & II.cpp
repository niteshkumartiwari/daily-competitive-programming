/* Paint House - I
There are a row of  n  houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a   cost matrix. For example,   is the cost of painting house 0 with color red;   is the cost of painting house 1 with color green, and so on ... Find the minimum cost to paint all houses.n x 3costs[0][0]costs[1][2]

Note:
All costs are positive integers.
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

class Solution {
 public :
     int minCost (vector <vector < int >> & costs) {
         if (costs.empty () || costs [ 0 ] .empty ()) return  0 ;
        vector <vector < int >> dp = costs;
         for ( int i = 1 ; i <dp.size (); ++ i) {
            dp [i] [ 0 ] += min (dp [i- 1 ] [ 1 ], dp [i- 1 ] [ 2 ]);
            dp [i] [ 1 ] += min (dp [i- 1 ] [ 0 ], dp [i- 1 ] [ 2 ]);
            dp [i] [ 2 ] += min (dp [i- 1 ] [ 0 ], dp [i- 1 ] [ 1 ]);
        }
        return min (min (dp.back () [ 0 ], dp.back () [ 1 ]), dp.back () [ 2 ]);
    }
};

/*
Paint House - II
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.
Note:
All costs are positive integers.
Follow up:
Could you solve it in O(nk) runtime?
*/


//Approach-1 - Time O(n*k^2) Space O(n*k)
class Solution {
 public :
    int minCost (vector <vector < int >> & costs) {
        if(costs.size()==0 || costs[0].size())
            return 0;
        int n=costs.size();
        int k=costs[0].size();

        vector<vector<int>> dp(n,vector<int>(k,0));//where dp[i][j] means for house i with color j the minimum cost. 

        for(int i=0;i<k;i++)
            dp[0][i]=costs[0][i];

        for(int i=0;i<n;i++){//O(n*k^2)
            for(int j=0;j<k;j++){
                dp[i][j]=INT_MAX;
                for(int m=0;m<k;m++){
                    if(m!=j)
                        dp[i][j]=min(dp[i][j],dp[i-1][m]+costs[i][j]);
                }
            }
        }
        
        return *min_element(dp[n-1].begin(),dp[n-1].end());
    }
};

//Approach-2 - Time O(n*k^2) Space O(k)
class Solution {
 public :
    int minCost (vector <vector < int >> & costs) {
        if(costs.size()==0 || costs[0].size())
            return 0;
        int n=costs.size();
        int k=costs[0].size();

        vector<int> dp1(k,0);
        vector<int> dp2(k,0);

        for(int i=0;i<k;i++)
            dp1[i]=costs[0][i];

        for(int i=1;i<n;i++){
            for(int j=0;j<k;j++){
                dp2[j]= INT_MAX;
                for(int m=0;m<k;m++){
                    if(m!=j)
                        dp2[j]=min(dp2[j],dp1[m]+costs[i][j]);
                }
            }

            dp1=dp2;
        }

        return *min_element(dp1.begin(),dp1.end());
    }
};

//Approach-2 - Time O(n*k) Space O(k)
/*
f we continue follow the old coding structure, we definitely would end up with the time complexity: O(nk^2).
level 1: n is the total number of houses we have to paint. 
level 2: the first k represent for each house we need to try k colors. 
level 3: the second k was caused by the process to search the minimum cost (if not use certain color).

Apparently, if we want reach the time complexity O(nk), we have to optimize our operation at level 3. 
If we choose the color[i][j], how could we reduce the comparision between (color[i-1][0] to color[i-1][k], except color[i-1][j])
And we know there are acutally extra comparisions, since fore each color, we have to find the smallest amongst other colors. 

There must be way to solve it, Right?
Yup!!! There is a magic skill for it!!!
Let us assume, we have "min_1" and "min_2". 
min_1 : the lowest cost at previous stage.
min_2 : the 2nd lowest cost at previous stage. 

And we have the minimum costs for all colors at previous stage.
color[i-1][k]

Then, iff we decide to paint house "i" with color "j", we can compute the minimum cost of other colors at "i-1" stage through following way.
case 1: iff "color[i-1][j] == min_1", it means the min_1 actually records the minimum value of color[i-1][j] (previous color is j), we have to use min_2;
case 2: iff "color[i-1][j] != min_1", it means min_1 is not the value of color[i-1][j] (previous color is not j), we can use the min_1's color.
Note: iff "pre_min_1 == pre_min_2", it means there are two minimum costs, anyway, no matter which color is pre_min_1, we can use pre_min_2.
----------------------------------------------------------
if (dp[j] != pre_min_1 || pre_min_1 == pre_min_2) {
    dp[j] = pre_min_1 + costs[i][j];
} else{
    dp[j] = pre_min_2 + costs[i][j];
}
----------------------------------------------------------
The way to maintain "min_1" and "min_2".
for (int i = 0; i < len; i++) {
    ...
    min_1 = Integer.MAX_VALUE;
    min_2 = Integer.MAX_VALUE;
    ...
    if (dp[j] <= min_1) {
        min_2 = min_1;
        min_1 = dp[j];
    } else if (dp[j] < min_2){
        min_2 = dp[j];
    }
}
*/

class Solution {
 public :
    int minCost (vector <vector < int >> & costs) {
        if(costs.size()==0 || costs[0].size())
            return 0;
        int n=costs.size();
        int k=costs[0].size();

        vector<int> dp(k,0);
        int min1=0,min2=0;

        for(int i=0;i<n;i++){
            int oldMin1=min1;
            int oldMin2=min2;

            min1=min2=INT_MAX;

            for(int j=0;j<k;j++){
                if(dp[j]!=oldMin1 || oldMin1==oldMin2)
                    dp[j]=oldMin1+costs[i][j];
                else
                    dp[j]=oldMin2+costs[i][j];

                if(min1<=dp[j])
                    min2=min(min2,dp[j]);
                else{
                    min2=min1;
                    min1=dp[j];
                }
            }
        }

        return min1;
    }
};




int main(){

    return 0;
}