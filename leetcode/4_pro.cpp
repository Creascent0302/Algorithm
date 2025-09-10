#include <vector>
#include <initializer_list>
using namespace std;
class Solution
{
public:
    // 找到不大于目标点的位置，如果都大于目标点则返回 -1
    int binarySearch(int target, vector<int> &nums, int l, int r)
    {
        int left = l, right = r, result = l - 1;
        if (nums.empty() || (left > right))
            return result;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (target >= nums[mid])
            {
                result = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return result;
    }

    // 猜数二分
    template <typename... Args>
    double findMedianSortedArrays(Args... args)
    {
        vector<vector<int>> vecs = {args...};
        return findMedianArrays(vecs);
    }
    double findMedianArrays(vector<vector<int>> &vecs)
    {
        int vec_num = vecs.size();
        int left = INT_MAX, right = INT_MIN, total_len = 0;
        for (auto it = vecs.begin(); it != vecs.end();)
        {
            if (it->empty())
            {
                it = vecs.erase(it);
            }
            else
            {
                total_len += it->size();
                left = min(left, it->front());
                right = max(right, it->back());
                ++it;
            }
        }
        double result = 0.0;
        // 需要分奇偶讨论，因为偶数需要猜出来两个数，奇数只需要猜一个数
        if (total_len % 2 == 0)
        {
            int lres = 0, rres = 0;
            int mid = (left + right) / 2;
            int left1 = left, right1 = right;
            int total_left = 0, total_right = 0;
            while (left <= right)
            {
                total_left = 0;
                for (auto vec : vecs)
                {
                    int index = binarySearch(mid, vec, 0, vec.size() - 1);
                    total_left += index + 1;
                }
                total_right = total_len - total_left;
                if (total_left >= total_right)
                {
                    lres = mid;
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
                mid = (left + right) / 2;
            }

            mid = (left1 + right1) / 2;
            while (left1 <= right1)
            {
                total_left = 0;
                for (auto vec : vecs)
                {
                    int index = binarySearch(mid, vec, 0, vec.size() - 1);
                    total_left += index + 1;
                }
                total_right = total_len - total_left;
                if (total_left >= total_right + 2)
                {
                    rres = mid;
                    right1 = mid - 1;
                }
                else
                {
                    left1 = mid + 1;
                }
                mid = (left1 + right1) / 2;
            }
            result = 0.5 * (lres + rres);
        }
        else
        {
            // 奇数情况
            int res = 0;
            int mid = (left + right) / 2;
            int total_left = 0, total_right = 0;
            while (left <= right)
            {
                total_left = 0;
                for (auto vec : vecs)
                {
                    int index = binarySearch(mid, vec, 0, vec.size() - 1);
                    total_left += index + 1;
                }
                total_right = total_len - total_left;

                if (total_left >= total_right + 1)
                {
                    res = mid;
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
                mid = (left + right) / 2;
            }
            result = double(res);
        }
        return result;
    }
};
