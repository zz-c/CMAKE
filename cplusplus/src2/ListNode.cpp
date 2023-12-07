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
    // ����������
    int length = 1;
    ListNode* tail = head;
    while (tail->next) {
        length++;
        tail = tail->next;
    }
    // ����ʵ���ƶ�����
    k = k % length;
    // ���kΪ0����ʾ����Ҫ�ƶ�
    if (k == 0) {
        return head;
    }
    // ��������β�������γ�ѭ������
    tail->next = head;
    // �ҵ��µ�β���ڵ�
    ListNode* newTail = head;
    for (int i = 0; i < length - k - 1; ++i) {
        newTail = newTail->next;
    }
    // �µ�ͷ���ڵ�
    ListNode* newHead = newTail->next;
    // �Ͽ�ѭ������
    newTail->next = nullptr;
    return newHead;
}

// ��ӡ����
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // ����һ������ 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "Original List: ";
    printList(head);

    // �ƶ����� 2 λ
    head = rotateRight(head, 2);

    std::cout << "Rotated List: ";
    printList(head);

    return 0;
}
