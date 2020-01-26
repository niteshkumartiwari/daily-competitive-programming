/*
Given an array with non negative numbers, divide the array into two parts such that the average of both the parts is equal. Return both parts (If exist). If there is no solution. return an empty list. Example:
Input:
[1 7 15 29 11 9]

Output:
[9 15] [1 7 11 29]

The average of part is (15+9)/2 = 12,
average of second part elements is (1 + 7 + 11 + 29) / 4 = 12
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<bool> ans;
int dp[100][500][100];

bool isPossible(vector<int> &A, int elems, int currSum, int idx) {
    int n = A.size();
    int &memo = dp[elems][currSum][idx];

    if (memo != -1) return memo;
    if (elems == 0) return currSum == 0;
    if (idx >= n) return false;

    //le-lo
    if (currSum >= A[idx]) {
        ans[idx] = true;
        if (isPossible(A, elems - 1, currSum - A[idx], idx + 1)) return memo = 1;
        ans[idx] = false;
    }

    //na-lo
    if (isPossible(A, elems, currSum, idx + 1)) return memo = 1;

    return memo = 0;
}

vector<vector<int>> avgset(vector<int> &A) {
    int n = A.size();
    int totSum = 0;
    ans.clear();
    ans.resize(n, false);
    memset(dp, -1, sizeof dp);

    for (int val : A)
        totSum += val;

    sort(A.begin(), A.end());
    vector<vector<int>> res;

    for (int i = 1; i < n; i++) {
        if (totSum * i % n != 0) continue;
        ans.clear();
        if (isPossible(A, i, (totSum * i) / n, 0)) {
            vector<int> A1, B1;
            for (int i = 0; i < n; i++) {
                if (ans[i])
                    A1.push_back(A[i]);
                else
                    B1.push_back(A[i]);
            }

            if (A1.size() <= B1.size())
                res.push_back(A1), res.push_back(B1);
            else
                res.push_back(B1), res.push_back(A1);

            return res;
        }
    }

    return res;
}

int main() {
    return 0;
}
