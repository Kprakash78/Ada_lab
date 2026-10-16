#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[]={1,2,4,5};
    int n ;
    int sum =0;
    cout<<"Enter the value of n:";
    cin>>n;

    for(int x:arr){
        sum += x;
    }
    int expected_sum = (n*(n+1))/2;
    int missing_num = expected_sum-sum;

    cout<<"Missing number:"<<missing_num;
}