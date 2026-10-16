#include <iostream>
using namespace std;
int n;
int main()
{
cin>>n;
int arr[n];
for(int i=0;i<n;i++){
cin>>arr[i];
}
for(int i=0;i<n;i++){
cout<<arr[i]<<" ";
}
int low=0;
int high=n-1;
int ans=n;
while(low<=high){
    int mid=(low+high)/2;
    if(arr[mid]==1){
        ans=mid;
        high=mid-1;
    }
    else
      low=mid+1;
}
cout<<endl<<"Total 1s found: "<<n-ans<<endl;
cout<<"Total 0s found: "<<ans<<endl;
}