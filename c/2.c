/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head;
    struct ListNode *iter;
    struct ListNode *newNode;
    int carry = 0;
    int num;

    newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->next = NULL;
    iter = newNode;
    head = newNode;

    while (l1 && l2) {
        num = l1->val + l2->val + carry;
        carry = num / 10;
        num = num % 10;
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = num;
        newNode->next = NULL;
        iter->next = newNode;
        iter = newNode;
        l1 = l1->next;
        l2 = l2->next;
    }
    while (l1) {
        num = l1->val + carry;
        carry = num / 10;
        num = num % 10;
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = num;
        newNode->next = NULL;
        iter->next = newNode;
        iter = newNode;
        l1 = l1->next;
    }
    while (l2) {
        num = l2->val + carry;
        carry = num / 10;
        num = num % 10;
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = num;
        newNode->next = NULL;
        iter->next = newNode;
        iter = newNode;
        l2 = l2->next;
    }

    if (carry) {
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = carry;
        newNode->next = NULL;
        iter->next = newNode;
        iter = newNode;
        carry = 0;
    }
    return head->next;
}