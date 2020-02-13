/*
Problem Description
Deepthi loves cruises. She is going to visit the Caribbean on a Cruise. So, she thought of providing everyone who is traveling with her with lunch as well. Each food item is denoted by an integer ID. A lunchbox contains exactly A food items. She has a list of food items with her denoted by an integer array B. She asked you to tell her the maximum number of lunchboxes she can prepare. Note: A lunch box can contain multiple same kinds of food items but the content of each lunch box should be the same.           


Problem Constraints
1 <= A <= |B| <= 100000
1 <= B[i] <= 100000


Input Format
First argument of input is integer A
Second argument of input is an integer array B


Output Format
Return a single integer denoting the maximum number of lunch boxes that can be prepared.


Example Input
Input 1:
A = 3, B = [1, 2, 3, 2, 6, 1, 3]
Input 2:
A = 4, B = [1, 3, 1, 3, 10, 3, 6, 6, 13]
         


Example Output
 Output 1:
2
Output 2:
1
         


Example Explanation
 Explanation 1: 
She can choose the content to be [1, 2, 3] and prepare 2 luchboxes
 Explanation 2:
She can choose the content to be [1, 3, 3, 3]
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;


int solve(int A, vector<int> &B) {
    unordered_map<int,int> um;
    for(int i=0;i<B.size();i++)
        um[B[i]]++;
        
    vector<int> vec;
    for(auto it:um)
        vec.push_back(it.second);

    //sort(vec.begin(),vec.end());//zaroorat nhi h

    int l=1,r= B.size();
    int ans=1;

    function<bool(int)> isPossible = [&](int lboxes){
        int count=0;
        for(int i=0;i<vec.size();i++){
            if(vec[i]>=lboxes)
                count+=vec[i]/lboxes;
            if(count>=A)
                return true;
        }

        return false;
    };

    while(l<=r){
        int mid= l+(r-l)/2;

        if(isPossible(mid)){
            l=mid+1;
            ans=mid;
        }
        else
            r=mid-1;
    }

    return ans;
}



int main(){
    vector<int> B{1, 3, 1, 3, 10, 3, 6, 6, 13, 3};
    int A=4;

    cout<<solve(A,B);
  

    return 0;
}