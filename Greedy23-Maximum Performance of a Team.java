import java.util.*;

class Solution {
    public int maxPerformance(int n, int[] speed, int[] efficiency, int k) {
        int[][] combo = new int[n][2];
        long res = 0, speedSum = 0;

        for (int i = 0; i < n; i++)
            combo[i] = new int[] { efficiency[i], speed[i] };

        Arrays.sort(combo, (a, b) -> b[0] - a[0]);

        PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> a - b);

        for (int[] comb : combo) {
            pq.add(comb[1]);
            speedSum += comb[1];

            if (pq.size() > k)
                speedSum -= pq.poll();
            res = Math.max(res, comb[0] * speedSum);
        }

        return (int) (res % (long) (1e9 + 7));
    }
}

class Driver {
    public static void main(String[] args) {
        Solution sol = new Solution();

        int[] quality = new int[] { 2, 10, 3, 1, 5, 8 };
        int[] workers = new int[] { 5, 4, 3, 9, 7, 2 };
        int K = 2;
        int n = 6;

        System.out.println(sol.maxPerformance(n, quality, workers, K));
    }
}