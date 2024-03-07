/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseKGroup(struct ListNode* head, int k){
    int tmpK;
    struct ListNode *start;
    struct ListNode *end;
    struct ListNode *preStart;
    struct ListNode *endNext;
    struct ListNode *iter1;
    struct ListNode *iter2;
    struct ListNode *preHead;
    // k == 1, 不用翻转
    // 没有结点，不用翻转
    if (k == 1 || head == NULL) {
        return head;
    }

    // 创建一个指向第一个结点的结点
    preHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    preHead->next = head;

    preStart = preHead;
    endNext = preHead;
    while (1) {
        // 查找从start开始的第K个结点
        tmpK = k + 1;
        while (endNext && tmpK--) {
            endNext = endNext->next;
        }
        if (tmpK > 0) {
            break; // 不足k个结点退出
        }

        // 翻转K个结点
        start = preStart->next;
        iter1 = start;
        end = start->next;
        while (end && end != endNext) {
            iter2 = end->next;
            end->next = start;
            start = end;
            end = iter2;
        }
        // 连接翻转之后的链表和其前后结点
        preStart->next = start;
        iter1->next = endNext;

        // 更新循环变量
        preStart = iter1;
        endNext = iter1;
    }
    return preHead->next;
}