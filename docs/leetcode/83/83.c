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
    struct ListNode *iter = head;
    while (iter && iter->next) {
        if (iter->val == iter->next->val) {
            iter->next = iter->next->next;
        } else {
            iter = iter->next;
        }

    }
    return head;
}