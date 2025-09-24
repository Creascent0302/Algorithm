#include <vector>
#include <unordered_set>
using namespace std;
class Solution
{
public:
    bool haveCommonLanguage(const unordered_set<int> &set1, const unordered_set<int> &set2)
    {
        if (set1.size() > set2.size())
            return haveCommonLanguage(set2, set1);
        for (const auto &lan : set1)
        {
            if (set2.count(lan))
            {
                return true;
            }
        }
        return false;
    }
    int minimumTeachings(int n, vector<vector<int>> &languages, vector<vector<int>> &friendships)
    {
        vector<unordered_set<int>> per_lans(languages.size(), unordered_set<int>());
        for (int i = 0; i < languages.size(); i++)
        {
            for (const auto &lan : languages[i])
            {
                per_lans[i].insert(lan);
            }
        }
        unordered_set<int> cannot_talk({});
        for (const auto &fri : friendships)
        {
            if (!haveCommonLanguage(per_lans[fri[0] - 1], per_lans[fri[1] - 1]))
            {
                cannot_talk.insert(fri[0] - 1);
                cannot_talk.insert(fri[1] - 1);
            }
        }
        if (cannot_talk.empty())
            return 0;
        unordered_map<int, int> cnt;
        int max_cnt = 0;
        for (const auto &per : cannot_talk)
        {
            for (const auto &lan : per_lans[per])
            {
                cnt[lan]++;
                max_cnt = max(max_cnt, cnt[lan]);
            }
        }
        return cannot_talk.size() - max_cnt;
    }
};