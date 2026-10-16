#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> ans;
    int m, n, k;
    cout<<"Size of arr1:";
    cin >> m;
    cout<<"Size of arr2:";
    cin >> n;
    cout<<"Index of target element:";
    cin >> k;

    int arr1[m];
    cout << "Enter " << m << " elements for arr1: ";
    for(int x = 0; x < m; x++) cin >> arr1[x];

    int arr2[n];
    cout << "Enter " << n << " elements for arr2: ";
    for(int x = 0; x < n; x++) cin >> arr2[x];

    int i = 0, j = 0;
    while(i < m && j < n){
        if(arr1[i] < arr2[j]){
            ans.push_back(arr1[i]);
            i++;
        }
        else{
            ans.push_back(arr2[j]);
            j++;
        }
    }
    while(i < m){
        ans.push_back(arr1[i]);
        i++;
    }
    while(j < n){
        ans.push_back(arr2[j]);
        j++;
    }
    cout << "Output element:"<<ans[k];
}