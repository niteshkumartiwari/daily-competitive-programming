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

#define ll long long
using namespace std;

void findFinalState(string dominos) {
	deque<pair<char, int>> dq;

	bool flag = false;//false- R | true-L
	for (int i = 0; i < dominos.length(); i++) {
		if (dominos[i] != '.')
			dq.push_back({ dominos[i],i });
	}

	if (dq.size() == 0) {
		cout << dominos;
		return;
	}

	if (dq.size() == 1) {
		int idx = 0;

		if (dq.front().first == 'L') {
			int i;
			for (i = 0; i <= dq.front().second; i++)
				cout << 'L';
			while (i < dominos.length()) {
				cout << '.';
				i++;
			}

			return;
		}
		else {
			int i = 0;
			for (i = 0; i < dq.front().second; i++)
				cout << '.';
			cout << 'R';
			i++;
			while (i < dominos.length()) {
				cout << '.';
				i++;
			}
			return;

		}
	}

	if (dq.front().first == 'L') {
		int i = 0;
		while (i < dq.front().second) {
			cout << 'L';
			i++;
		}
	}
	else {// if its . or R
		int i = 0;
		while (i < dq.front().second) {
			cout << '.';
			i++;
		}
	}

	char fchar, schar;
	int fidx, sidx;
	while (dq.size() >= 2) {
		fchar = dq.front().first;
		fidx = dq.front().second;
		dq.pop_front();
		schar = dq.front().first;
		sidx = dq.front().second;
		dq.pop_front();

		int l = fidx + 1;
		int r = sidx - 1;
		int mid = (l + r) / 2;

		if (fchar == 'R' && schar == 'L') {
			if (r-l == 1)
				cout << '.';
			else if ((r-l) % 2 == 0) {//#of dots is odd then mid will be '.'
				int i = fidx;
				while (i < mid) {
					cout << 'R';
					i++;
				}
				cout << '.';
				i++;
				while (i <= r) {
					cout << 'L';
					i++;
				}

			}
			else if ((l - r) % 2 != 0) {//even #of dots, no dots 
				int i = fidx;
				while (i <= mid) {
					cout << 'R';
					i++;
				}

				while (i <= r) {
					cout << 'L';
					i++;
				}
			}
		}

		else if (fchar == 'L' && schar == 'R') {
			int i = fidx;
			cout << 'L';
			i++;
			while (i <= r) {
				cout << '.';
				i++;
			}
		}

		else if (fchar == 'L' && schar == 'L') {
			int i = fidx;
			while (i <= r) {
				cout << 'L';
				i++;
			}
		}

		else if (fchar == 'R' && schar == 'R') {
			int i = fidx;
			while (i <= r) {
				cout << 'R';
				i++;
			}
		}

		if (dq.size() == 0)
			break;
		dq.push_front({ schar,sidx });
	}

	if (schar == 'R') {
		int i = sidx;
		while (i < dominos.length()) {
			cout << 'R';
			i++;
		}
	}
	else {
		int i = sidx;
		cout << 'L';
		i++;
		while (i < dominos.length()) {
			cout << '.';
			i++;
		}
	}
}

int main() {
	string dominos;
	cin >> dominos;

	findFinalState(dominos);

	return 0;
}
