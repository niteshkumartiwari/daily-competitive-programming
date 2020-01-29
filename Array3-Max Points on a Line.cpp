/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/

#include<bits/stdc++.h>
using namespace std;    

class Solution {
public:
    int gcd(int a,int b){
        if(b==0)
            return a;
        return gcd(b,a%b);
    }

    int maxPoints(vector<vector<int>>& points) {
        int n=points.size();
        int ans=0;
        map<pair<int,int>,int> m;//slope count for each point
        int res=0;

        for(int i=0;i<n;i++){
            int ans=0, overlapping=0,vertical=0;
            for(int j=i+1;j<n;j++){
                int x0=points[j][0]-points[i][0],y0=points[j][1]-points[i][1];
                
                if(x0==0 && y0==0)
                    overlapping++; 
                else if(x0==0)
                    vertical++;
                else{
                    int cf=gcd(x0,y0);
                    
                    x0/=cf,y0/=cf;//Normalising

                    m[{x0,y0}]++;
                    
                    ans=max(ans,m[{x0,y0}]);
                }
                ans=max(ans,vertical);
            }

            res=max(res,ans+overlapping+1);
            m.clear();//clearing it for next point
        }

        return res;
    }
};

int main(){
   Solution sol= Solution();
   vector<vector<int>> points{
       {1,1},{2,2},{3,3}
   };

   cout<<sol.maxPoints(points);

    return 0;
}