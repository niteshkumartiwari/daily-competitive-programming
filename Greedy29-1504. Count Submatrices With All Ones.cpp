#include <bits/stdc++.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 100
#define ll long long
const int MOD = 1e9 + 7;
const int MAXBIT = 30;

void printArr(string str, vector<int> arr) {
    cout << str << endl;
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

/*----START CODING FROM HERE-------*/

class Solution {
   public:
    int numSubmat(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        vector<int> sumRowWise(m, 0);

        function<int(void)> getAllMatrixEndingAtJ = [&]() {
            stack<int> st;
            int n = sumRowWise.size();
            vector<int> sum(n, 0);

            for (int i = 0; i < n; i++) {
                while (!st.empty() && sumRowWise[st.top()] >= sumRowWise[i])  //already computed
                    st.pop();

                if (!st.empty()) {
                    /*
                        there is some bar(j) less than curr(i)
                        1 2 3(j) _ _ _ _ 4(i)
                        we have to consider all the matrix made ending at j.
                        we are not considering those matrices because its height is less than curr i
                    */
                    sum[i] = sum[st.top()];                    //with prev height
                    sum[i] += sumRowWise[i] * (i - st.top());  //with current height
                } else {
                    sum[i] = sumRowWise[i] * (i + 1);  //starts from zero
                }

                st.push(i);
            }

            return accumulate(sum.begin(), sum.end(), 0);
        };

        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (A[i][j] == 1)
                    sumRowWise[j] += A[i][j];
                else
                    sumRowWise[j] = 0;
            }

            res += getAllMatrixEndingAtJ();
        }

        return res;
    }
};

int main() {
    Solution sol = Solution();
    vector<vector<int>> A {
        {0, 1, 1, 1}, {1, 1, 0, 1}, {1, 1, 0, 0}, {1, 1, 1, 1}, { 0, 1, 0, 0 }
    }
    cout << sol.numSubmat(A);

    return 0;
}