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