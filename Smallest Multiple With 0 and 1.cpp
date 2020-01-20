/*
You are given an integer N. You have to find smallest multiple of N which consists of digits 0 and 1 only. Since this multiple could be large, return it in form of a string. Note:
Returned string should not contain leading zeroes.
For example,
For N = 55, 110 is smallest multiple consisting of digits 0 and 1.
For N = 2, 10 is the answer.
*/
#include <bits/stdc++.h>
#include <unordered_set>
#define ll long long
using namespace std;

int getRem(string num, int N) {
    int rem = 0;
    for (int i = 0; i < num.length(); i++) {
        rem = rem * 10 + (num[i] - '0');
        rem %= N;
    }

    return rem;
}

string multiple(int N) {
    queue<string> q;
    unordered_set<int> remSet;

    q.push("1");

    while (1) {
        string num = q.front();
        q.pop();
        int rem = getRem(num, N);

        if (rem == 0) return num;

        if (remSet.count(rem) == 0) {
            q.push(num + "0");
            q.push(num + "1");
            remSet.insert(rem);
        }
    }

    return "";
}

int main() {
    return 0;
}
/*
x % N = rem
y % N = rem
x is smaller than y
yz % N = 0
[1/0 * 10^i % N + 1/0 *10^j % N +...]<= z ka representation
aisehi same y ka banega withjo append hoga,
if already same rem with smaller digit h tu no need for bigger digit!!
i,j-> set bits in decimal representation
*/
