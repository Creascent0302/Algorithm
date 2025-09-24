#include <string>
#include <unordered_set>
using namespace std;
// 计数排序（这种固定数量且小规模的可以直接计数暴力排序）+位运算优化！！
class Solution
{
private:
    const int bit_set = (1 << 1) + (1 << 5) + (1 << 9) + (1 << 15) + (1 << 21);

public:
    string sortVowels(string s)
    {
        unordered_map<char, int> cnt;
        for (const auto &c : s)
        {
            if ((bit_set >> (c & 31)) & 1 == 1)
                cnt[c]++;
        }
        string aeiou = "AEIOUaeiou";
        int idx = 0;
        char ch = aeiou[idx];
        for (auto &c : s)
        {
            if ((bit_set >> (c & 31)) & 1 == 1)
            {
                while (cnt[ch] <= 0)
                {
                    ch = aeiou[++idx];
                }
                c = ch;
                cnt[ch]--;
            }
        }
        return s;
    }
};

#include <iostream>
int main()
{
    Solution sol = Solution();
    string s = "lEetcOde";
    string c = sol.sortVowels(s);
    cout << c << endl;
}