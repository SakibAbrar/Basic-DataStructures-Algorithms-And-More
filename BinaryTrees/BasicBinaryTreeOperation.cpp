#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   public:
    // Traversal Order : left, root, right
    vector<int> inorderIterativeTraversal(TreeNode *root) {
        vector<int> ret;        // this will keep track of the visited nodes sequentially
        stack<TreeNode *> stk;  // a stack that will keep the yet to process/visit nodes
        TreeNode *curr = root;

        while (!stk.empty() || curr != nullptr) {
            // keep going to the left until no left is availabe
            // add every node to the stack as those are yet to process/visit
            while (curr != nullptr) {
                stk.push(curr);
                curr = curr->left;
            }
            // most recently pushed node has no more left
            // meaning we can visit it now and pop it from the stack
            // then work with it's right subtree similarly
            curr = stk.top();
            stk.pop();
            ret.push_back(curr->val);
            curr = curr->right;
        }
        return ret;
    }
};

class Test {
   public:
    void testInorderIterativeTraversal() {
        /*
        Constructed binary tree is
                  1
                /   \
              2      3
            /  \
          4     5

        */
        TreeNode *treeRoot = new TreeNode(1);
        treeRoot->left = new TreeNode(2);
        treeRoot->right = new TreeNode(3);
        treeRoot->left->left = new TreeNode(4);
        treeRoot->left->right = new TreeNode(5);

        Solution sln;
        vector<int> res = sln.inorderIterativeTraversal(treeRoot);

        for (int num : res) {
            cout << num << " ";
        }
    }
};

int main() {
    Test test;
    // test.testInorderIterativeTraversal();
    return 0;
}