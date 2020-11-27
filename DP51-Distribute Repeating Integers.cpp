/*
You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:

The ith customer gets exactly quantity[i] integers,
The integers the ith customer gets are all equal, and
Every customer is satisfied.
Return true if it is possible to distribute nums according to the above conditions.

 

Example 1:

Input: nums = [1,2,3,4], quantity = [2]
Output: false
Explanation: The 0th customer cannot be given two different integers.
Example 2:

Input: nums = [1,2,3,3], quantity = [2]
Output: true
Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
Example 3:

Input: nums = [1,1,2,2], quantity = [2,2]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].
Example 4:

Input: nums = [1,1,2,3], quantity = [2,2]
Output: false
Explanation: Although the 0th customer could be given [1,1], the 1st customer cannot be satisfied.
Example 5:

Input: nums = [1,1,1,1,1], quantity = [2,3]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [1,1,1].
 

Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= 1000
m == quantity.length
1 <= m <= 10
1 <= quantity[i] <= 105
There are at most 50 unique values in nums.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> freqMap;
        for (int num : nums)
            freqMap[num]++;

        vector<int> freq;
        for (auto it : freqMap)
            freq.push_back(it.second);

        int elems = freq.size();
        int people = quantity.size();

        vector<vector<int> > dp(elems, vector<int>(1 << people, -1));

        function<int(int, int)> go = [&](int idx, int peopleMask) {
            if (peopleMask == (1 << people) - 1)  //all people have satisfied
                return 1;

            if (idx == elems)  //we have reached end but people have not yet been satisfied
                return 0;

            int& ans = dp[idx][peopleMask];

            if (ans != -1) return ans;

            ans = go(idx + 1, peopleMask);  //don't use this freq[idx]

            for (int i = 0; i < (1 << people); i++) {  //iterate all subset of people

                if (peopleMask != (peopleMask & i))  //We will satisfy only the people who are not yet satisfied
                    continue;
                int sum = 0;
                int nextMask = peopleMask;

                for (int j = 0; j < people; j++) {        //Try to satisfy a[i] people with freq[idx] if not already satisfied
                    if (peopleMask & (1 << j)) continue;  //already satisfied

                    if (i & (1 << j)) {  //trying to satisfy not satisfied person
                        sum += quantity[j];
                        nextMask |= (1 << j);  //satisfied for next mask;
                    }
                }

                if (sum <= freq[idx])
                    ans |= go(idx + 1, nextMask);
            }

            return ans;
        };

        return go(0, 0);
    }
};

int main() {
    return 0;
}
