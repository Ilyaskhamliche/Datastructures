// BTreeNode.h
#include <vector>

class BTreeNode {
public:
    int t;  // Minimum degree
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(int t, bool isLeaf);
    ~BTreeNode();
};

// BTreeNode.cpp
#include "BTreeNode.h"

BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    this->isLeaf = isLeaf;
    keys.assign(2 * t - 1, 0);
    children.assign(2 * t, nullptr);
}

BTreeNode::~BTreeNode() {
    for (auto child : children) {
        delete child;
    }
}

// BTree.h
#include "BTreeNode.h"

class BTree {
private:
    BTreeNode* root;
    int t;

    void insertNonFull(BTreeNode* node, int key);
    BTreeNode* splitChild(BTreeNode* node, int childIndex, int key);

public:
    BTree(int t);
    ~BTree();

    void insert(int key);
};

// BTree.cpp
#include "BTree.h"

BTree::BTree(int t) {
    this->t = t;
    root = nullptr;
}

BTree::~BTree() {
    delete root;
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = key;
    } else {
        BTreeNode* s = splitChild(root, 0, key);
        if (s != nullptr) {
            BTreeNode* newRoot = new BTreeNode(t, false);
            newRoot->children[0] = root;
            newRoot->keys[0] = s->keys[0];
            newRoot->children[1] = s;
            root = newRoot;
        }
    }
}

void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        BTreeNode* child = splitChild(node, i, key);
        if (child != nullptr) {
            for (int j = node->keys.size() - 1; j >= i + 1; j--) {
                node->keys[j] = node->keys[j - 1];
                node->children[j + 1] = node->children[j];
            }
            node->keys[i] = child->keys[0];
            node->children[i + 1] = child;
        }
    }
}

BTreeNode* BTree::splitChild(BTreeNode* node, int childIndex, int key) {
    BTreeNode* child = node->children[childIndex];
    if (child->isLeaf) {
        insertNonFull(child, key);
        return nullptr;
    }

    int mid = t - 1;
    BTreeNode* newChild = new BTreeNode(t, child->isLeaf);
    newChild->keys[0] = child->keys[mid];
    for (int j = mid + 1; j < 2 * t - 1; j++) {
        newChild->keys[j - mid] = child->keys[j];
        child->keys[j] = 0;
    }
    newChild->isLeaf = child->isLeaf;
    if (!child->isLeaf) {
        for (int j = 0; j < t; j++) {
            newChild->children[j] = child->children[mid + 1 + j];
            child->children[mid + 1 + j] = nullptr;
        }
    }
    insertNonFull(child, key);
    return newChild;
}
