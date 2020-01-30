/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]] 
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]] 
Explanation: The palindromes are ["battab","tabbat"]
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
Steps:

Traverse the array, build map. Key is the reversed string, value is index in array (0 based)

Edge case - check if empty string exists. It's interesting that for given words {"a", ""}, it's expected to return two results [0,1] and [1,0]. Since my main logic can cover [0, 1] concatenate("a", ""), so as to cover the other situation concatenate("", "a"), I need to traverse the words array again, find the palindrome word candidate except "" itself, and add pair("", palindrome word) to the final answer.

Main logic part. Partition the word into left and right, and see 1) if there exists a candidate in map equals the left side of current word, and right side of current word is palindrome, so concatenate(current word, candidate) forms a pair: left | right | candidate. 2) same for checking the right side of current word: candidate | left | right.
*/

class Solution {
    bool isPalindrome(string s) {
        int i = 0, j = s.length() - 1;

        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }

   public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        unordered_map<string, int> dict;
        vector<vector<int>> ans;

        for (int i = 0; i < n; i++) {
            string key = words[i];
            reverse(key.begin(), key.end());
            dict[key] = i;
        }

        if (dict.count("") != 0) {
            for (int i = 0; i < n; i++) {
                if (i == dict[""]) continue;
                ans.push_back({dict[""], i});
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].length(); j++) {
                string left = words[i].substr(0, j);
                string right = words[i].substr(j);

                if (dict.count(left) != 0 && isPalindrome(right) && dict[left] != i)
                    ans.push_back({i, dict[left]});

                if (dict.count(right) != 0 && isPalindrome(left) && dict[right] != i)
                    ans.push_back({dict[right], i});
            }
        }

        return ans;
    }
};

int main() {
    return 0;
}
