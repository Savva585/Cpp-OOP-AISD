#include <iostream>
using namespace std;

struct Node
{
    Node *left;
    Node *right;
    int value;
    int height = 0;
    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

Node *gen_balance_tree(int number)
{
    if (number <= 0)
    {
        return nullptr;
    }
    int value = rand();
    Node *root = new Node(value);
    int left_col = (number - 1) / 2;
    int right_col = (number - 1) - left_col;
    root->left = gen_balance_tree(left_col);
    root->right = gen_balance_tree(right_col);
    return root;
}

int count_non_leaves_root(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    if (root->left || root->right)
    {
        return 1 + count_non_leaves_root(root->left) + count_non_leaves_root(root->right);
    }
    return 0;
}

int count_nodes(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int sum_values(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->value + sum_values(root->left) + sum_values(root->right);
}

int sum_values(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->value + sum_values(root->left) + sum_values(root->right);
}

int find_max(Node *root)
{
    if (root == nullptr)
        return;
    if (root->right == nullptr)
        return root->value;
    return find_max(root->right);
}

int count_one_child_tree(Node *root)
{
    if (!root)
        return 0;
    int count = 0;
    if ((root->right != nullptr) + (root->left != nullptr) == 1)
    {
        count = 1;
    }
    return count + count_one_child_tree(root->right) + count_one_child_tree(root->left);
}

Node *find_in_bst(Node *root, int target)
{
    if (!root)
        return nullptr;
    if (root->value == target)
        return root;

    if (target < root->value)
    {
        return find_in_bst(root->left, target);
    }
    else
    {
        return find_in_bst(root->right, target);
    }
}

bool find(Node *root, int target)
{
    return find_in_bst(root, target) != nullptr;
}

bool is_same_tree(Node *a, Node *b)
{
    if (!a && !b)
        return true;
    if (!a || !b)
        return false;
    if (a->value != b->value)
        return false;

    return is_same_tree(a->left, b->left) &&
           is_same_tree(a->right, b->right);
}

bool is_subtree(Node *root, Node *sub_root)
{
    if (!sub_root)
        return true;
    if (!root)
        return false;

    if (root->value == sub_root->value)
    {
        if (is_same_tree(root, sub_root))
            return true;
    }

    return is_subtree(root->left, sub_root) ||
           is_subtree(root->right, sub_root);
}

Node *insertBST(Node *root, int value)
{
    if (!root)
    {
        Node *buf = new Node(value);
        root = buf;
        return root;
    }
    if (value > root->value)
    {
        root->right = insertBST(root->right, value);
    }
    else
    {
        root->left = insertBST(root->left, value);
    }
    return root;
}

void mirrorTree(Node *root)
{
    if (!root)
        return;

    Node *buf = root->left;
    root->left = root->right;
    root->right = buf;

    mirrorTree(root->right);
    mirrorTree(root->left);
}

int sumTree(Node *root)
{
    if (!root)
        return 0;
    return root->value + sumTree(root->left) + sumTree(root->right);
}

int sumAtLevel(Node *root, int level)
{
    if (!root)
        return 0;
    if (level == 0)
        return root->value;
    return sumAtLevel(root->left, level - 1) +
           sumAtLevel(root->right, level - 1);
}

void preOrder(Node *root)
{
    if (!root)
        return;
    cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node *root)
{
    if (!root)
        return;
    inOrder(root->left);
    cout << root << " ";
    inOrder(root->right);
}

void postOrder(Node *root)
{
    if (!root)
        return;
    inOrder(root->left);
    inOrder(root->right);
    cout << root << " ";
}

void delTree(Node *root)
{
    if (!root)
        return;
    delTree(root->left);
    delTree(root->right);
    delete root;
}

int countFullNodes(Node *root)
{
    if (!root)
        return 0;
    int count = 0;
    if (root->left && root->right)
    {
        count = 1;
    }
    return count + countFullNodes(root->left) + countFullNodes(root->right);
}

int sumLeftLeaves(Node *root)
{
    if (!root)
        return 0;

    int sum = 0;
    if (root->left && !root->left->left && !root->left->right)
    {
        sum = root->left->value;
    }
    return sum + sumLeftLeaves(root->left) + sumLeftLeaves(root->right);
}

bool isBSTUtil(Node *root, int minVal, int maxVal)
{
    if (!root)
        return true;

    if (root->value <= minVal || root->value >= maxVal)
    {
        return false;
    }

    return isBSTUtil(root->left, minVal, root->value) &&
           isBSTUtil(root->right, root->value, maxVal);
}

bool is_bst(Node *root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

int countOddNodes(Node *root)
{
    if (!root)
        return 0;
    int flag = 0;
    if (root->value % 2 == 1)
        flag = 1;
    return countOddNodes(root->left) + countOddNodes(root->right) + flag;
}

int replaceWithSubtreeSum(Node *root)
{
    if (!root)
        return 0;
    int sum_left = replaceWithSubtreeSum(root->left);

    int sum_right = replaceWithSubtreeSum(root->right);
    int old = root->value;
    root->value = old + sum_left + sum_right;
    return root->value;
}
bool is_mirror(Node *right, Node *left)
{
    if (!right && !left)
        return true;
    if ((right == nullptr) + (left == nullptr) == 1)
        return false;
    if (right->value != left->value)
    {
        return false;
    }
    return is_mirror(left->left, right->right) && is_mirror(left->right, right->left);
}

bool is_symetric(Node *root)
{
    if (!root)
        return true;
    return is_mirror(root->right, root->left);
}

int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

int minHeight(Node* root){
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    if(!root->left) return 1+minHeight(root->right);
    if(!root->right) return 1+minHeight(root->left);
    return 1+min(minHeight(root->left),minHeight(root->right));
}


int depth(Node* root, int val, int currentDepth = 0) {
    if (!root) return -1;
    if (root->value == val) return currentDepth;
    
    int left = depth(root->left, val, currentDepth + 1);
    if (left != -1) return left;
    
    return depth(root->right, val, currentDepth + 1);
}