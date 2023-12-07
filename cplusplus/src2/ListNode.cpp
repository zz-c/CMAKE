#include <iostream>

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) {
        return head;
    }
    // 计算链表长度
    int length = 1;
    ListNode* tail = head;
    while (tail->next) {
        length++;
        tail = tail->next;
    }
    // 计算实际移动步数
    k = k % length;
    // 如果k为0，表示不需要移动
    if (k == 0) {
        return head;
    }
    // 将链表首尾相连，形成循环链表
    tail->next = head;
    // 找到新的尾部节点
    ListNode* newTail = head;
    for (int i = 0; i < length - k - 1; ++i) {
        newTail = newTail->next;
    }
    // 新的头部节点
    ListNode* newHead = newTail->next;
    // 断开循环链表
    newTail->next = nullptr;
    return newHead;
}

// 打印链表
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // 创建一个链表 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "Original List: ";
    printList(head);

    // 移动链表 2 位
    head = rotateRight(head, 2);

    std::cout << "Rotated List: ";
    printList(head);

    return 0;
}
