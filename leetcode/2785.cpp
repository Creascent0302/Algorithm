#include <string>
#include <unordered_set>
using namespace std;
// 变异快排
class Solution
{
private:
    unordered_set<char> characters = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

public:
    void sortString(string &s, int left, int right)
    {
        if (left > right)
            return;
        int l = left, r = right;
        int index = left;
        bool flag = false;
        // 找一个元音字符作为标准
        for (int i = left; i < right; i++)
        {
            if (characters.count(s[i]) > 0)
            {
                index = i;
                flag = true;
                break;
            }
        }
        if (!flag)
            return;
        auto c = s[index];
        while (l <= r)
        {
            while ((l <= r) && ((characters.count(s[l]) <= 0) || s[l] < c))
            {
                l++;
            }
            while ((l <= r) && ((characters.count(s[r]) <= 0) || s[r] > c))
            {
                r--;
            }
            if (l <= r)
            {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        sortString(s, left, r);
        sortString(s, l, right);
        return;
    }
    string sortVowels(string s)
    {
        sortString(s, 0, s.size() - 1);
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