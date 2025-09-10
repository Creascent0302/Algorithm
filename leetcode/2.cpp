
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int v = (l1->val + l2->val) % 10;
        int add = (l1->val + l2->val) / 10;
        ListNode *ans = new ListNode(v);
        l1 = l1->next, l2 = l2->next;
        ListNode *current = ans;
        while (l1 || l2)
        {
            int v1 = 0, v2 = 0;
            if (l1)
                v1 = l1->val;
            if (l2)
                v2 = l2->val;
            int sum = (v1 + v2 + add);
            v = sum % 10;
            add = sum / 10;
            ListNode *next = new ListNode(v);
            current->next = next;
            current = current->next;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        if (add == 1)
        {
            ListNode *next = new ListNode(1);
            current->next = next;
        }
        return ans;
    }
};