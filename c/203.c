/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeElements(struct ListNode* head, int val){
    struct ListNode *pre;
    struct ListNode *curr;
    struct ListNode *g;

    g = (struct ListNode*)malloc(sizeof(struct ListNode));
    g->next = head;
    pre = g;
    curr = head;

    while (curr) {
        if (curr && curr->val == val) {
            pre->next = curr->next;
            curr = curr->next;
        } else {
            pre = curr;
            curr = curr->next;
        }
    }
    return g->next;
}