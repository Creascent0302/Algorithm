#include <vector>
using namespace std;
class Solution
{
public:
    // 找到不大于目标点的位置，如果都大于目标点则返回 -1
    // int binarySearch(int target, vector<int> &nums, int l, int r)
    // {
    //     int left = l, right = r, result = l - 1;
    //     if (nums.empty() || (left > right))
    //         return result;
    //     while (left <= right)
    //     {
    //         int mid = left + (right - left) / 2;
    //         if (target >= nums[mid])
    //         {
    //             result = mid;
    //             left = mid + 1;
    //         }
    //         else
    //         {
    //             right = mid - 1;
    //         }
    //     }
    //     return result;
    // }

    // 很不错的二分解法题，重要的是确定好左右移动条件
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 > len2)
            return findMedianSortedArrays(nums2, nums1); // 快速交换，不用拷贝 vector 进行交换，节省时间内存

        int mid = (len1 + len2 + 1) / 2;
        int left = 0, right = len1;
        int i = 0, j = 0;
        int left_max = INT_MAX, right_min = INT_MIN;
        while (left <= right)
        {
            i = (left + right) / 2;
            j = mid - i;
            int left_m1 = i == 0 ? INT_MIN : nums1[i - 1];
            int left_m2 = j == 0 ? INT_MIN : nums2[j - 1];
            int right_m1 = i == len1 ? INT_MAX : nums1[i];
            int right_m2 = j == len2 ? INT_MAX : nums2[j];
            if (left_m1 <= right_m2)
            {
                left = i + 1;
                left_max = max(left_m1, left_m2);
                right_min = min(right_m1, right_m2);
            }
            else
            {
                right = i - 1;
            }
        }
        double result = 0.0;
        if ((len1 + len2) % 2 == 0)
        {
            result = (left_max + right_min) / 2.0;
        }
        else
        {
            result = left_max;
        }
        return result;
    }
};

#include <iostream>
int main()
{
    vector<int> test = {2, 3, 3, 3, 4, 4, 5, 6, 7};
    Solution sol = Solution();
    // cout << sol.binarySearch(2, test, 0, 4) << endl;
}