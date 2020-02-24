/*
Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.

 

Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.
Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
 

Constraints:

1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp1(3,0),dp2(3,0);
        
        for(int i=0;i<n;i++){
            dp2=dp1;
            for(int j=0;j<3;j++){
                int sum=dp2[j]+nums[i];
                dp1[sum % 3]=max(dp1[sum % 3], sum);
            }
        }
        
        return dp1[0];
    }
};

int main(){
    Solution sol= Solution();
    vector<int> A{3,6,5,1,8};

    cout<<sol.maxSumDivThree(A);

    return 0;
}