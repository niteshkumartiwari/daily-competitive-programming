/*
You are given a sorted array A of N integers, where N is odd. You can make the following operation with it: Choose one of the elements of the array (for example ai) and increase it by 1 (that is, replace it with ai + 1). Return the largest possible median of the array using at most B operations. Note: The median of the odd-sized sorted array is the middle element after the array is sorted in non-decreasing order. 
 Input Format:
The first argument of input contains an integer array A, of length N.
The second argument of input contains a string B, representing the number of options.

Note: Please convert B to an integer from its string representation.
Output Format:
Return the string representation of the required maximum median.
Constraints:
1 <= N <= 1e7
1 <= A[i] <= 1e9
1<= B <= 1e12
Examples:
Input 1:
    A = [1, 3, 5]
    B = "2"

Output 1:
    "5"

Explanation 1:
    As 2nd element can be increased 2 times to make it 5.

Input 2:
    A = [1, 1, 1, 1, 2]
    B = "3"

Output 2:
    "3"

Explanation 2:
    Increase 2nd element once and fourth and last element 2 times.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//Can be done using binary search Q*logk*logn
bool check(vector<int> &A, ll x, ll k) {
    ll moves = 0;
    int n = A.size();
    for (int i = n / 2; i < n; i++) {  //increasing all the right half elems < x to x
        if (x - A[i] > 0) moves += x - A[i];
        if (moves > k) return false;
    }

    if (moves <= k) return true;
    return false;
}

string solve(vector<int> &A, string B) {  //nlogk
    int n = A.size();
    ll k = stoll(B);

    ll l = A[n / 2], r = A[n / 2] + k;
    ll ans = l;

    while (l <= r) {
        ll mid = l + (r - l) / 2;

        if (check(A, mid, k))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }

    return to_string(ans);
}

int main() {
    vector<int> A{2, 2, 4, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 15, 15, 16, 17, 18, 20};
    string B = "3";
    cout << solve(A, B);

    return 0;
}