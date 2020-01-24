/*
Given an array of meeting time intervals consisting of start and end times  [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
For example,
Given  [[0, 30],[5, 10],[15, 20]],
return  2.
*/

//Time: O(nlogn)
#include<bits/stdc++.h>
using namespace std;

struct Interval{
    int start,end;

    Interval(int start,int end){
        start=start;
        end=end;
    }
};

int minMeetingRooms (vector <Interval> & intervals){
    int n=intervals.size();
    if(n==0)return 0;
    sort(intervals.begin(),intervals.end(),[](Interval &a,Interval &b){return a.start < b.start;});
    priority_queue<int,vector<int>,greater<int>> pq;
    pq.push(intervals[0].end);

    for(int i=1;i<n;i++){
        int x= pq.top();
        if(x<= intervals[i].start)
            pq.pop();
        pq.push(intervals[i].end);
    }

    return pq.size();
}

int main(){


    return 0;
}