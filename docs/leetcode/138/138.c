#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

//Definition for a Node.
struct Node {
    int val;
    struct TreeNode *next;
    struct TreeNode *random;
};

struct Node* copyRandomList(struct Node* head) {
	if (head == NULL) {
        return NULL;
    }

    struct Node *iter = head;
    while (iter) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->val = iter->val;
        newNode->next = iter->next;
        iter->next = newNode;
        iter = newNode->next;
    }
    iter = head;
    while (iter && iter->next) {
        iter->next->random = (iter->random == NULL ? NULL :  iter->random->next);
        iter = iter->next->next;
    }
    iter = head->next;
    while (iter && iter->next) {
        iter->next = iter->next->next;
        iter = iter->next;
    }
    return head->next;
}