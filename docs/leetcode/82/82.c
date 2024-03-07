#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head){
    if (head == NULL || head->next == NULL) return head;
    struct ListNode *preStart, *start, *end;
    struct ListNode *g = (struct ListNode *)malloc(sizeof(struct ListNode));
    g->next = head;
    preStart = g;
    start = g->next;
    end = start->next;
    int same = 0;
    while (end) {
        same = 0;
        while (end && end->val == start->val) {
            same = 1;
            end = end->next;
        }
        if (same) {
            preStart->next = end;
            start = end;
            end = (end == NULL ? NULL : end->next);
        } else {
            preStart = start;
            start = end;
            end = end->next;
        }
    }
    return g->next;
}