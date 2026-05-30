// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(T value) {
            key = value;
            count = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insert(Node* node, T value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->key)
            node->left = insert(node->left, value);
        else if (value > node->key)
            node->right = insert(node->right, value);
        else
            node->count++;

        return node;
    }

    int search(Node* node, T value) const {
        if (node == nullptr)
            return 0;

        if (value == node->key)
            return node->count;

        if (value < node->key)
            return search(node->left, value);

        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (node == nullptr)
            return 0;

        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void clear(Node* node) {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    void collect(Node* node,
                 std::vector<std::pair<T, int> >& words) const {
        if (node == nullptr)
            return;

        collect(node->left, words);
        words.push_back(std::make_pair(node->key, node->count));
        collect(node->right, words);
    }

 public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    int search(T value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int> > getWords() const {
        std::vector<std::pair<T, int> > words;
        collect(root, words);
        return words;
    }
};

#endif  // INCLUDE_BST_H_
