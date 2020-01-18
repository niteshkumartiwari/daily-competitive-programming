/*
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> computeLPS(string pat) {
    int n = pat.size();
    int len = 0, i = 1;
    vector<int> lps(n, 0);

    while (i < n) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }

    return lps;
}

void search(string str, string pat) {
    vector<int> lps = computeLPS(pat);

    int n = str.length(), m = pat.length();

    int i = 0, j = 0;
    while (i < n) {
        if (str[i] == pat[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "found @" << i - j << endl;
            j = lps[j - 1];
        }

        else if (i < n && pat[j] != str[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    string str = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";

    search(str, pat);
    return 0;
}
