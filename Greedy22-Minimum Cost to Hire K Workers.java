/*
 * There are N workers. The i-th worker has a quality[i] and a minimum wage
 * expectation wage[i].
 * 
 * Now we want to hire exactly K workers to form a paid group. When hiring a
 * group of K workers, we must pay them according to the following rules:
 * 
 * Every worker in the paid group should be paid in the ratio of their quality
 * compared to other workers in the paid group. Every worker in the paid group
 * must be paid at least their minimum wage expectation. Return the least amount
 * of money needed to form a paid group satisfying the above conditions.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: quality = [10,20,5], wage = [70,50,30], K = 2 Output: 105.00000
 * Explanation: We pay 70 to 0-th worker and 35 to 2-th worker. Example 2:
 * 
 * Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3 Output: 30.66667
 * Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers
 * seperately.
 * 
 * 
 * Note:
 * 
 * 1 <= K <= N <= 10000, where N = quality.length = wage.length 1 <= quality[i]
 * <= 10000 1 <= wage[i] <= 10000 Answers within 10^-5 of the correct answer
 * will be considered correct.
 */

import java.util.*;

class Solution {
    public double mincostToHireWorkers(int[] quality, int[] wage, int K) {
        int n = quality.length;

        double[][] workers = new double[n][2];
        for (int i = 0; i < n; i++)
            workers[i] = new double[] { (double) (wage[i]) / quality[i], (double) quality[i] };

        Arrays.sort(workers, (a, b) -> Double.compare(a[0], b[0]));

        PriorityQueue<Double> pq = new PriorityQueue<>(Collections.reverseOrder());

        double res = Double.MAX_VALUE;
        double qualitySum = 0;
        for (double[] worker : workers) {
            qualitySum += worker[1];
            pq.add(worker[1]);
            if (pq.size() > K)
                qualitySum -= pq.poll();
            if (pq.size() == K)
                res = Math.min(res, qualitySum * worker[0]);
        }

        return res;
    }
}

class Driver {
    public static void main(String[] args) {
        Solution sol = new Solution();

        int[] quality = new int[] { 10, 20, 5 };
        int[] workers = new int[] { 70, 50, 30 };
        int K = 2;

        System.out.println(sol.mincostToHireWorkers(quality, workers, K));
    }
}