#include <iostream>
#include <queue>

// 二叉树节点的定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// 计算二叉树的最小深度
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

            // 如果遇到第一个叶子节点，直接返回深度
            if (!node->left && !node->right) {
                return depth;
            }

            // 将非空子节点加入队列
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }

        // 移动到下一层
        ++depth;
    }

    return depth;
}

int main() {
    // 构建一个简单的二叉树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // 计算最小深度并输出结果
    int result = minDepth(root);
    std::cout << "Minimum Depth of the Binary Tree: " << result << std::endl;

    // 释放二叉树内存
    // 这里省略了释放内存的代码，实际应用中应该确保进行适当的内存管理

    return 0;
}
