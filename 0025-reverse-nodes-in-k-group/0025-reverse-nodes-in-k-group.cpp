class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* prev = &dummy;

        while (true) {
            // check that k nodes remain after prev
            ListNode* kth = prev;
            for (int i = 0; i < k && kth; i++) kth = kth->next;
            if (!kth) break;

            // reverse the block by head-insertion
            ListNode* curr = prev->next;   // old first node, becomes tail
            for (int i = 0; i < k - 1; i++) {
                ListNode* nxt = curr->next;
                curr->next = nxt->next;
                nxt->next = prev->next;
                prev->next = nxt;
            }
            prev = curr;
        }
        return dummy.next;
    }
};