/*
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int largestRectangleArea(vector<int>& A) {
        int n = A.size();
        stack<int> st;

        int area = 0;
        int i = 0;
        for (; i < n; i++) {
            if (st.empty() || A[st.top()] <= A[i])
                st.push(i);
            else {
                while (!st.empty() && A[st.top()] > A[i]) {
                    int currentHeight = A[st.top()];
                    st.pop();
                    int width = st.empty() ? i : (i - st.top() - 1);
                    area = max(area, currentHeight * width);
                }
                st.push(i);
            }
        }

        while (!st.empty()) {
            int currentHeight = A[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            area = max(area, currentHeight * width);
        }

        return area;
    }
};

int main() {
    return 0;
}
