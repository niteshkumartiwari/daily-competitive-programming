/*
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 ≤ i ≤ j < n.

Follow up: Could you do this in O(n) runtime?

 

Example 1:

Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
Example 2:

Input: nums = [0]
Output: 0
Example 3:

Input: nums = [2,4]
Output: 6
Example 4:

Input: nums = [8,10,2]
Output: 10
Example 5:

Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127
 

Constraints:

1 <= nums.length <= 2 * 104
0 <= nums[i] <= 231 - 1
*/

import java.util.*;

class Solution {
    public int findMaximumXOR(int[] nums) {
        int n = nums.length;
        int mask = 0;
        int maxResult = 0;

        for (int j = 31; j >= 0; j--) {
            mask = mask | (1 << j);

            Set<Integer> set = new HashSet<>();
            for (int i = 0; i < nums.length; i++) {
                int leftPart = mask & nums[i];
                set.add(leftPart);
            }

            int greedyMax = maxResult | (1 << j);
            for (int leftPart : set) {
                int anotherNum = leftPart ^ greedyMax;
                if (set.contains(anotherNum)) {
                    maxResult = greedyMax;
                    break;
                }
            }
        }

        return maxResult;
    }
}

class Driver {
    public static void main(String[] args) {
        Solution sol = new Solution();

        int[] nums = new int[] { 3, 10, 5, 25, 2, 8 };

        System.out.println(sol.findMaximumXOR(nums));
    }
}