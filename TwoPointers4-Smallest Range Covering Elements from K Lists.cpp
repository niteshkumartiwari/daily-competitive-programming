/*
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

 

Example 1:

Input: [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
 

Note:

The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;
typedef tuple<int,int,int> ti;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n=nums.size();
        priority_queue<ti,vector<ti>,greater<ti>> pq;
        int maxVal=INT_MIN,range=INT_MAX;
        for(int i=0;i<n;i++){
            pq.emplace(nums[i][0],i,0);
            maxVal=max(maxVal,nums[i][0]);
        }

        int start=-1,end=-1;
        while(pq.size()==n){
            auto [val,row,idx]=pq.top();pq.pop();
            if(maxVal-val < range){
                range=maxVal-val;
                start=val;
                end=maxVal;
            }
            if(idx + 1 < nums[row].size()){
                pq.emplace(nums[row][idx+1],row,idx+1);
                maxVal=max(maxVal,nums[row][idx+1]);
            }
        }

        return {start,end};
    }
};


int main(){


    return 0;
}

/*
Image you are merging k sorted array using a heap. Then everytime you pop the smallest element 
out and add the next element of that array to the heap. By keep doing this, you will have the smallest range.
*/