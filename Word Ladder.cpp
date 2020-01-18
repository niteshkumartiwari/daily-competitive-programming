/*
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",return its length 5
*/
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
   public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordDict(wordList.begin(), wordList.end());
        wordDict.erase(beginWord);
        if (wordDict.find(endWord) == wordDict.end()) return 0;
        wordDict.erase(endWord);

        unordered_set<string> nextWords, prevWords;
        nextWords.insert(beginWord);
        prevWords.insert(endWord);
        int ladder = 2;
        int len = beginWord.length();

        while (!nextWords.empty() && !prevWords.empty()) {
            if (nextWords.size() > prevWords.size())
                swap(nextWords, prevWords);

            unordered_set<string> temp;  //to store next level of nextWords
            //otherwise we wont know when to stop nextWords loop!
            for (auto& itr : nextWords) {
                string str = itr;
                for (int i = 0; i < len; i++) {
                    char letter = str[i];
                    for (int j = 0; j < 26; j++) {
                        str[i] = 'a' + j;

                        if (prevWords.find(str) != prevWords.end())
                            return ladder;
                        if (wordDict.find(str) != wordDict.end()) {
                            temp.insert(str);
                            wordDict.erase(str);
                        }
                    }
                    str[i] = letter;
                }
            }

            ladder++;
            swap(nextWords, temp);
        }

        return 0;
    }
};

/*
//BFS， two-end method
//traverse the path simultaneously from start node and end node, and merge in the middle
//the speed will increase (logN/2)^2 times compared with one-end method
I agree with sqrt(N)/2. Say the ladder is of length 'len', and each word branches out 'm' new words.
From one end, we have to generate O(m^len) branches. Yet from both ends, we are only supposed to generate O(2m^(len/2)) braches.
 So we are sqrt(m^len)/2 times faster.
*/

int main() {
    return 0;
}
