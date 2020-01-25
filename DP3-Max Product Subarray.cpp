/*
Max Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest product. Return an integer corresponding to the maximum product possible.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int maxProduct(vector<int> A) {
    int n = A.size();
    int maxVal = A[0], minVal = A[0], maxProd = A[0];

    for (int i = 1; i < n; i++) {
        if (A[i] < 0)
            swap(maxVal, minVal);
        maxVal = max(A[i], maxVal * A[i]);
        minVal = min(A[i], minVal * A[i]);
        maxProd = max(maxProd, maxVal);
    }
    return maxProd;
}

int main() {
    return 0;
}
