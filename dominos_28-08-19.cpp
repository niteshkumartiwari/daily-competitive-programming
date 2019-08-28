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

#include "bits/stdc++.h"
#define ll long long
using namespace std;

void findFinalState(string dominos){
	deque<pair<char,int>> dq;

	bool flag=false;//false- R | true-L
	for(int i=0;i<dominos.length();i++){
		if(dominos[i]!='.')
			dq.push_back({dominos[i],i});
	}

	if(dq.size()==0){
		cout<<dominos;
		return;
	}

	if(dq.front().first=='L'){
		int i=0;
		while(i < dq.front().second){
			cout<<'L';
			i++;
		}
	}
	else{// if its . or R
		int i=0;
		while(i < dq.front().first){
			cout<<'.';
		}
	}

	pair<char,int> f,s;
	while(dq.size()>=2){
		f = dq.pop_front();
		s = dq.pop_front();

		int l = f.second +1;
		int r = s.second -1;
		int mid = (l+r)/2;

		if(f.first == 'R' && s.first =='L'){
			if(l-r ==1)
				cout<<'.';
			else if((l-r)%2 == 0){//#of dots is odd then mid will be '.'
				int i=l;
				while(i<mid){
					cout<<'R';
					i++;
				}
				cout<<'.';
				i++;
				while(i<r){
					cout<<'L';
					i++;
				}

			}
			else if((l-r)%2 != 0){//even #of dots, no dots 
				int i=l;
				while(i<= mid){
					cout<<'R';
					i++;
				}

				while(i<r){
					cout<<'L';
					i++;
				}
			}
		}

		else if(f.first=='L' && s.first=='R'){
			int i=l;
			while(i<r)
				cout<<'.';
		}

		else if(f.first=='L' && s.first=='L'){
			int i=l;
			while(i<r)
				cout<<'L';
		}

		else if(f.first=='R' && s.first=='R'){
			int i=l;
			while(i<r)
				cout<<'R';
		}

		if(dq.size()==0)
			break;
		dq.push_front(s);
	}

	if(s.first =='R'){
		int i=s.second;
		while(i<dominos.length()){
			cout<<'R';
			i++;
		}
	}
	else{
		int i=s.second;
		while(i<dominos.length()){
			cout<<'L';
			i++;
		}
	}
}

int main(){
	string dominos;
	cin>>dominos;

	findFinalState(dominos);

	return 0;
}