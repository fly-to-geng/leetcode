#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head){
    if (head == NULL || head->next == NULL) return head;

    struct ListNode *first = head;
    struct ListNode *second = first->next;
    struct ListNode *pre = (struct ListNode*)malloc(sizeof(struct ListNode));
    pre->next = head;
    head = second;
    while (second) {
        pre->next = second;
        first->next = second->next;
        second->next = first;
        pre = first;
        first = first->next;
        if (first) {
            second = first->next;
        } else {
            second = NULL;
        }
    }
    return head;
}