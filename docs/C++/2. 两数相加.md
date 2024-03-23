## [2. 两数相加](https://leetcode-cn.com/problems/add-two-numbers/)

### 题目描述

给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

**示例**

```
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
```

### 解题思路

### 题解

遍历相加注意进位即可。

#### C++

```c
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;

        ListNode *iter = new ListNode(-1);
        ListNode *head = iter;
        int carry = 0;
        while (l1 != nullptr and l2 != nullptr)
        {
            carry = l1->val + l2->val + carry;
            ListNode *node = new ListNode(carry % 10);
            iter->next = node;
            iter = node;
            carry = carry / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1 != nullptr)
        {
            carry = l1->val + carry;
            ListNode *node = new ListNode(carry % 10);
            iter->next = node;
            iter = node;
            carry = carry / 10;
            l1 = l1->next;

        }
        while (l2 != nullptr)
        {
            carry = l2->val + carry;
            ListNode *node = new ListNode(carry % 10);
            iter->next = node;
            iter = node;
            carry = carry / 10;
            l2 = l2->next;
        }
        if (carry > 0)
        {
            ListNode *node = new ListNode(carry);
            iter->next = node;
        }
        return head->next;
    }
};
```

#### python

```python
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        if not l1:
            return l2
        if not l2:
            return l1
        
        carry = 0
        head = ListNode(-1)
        iters = head
        while(l1 and l2):
            carry = l1.val + l2.val + carry
            node = ListNode(carry % 10)
            carry = carry // 10
            iters.next = node
            iters = node
            l1 = l1.next
            l2 = l2.next
        while(l1):
            carry = l1.val + carry
            node = ListNode(carry % 10)
            carry = carry // 10
            iters.next = node
            iters = node
            l1 = l1.next
        while(l2):
            carry = l2.val + carry
            node = ListNode(carry % 10)
            carry = carry // 10
            iters.next = node
            iters = node
            l2 = l2.next
        if carry > 0:
            node = ListNode(carry)
            iters.next = node

        return head.next
```