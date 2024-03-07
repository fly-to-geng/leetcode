# [19. 删除链表的倒数第N个节点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)

## 题目描述

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

      给定一个链表: 1->2->3->4->5, 和 n = 2.

      当删除了倒数第二个节点后，链表变为 1->2->3->5.
      说明：

      给定的 n 保证是有效的。

进阶：

      你能尝试使用一趟扫描实现吗？

## 解题思路

- 常规解法
假设链表为link, 节点个数为N，倒数第n个节点，就是正数第(N-n+1)个节点，删除该节点，需要找到它前面的节点，也就是第(N-n)个节点。
如果(N-n)==0, 直接用头结点指向第二个节点，即删除了第一个节点；
其他情况，找到第(N-n)节点，next指针指向下下个节点；


- 一次遍历的解法
设置两个指针，间隔n, 然后一起移动两个指针，前面的到结尾，后面的指针正好指向倒数第n个节点前一个。

```c
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
```
