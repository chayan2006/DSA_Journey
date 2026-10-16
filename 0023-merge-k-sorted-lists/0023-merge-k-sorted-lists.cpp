class Solution {
    struct Cmp {
        bool operator()(ListNode* a, ListNode* b) const {
            return a->val > b->val;  // min-heap
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Cmp> pq;
        for (ListNode* head : lists)
            if (head) pq.push(head);

        ListNode dummy;
        ListNode* tail = &dummy;
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            tail->next = node;
            tail = node;
            if (node->next) pq.push(node->next);
        }
        return dummy.next;
    }
};