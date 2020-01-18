/*
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> getZarray(string str) {
    int n = str.length();
    vector<int> zarray(n, 0);
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i > right) {
            /*
            i > R then there is no prefix substring that starts before i and 
   ends after i, so we reset L and R and compute new [L,R] by comparing 
   str[0..] to str[i..] and get Z[i] (= R-L+1).
            */
            left = right = i;
            while (right < n && str[right] == str[right - left])
                right++;
            zarray[i] = right - left;
            right--;
        } else {
            int k = i - left;
            if (zarray[k] < right - i + 1)
                /*
                there is no prefix substring starting at 
         str[i] (otherwise Z[K] would be larger)  so  Z[i] = Z[K]  and 
         interval [L,R] remains same.
                */
                zarray[i] = zarray[k];
            else {
                /*
                it is possible to extend the [L,R] interval
         thus we will set L as i and start matching from str[R]  onwards  and
         get new R then we will update interval
                */
                left = i;
                while (right < n && str[right] == str[right - left])
                    right++;
                zarray[i] = right - left;
                right--;
            }
        }
    }

    return zarray;
}

void search(string str, string pat) {
    string zstring = pat + "$" + str;
    vector<int> zarray = getZarray(zstring);

    for (int i = 0; i < zarray.size(); i++)
        if (zarray[i] == pat.length())
            cout << "found @" << i - pat.length() - 1 << endl;
}

int main() {
    string str = "GEEKS FOR GEEKS";
    string pat = "GEEKS";

    search(str, pat);
    return 0;
}
