/*
Given a non-empty string str and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".
Example 1:
str = "aabbcc", k = 3

Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
str = "aaabc", k = 3 

Answer: ""

It is not possible to rearrange the string.
Example 3:
str = "aaadbbcc", k = 2

Answer: "abacabcd"

Another possible answer is: "abcabcda"

The same letters are at least distance 2 from each other.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

typedef pair<int, int> pi;
string rearrange(string s, int k) {
    if (k == 0 || s.length() < k) return s;
    int map[26] = {0};

    for (char ch : s)
        map[ch - 'a']++;

    priority_queue<pi> pq;

    for (int i = 0; i < 26; i++) {
        if (map[i] > 0) pq.emplace(map[i], i);
    }

    string res;

    while (!pq.empty()) {
        vector<int> temp;
        for (int i = 0; i < k; i++) {
            int freq = pq.top().first;
            int idx = pq.top().second;
            pq.pop();
            res += (idx + 'a');
            temp.push_back(idx);

            if (pq.empty()) {
                if (i != k - 1 && res.length() != s.length())
                    return "";
                else
                    break;
            }
        }

        for (int idx : temp) {
            if (--map[idx] > 0)
                pq.emplace(map[idx], idx);
        }
    }

    return res;
}

int main() {
    string s = "aaadbbcc";
    int k = 2;
    cout << rearrange(s, k);
    return 0;
}
