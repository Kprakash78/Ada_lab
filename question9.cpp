#include<bits/stdc++.h>
using namespace std;
vector<int> maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int sum = 0, maxi = INT_MIN , start=0 , end = 0 , beststart = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (sum > maxi) {
                maxi = sum;
                end = i;
                beststart = start;
            }
            if (sum < 0) {
                sum = 0;
                start = i + 1;
            }
        }
        return vector<int>(nums.begin() + start, nums.begin() + end + 1);
    }
int main()
{
    vector<int> nums1 = {-2, 11, -4, 13, -5, 2};
    vector<int> nums2 = {1, -3, 4, -2, -1,6};
    vector<int> result = maxSubArray(nums1);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << "\n";
    vector<int> result2 = maxSubArray(nums2);
    for (int i = 0; i < result2.size(); i++)
    {
        cout << result2[i] << " ";
    }
    return 0;
}