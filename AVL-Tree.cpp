// AVLNode.h
class AVLNode {
public:
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int data);
};

// AVLNode.cpp
#include "AVLNode.h"

AVLNode::AVLNode(int data) {
    this->data = data;
    height = 1;
    left = nullptr;
    right = nullptr;
}

// AVLTree.h
#include "AVLNode.h"

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* node);
    AVLNode* leftRotate(AVLNode* node);
    AVLNode* insertNode(AVLNode* node, int key);

public:
    AVLTree();
    ~AVLTree();

    void insert(int key);
};

// AVLTree.cpp
#include "AVLTree.h"

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    // Implement destructor to free memory
}

void AVLTree::insert(int key) {
    root = insertNode(root, key);
}

AVLNode* AVLTree::insertNode(AVLNode* node, int key) {
    if (node == nullptr) {
        return new AVLNode(key);
    }

    if (key < node->data) {
        node->left = insertNode(node->left, key);
    } else if (key > node->data) {
        node->right = insertNode(node->right, key);
    } else {
        return node; // Duplicate key, do nothing
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left-Left case
    if (balance > 1 && key < node->left->data) {
        return rightRotate(node);
    }

    // Right-Right case
    if (balance < -1 && key > node->right->data) {
        return leftRotate(node);
    }

    // Left-Right case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int AVLTree::height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* temp = y->left;

    y->left = x;
    x->right = temp;
