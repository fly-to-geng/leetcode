#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
 
typedef struct ListNode NODE;
typedef struct ListNode* NODE_ARRAY;

void swap(NODE_ARRAY *nodes, int a, int b)
{
    NODE *tmp;
    tmp = nodes[a];
    nodes[a] = nodes[b];
    nodes[b] = tmp;
}
void heapify(NODE_ARRAY *nodes, int n, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int minv = i;
    if (left < n && nodes[left]->val < nodes[minv]->val) {
        minv = left;
    }
    if (right < n && nodes[right]->val < nodes[minv]->val) {
        minv = right;
    }
    if (minv != i) {
        swap(nodes, minv, i);
        heapify(nodes, n, minv);
    }
}
// 建立堆
void build(NODE_ARRAY *nodes, int n)
{
    for (int i = n / 2; i >= 0; i--) {
        heapify(nodes, n, i);
    }
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if (lists == NULL || listsSize <= 0) return NULL;
    
    NODE_ARRAY *nodes = (NODE_ARRAY*)malloc(sizeof(NODE_ARRAY) * listsSize);
    int nodesEnd = 0;
    for (int i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            nodes[nodesEnd++] = lists[i];
        }
    }
    if (nodesEnd == 0) {
        return NULL;
    }
    build(nodes, nodesEnd);
    NODE *head = (NODE*)malloc(sizeof(NODE));
    NODE *pre = head;
    while (nodesEnd > 0) {
        NODE *curr = nodes[0];
        pre->next = curr;
        pre = curr;
        if (curr->next) {
            nodes[0] = curr->next;
            heapify(nodes, nodesEnd, 0);
        } else {
            swap(nodes, 0, nodesEnd - 1);
            nodesEnd = nodesEnd - 1;
            heapify(nodes, nodesEnd, 0);
        }
    }
    return head->next;
}