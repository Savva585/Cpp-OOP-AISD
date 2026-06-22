#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <queue>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;          
        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    void updateHeight(Node* node) {
        if (node)
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balanceNode(Node* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int bf = getBalanceFactor(node);
        if (bf > 1) {
            if (getBalanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left); 
            return rotateRight(node);               
        }
        if (bf < -1) {
            if (getBalanceFactor(node->right) > 0)
                node->right = rotateRight(node->right); 
            return rotateLeft(node);                   
        }
        return node;
    }

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; 

        return balanceNode(node);
    }

    Node* findMin(Node* node) const {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return balanceNode(node);
    }

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    void inorder(const Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(const Node* node) const {
        if (node) {
            std::cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(const Node* node) const {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            std::cout << node->data << " ";
        }
    }

    void levelOrder(const Node* node) const {
        if (!node) return;
        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            std::cout << cur->data << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        newNode->height = node->height;
        return newNode;
    }

    int getHeightAndCheck(Node* node) const {
        if (!node) return 0;
        int leftH = getHeightAndCheck(node->left);
        int rightH = getHeightAndCheck(node->right);
        if (leftH == -1 || rightH == -1) return -1;
        if (std::abs(leftH - rightH) > 1) return -1;
        return 1 + std::max(leftH, rightH);
    }

    
public:
    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& other) : root(copy(other.root)) {}

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clear(root);
            root = copy(other.root);
        }
        return *this;
    }

    ~AVLTree() {
        clear(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    bool contains(const T& value) const {
        return search(root, value);
    }

    void printInorder() const {
        inorder(root);
        std::cout << std::endl;
    }

    void printPreorder() const {
        preorder(root);
        std::cout << std::endl;
    }

    void printPostorder() const {
        postorder(root);
        std::cout << std::endl;
    }

    void printLevelOrder() const {
        levelOrder(root);
        std::cout << std::endl;
    }

    int size() const {
        auto count = [](Node* node, auto&& self) -> int {
            if (!node) return 0;
            return 1 + self(node->left, self) + self(node->right, self);
        };
        return count(root, count);
    }


    int height() const {
        return getHeight(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    bool isBalanced() const {
        return getHeightAndCheck(root) != -1;
    }

};

#endif 