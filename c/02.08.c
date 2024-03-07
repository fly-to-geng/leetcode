/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        return NULL;
    }

    struct ListNode *slow = head->next;
    struct ListNode *quick = head->next->next;

    // 快慢指针直到两个指针相遇
    while (slow != NULL && quick != NULL && slow != quick) {
        if (slow->next == NULL) return NULL;
        if (quick->next == NULL) return NULL;
        if (quick->next->next == NULL) return NULL;
        slow = slow->next;
        quick = quick->next->next;
    }

    // 找到入口的位置
    slow = head;
    while (slow != quick) {
        slow = slow->next;
        quick = quick->next;
    }
    return slow;
}