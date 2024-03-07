#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode NODE;

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    if (head == NULL || k <= 1) {
        return head;
    }

    NODE *preStart, *endNext, *start, *end, *iter;
    NODE *g = (NODE*)malloc(sizeof(NODE));
    g->next = head;
    preStart = g;
    endNext = g->next;
    int tmpk = k;
    while (1) {
        tmpk = k;
        endNext = preStart->next;
        while (tmpk && endNext) {
            endNext = endNext->next;
            tmpk--;
        }
        if (tmpk > 0) {
            break;
        }

        start = preStart->next;
        end = start->next;
        start->next = NULL;
        while (end != endNext) {
            iter = end->next;
            end->next = start;
            start = end;
            end = iter;
        }

        NODE *tmp = preStart->next;
        preStart->next->next = end;
        preStart->next = start;
        preStart = tmp;
    }
    return g->next;
}