#include <iostream>
#include <queue>

// �������ڵ�Ķ���
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// �������������С���
int minDepth(TreeNode* root) {
    if (!root) {
        return 0;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    int depth = 1;

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            // ���������һ��Ҷ�ӽڵ㣬ֱ�ӷ������
            if (!node->left && !node->right) {
                return depth;
            }

            // ���ǿ��ӽڵ�������
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }

        // �ƶ�����һ��
        ++depth;
    }

    return depth;
}

int main() {
    // ����һ���򵥵Ķ�����
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // ������С��Ȳ�������
    int result = minDepth(root);
    std::cout << "Minimum Depth of the Binary Tree: " << result << std::endl;

    // �ͷŶ������ڴ�
    // ����ʡ�����ͷ��ڴ�Ĵ��룬ʵ��Ӧ����Ӧ��ȷ�������ʵ����ڴ����

    return 0;
}
