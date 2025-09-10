#include <vector>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int head = 0, tail = 0;
        unordered_map<char, int> map;
        int max_length = 0;
        for (tail; tail < s.length(); tail++)
        {
            char c = s[tail];
            if (map.find(c) != map.end())
            {
                head = (map[c] + 1) > head ? (map[c] + 1) : head;
            }
            map[c] = tail;
            max_length = (tail + 1 - head) > max_length ? (tail + 1 - head) : max_length;
        }
        return max_length;
    }
};