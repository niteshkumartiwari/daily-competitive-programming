/*
Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int monotoneIncreasingDigits(int N) {
        string str = to_string(N);
        int monoIncToTheLeft = N - 1;
        for (int i = str.length() - 1; i > 0; i--) {
            if (str[i - 1] > str[i]) {
                monoIncToTheLeft = i - 1;
                str[i - 1]--;
            }
        }

        for (int i = monoIncToTheLeft + 1; i < str.length(); i++)
            str[i] = '9';

        return stoi(str);
    }
};

int main() {
    return 0;
}
