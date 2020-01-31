/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
Note:

There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?
*/

#include<bits/stdc++.h>
using namespace std;    

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {//O(nlogn)
        int n=nums.size();
        vector<int> lis;

        for(int i=0;i<n;i++){
            if(lis.size()==0)
                lis.push_back(nums[i]);
            else{
                auto index= lower_bound(lis.begin(),lis.end(),nums[i]);

                if(index==lis.end())lis.push_back(nums[i]);
                else if(*index > nums[i]) *index=nums[i];
            }
        }

        return lis.size();
    }
};

int main(){
    Solution sol= Solution();
    vector<int> A{10,9,2,5,3,7,101,18};

    cout<<sol.lengthOfLIS(A);

    return 0;
}