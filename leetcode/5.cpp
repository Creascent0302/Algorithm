#include <string>
using namespace std;
// 中心扩散算法，不过有点麻烦没有题解简洁
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int length = s.size();
        int max_len = 1;
        string result = "";
        result += s[0];
        for (int i = 0; i < length - 1; i++)
        {
            int tmp_len = 1;
            int boundary = min(i, length - i - 1);
            int left = i;
            for (int j = 1; j <= boundary; j++)
            {
                if (s[i - j] == s[i + j])
                {
                    tmp_len += 2;
                    left = i - j;
                }
                else
                {
                    break;
                }
            }
            if (tmp_len > max_len)
            {
                max_len = tmp_len;
                result = s.substr(left, max_len);
            }

            tmp_len = 0;
            left = i;
            boundary = min(i, length - 2 - i);
            for (int j = 0; j <= boundary; j++)
            {
                if (s[i - j] == s[i + 1 + j])
                {
                    tmp_len += 2;
                    left = i - j;
                }
                else
                {
                    break;
                }
            }
            if (tmp_len > max_len)
            {
                max_len = tmp_len;
                result = s.substr(left, max_len);
            }
        }
        return result;
    }
};