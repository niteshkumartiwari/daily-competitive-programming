/*
You are given an even number of people num_people that stand around a circle and each person shakes hands with someone else, so that there are num_people / 2 handshakes total.
Return the number of ways these handshakes could occur such that none of the handshakes cross.
Since this number could be very big, return the answer mod 10^9 + 7

Example 1:
Input: num_people = 2
Output: 1
Example 2:

Input: num_people = 4
Output: 2
Explanation: There are two ways to do it, the first way is [(1,2),(3,4)] and the second one is [(2,3),(4,1)].
Example 3:

Input: num_people = 6
Output: 5
Example 4:
Input: num_people = 8
Output: 14

Constraints:
2 <= num_people <= 1000
num_people % 2 == 0
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int dp[1009];
int numOfWays(int n) {
    int &ans = dp[n];
    if (ans != -1) return ans;
    if (n == 0) return ans = 1;      //no people
    if (n % 2 == 1) return ans = 0;  //odd people

    long sum = 0;
    for (int i = 0; i < n; i += 2) {
        sum += numOfWays(i) * numOfWays(n - i - 2);  //get the ans from two
        //divided halfs
    }

    return ans = sum;
}

int main() {
    memset(dp, -1, sizeof dp);
    cout << numOfWays(8);
    return 0;
}
