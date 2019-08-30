/*
Hi, here's your problem today. This problem was recently asked by Twitter:

Given a string with the initial condition of dominoes, where:

. represents that the domino is standing still
L represents that the domino is falling to the left side
R represents that the domino is falling to the right side

Figure out the final position of the dominoes. If there are dominoes that get pushed on both ends, the force cancels out and that domino remains upright.

Example:
Input:  ..R...L..R.
Output: ..RR.LL..RR

*/

#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include <iterator>
#include <limits>
#include <algorithm>

#define ll long long
using namespace std;

string findDominos(string dominoes) {
	int n = dominoes.length();
	int forces[1000] = { 0 };
	int force = 0;
	for (int i = 0; i < n; i++) {
		if (dominoes[i] == 'R')
			force = n;
		else if (dominoes[i] == 'L')
			force = 0;
		else 
			force = max(force - 1, 0);
		
		forces[i] += force;
	}

	force = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (dominoes[i] == 'L')
			force = n;
		else if (dominoes[i] == 'R')
			force = 0;
		else
			force = max(force - 1, 0);

		forces[i] -= force;
	}

	string res;
	for (int i = 0; i < n; i++) {
		if (forces[i] > 0)
			res += 'R';
		else if (forces[i] < 0)
			res += 'L';
		else
			res += '.';
	}

	return res;
}

int main() {
	string str;
	cin >> str;
	cout << findDominos(str);

	return 0;
}
