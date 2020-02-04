/*
Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.

Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0 
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.
Note:
2 <= len(nums) <= 10000.
0 <= nums[i] < 1000000.
1 <= k <= len(nums) * (len(nums) - 1) / 2.
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;


//Approach 1 :=O(nlogn)
class Solution {
    // Returns number of pairs with absolute difference less than or equal to mid.
    int countPairs(vector<int> &nums,int mid){//O(n)
        int n=nums.size();
        int count=0,j=0;
        for(int i=0;i<n;i++){
            while(j<n && nums[j]-nums[i] <= mid) j++;
            count+=j-i-1;
        }
        return count;
    }
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int l=0,r=nums[n-1]-nums[0];

        while(l<r){//binary search on distance space logn
            int mid=l+(r-l)/2;
            int count= countPairs(nums,mid);

            if(count<k)
                l=mid+1;
            else
                r=mid;

        }
        return l;
    }
};

int main(){


    return 0;
}