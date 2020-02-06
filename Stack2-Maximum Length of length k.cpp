/*

*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

//maximum no of len=k
vector<int> maxArray(vector<int>A ,int k){
    int n=A.size();
    vector<int> ans(k,0);

    for(int i=0,j=0;i<n;i++){
        while(n-i+j > k && j>0 && ans[j-1] < A[i])j--;
        if(j<k)ans[j++]= A[i];
    }

    return ans;
}


int main(){
    vector<int> A{1,2,9,3,4,20,7};
    int k=4;

    auto res= maxArray(A,k);
    for(int val: res)
        cout<<val<<" ";

    return 0;
}