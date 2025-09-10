#include <vector>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<int> result;
        unordered_map<int, int> map;
        for (int i = 0; i < n; i++)
        {
            int a = target - nums[i];
            if (map.find(a) != map.end())
            {
                result.push_back(i);
                result.push_back(map[a]);
                return result;
            }
            else
            {
                map[nums[i]] = i;
            }
        }
        return result;
    }
};