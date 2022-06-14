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
    // Traversal Order : root, left, right
    vector<int> preorderIterativeTraversal(TreeNode *root) {
        vector<int> visitOrder;  // this will keep track of the visited nodes sequentially
        stack<TreeNode *> stk;   // a stack that will keep the yet to process/visit nodes
        TreeNode *curr = root;   // this will point to the current node

        while (!stk.empty() || curr != nullptr) {
            // when we visit any node the first time, we process it,
            // push the node into the stack (to process the right subtree of that node later), and go to the left child.
            if (curr != nullptr) {
                visitOrder.push_back(curr->val);
                stk.push(curr);
                curr = curr->left;
            }

            // If there’s no left child, we grab one node from the top of the stack and go to the right child of that node.
            // Now we continue the same process for the subtree rooted at the right child of the popped node.
            else {
                curr = stk.top();
                stk.pop();
                curr = curr->right;
            }
        }
        return visitOrder;
    }

    // Traversal Order : left, root, right
    vector<int> inorderIterativeTraversal(TreeNode *root) {
        vector<int> visitOrder;  // this will keep track of the visited nodes sequentially
        stack<TreeNode *> stk;   // a stack that will keep the yet to process/visit nodes
        TreeNode *curr = root;   // this will point to the current node

        while (!stk.empty() || curr != nullptr) {
            // before processing the left subtree of any node,
            // we need to save the node on a stack (to process the node and right subtree of that node).
            // Then we go to the left child of that node.
            if (curr != nullptr) {
                stk.push(curr);
                curr = curr->left;
            }

            // After processing all the nodes in the left subtree,
            // we pop the top node the stack, visit it,
            // and go to the right child of that node to traverse the right subtree.
            else {
                curr = stk.top();
                stk.pop();
                visitOrder.push_back(curr->val);
                curr = curr->right;
            }
        }
        return visitOrder;
    }

    // Traversal Order : root, left, right
    // As the reverse of this is order is : root, right, left which is very close to Preorder Traversal (root, left, right)
    // The only difference is that the right child is visited before left child
    // So, we can do something like iterative preorder traversal with the following differences:
    // Instead of adding it to a normal visit order, we push it to a stack which will be reversed later
    // We push the right child before the left
    vector<int> postorderIterativeTraversal(TreeNode *root) {
        stack<int> reverseVisitOrder;  // this will store the reverse of the actual visit order
        vector<int> visitOrder;        // this will keep track of the visited nodes sequentially
        stack<TreeNode *> stk;         // a stack that will keep the yet to process/visit nodes
        TreeNode *curr = root;         // this will point to the current node

        while (!stk.empty() || curr != nullptr) {
            // when we visit any node the first time, we process it,
            // push the node into the stack (to process the left subtree of that node later), and go to the right child.
            if (curr != nullptr) {
                reverseVisitOrder.push(curr->val);  // push it to the reverseVisitOrder stack
                stk.push(curr);
                curr = curr->right;
            }

            // If there’s no right child, we grab one node from the top of the stack and go to the left child of that node.
            // Now we continue the same process for the subtree rooted at the left child of the popped node.
            else {
                curr = stk.top();
                stk.pop();
                curr = curr->left;
            }
        }

        // now time to get the actual visitOrder
        while (!reverseVisitOrder.empty()) {
            visitOrder.push_back(reverseVisitOrder.top());
            reverseVisitOrder.pop();
        }

        return visitOrder;
    }
};

class Test {
   public:
    void testPreorderIterativeTraversal() {
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
        vector<int> res = sln.preorderIterativeTraversal(treeRoot);

        for (int num : res) {
            cout << num << " ";
        }
        cout << endl;
    }

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
        cout << endl;
    }

    void testPostorderIterativeTraversal() {
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
        vector<int> res = sln.postorderIterativeTraversal(treeRoot);

        for (int num : res) {
            cout << num << " ";
        }
        cout << endl;
    }
};

int main() {
    Test test;
    // test.testInorderIterativeTraversal();
    // test.testPreorderIterativeTraversal();
    test.testPostorderIterativeTraversal();
    return 0;
}