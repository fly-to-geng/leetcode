/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *g;
    struct ListNode *c;
    struct ListNode *p;

    g = (struct ListNode*)malloc(sizeof(struct ListNode));
    g->next = head;

    if (head == NULL) {
        return head;
    }

    // 提前走n+1步
    n = n + 1;
    c = g;
    while (c && n) {
        c = c->next;
        n = n - 1;
    }

    // 一起走知道c为空
    p = g;
    while (c) {
        c = c->next;
        p = p->next;
    }

    // p的下一个结点为要删除的节点
    p->next = p->next->next;
    return g->next;
}