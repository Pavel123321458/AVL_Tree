
#pragma once

#include <iostream>
#include "UnqPtr.h"
#include <algorithm>
#include <cstddef>
#include <utility>

namespace my_labs {

template <typename T>
struct TreePrinter;

template <typename T>
class Avl_tree {
private:
    friend struct TreePrinter<T>;

    struct Node {
        T value;
        UnqPtr<Node> left;
        UnqPtr<Node> right;
        int height;
        Node(const T& val) : value(val), height(1) {}
    };

    UnqPtr<Node> root;
    size_t tree_size = 0;

    int getHeight(const UnqPtr<Node>& node) const {
        if (!node.get()) return 0;
        return node->height;
    }

    void updateHeight(Node* node) {
        if (!node) return;
        int leftH = getHeight(node->left);
        int rightH = getHeight(node->right);
        node->height = 1 + std::max(leftH, rightH);
    }

    int getBalance(Node* node) {
        if (!node) return 0;
        return getHeight(node->right) - getHeight(node->left);
    }

    void rotateLeft(UnqPtr<Node>& node) {
        UnqPtr<Node> newRoot = std::move(node->right);
        node->right = std::move(newRoot->left);
        newRoot->left = std::move(node);
        updateHeight(newRoot->left.get());
        updateHeight(newRoot.get());
        node = std::move(newRoot);
    }

    void rotateRight(UnqPtr<Node>& node) {
        UnqPtr<Node> newRoot = std::move(node->left);
        node->left = std::move(newRoot->right);
        newRoot->right = std::move(node);
        updateHeight(newRoot->right.get());
        updateHeight(newRoot.get());
        node = std::move(newRoot);
    }

    void balance(UnqPtr<Node>& node) {
        if (!node.get()) return;
        updateHeight(node.get());
        int bal = getBalance(node.get());

        if (bal > 1) {
            if (getBalance(node->right.get()) < 0) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        } else if (bal < -1) {
            if (getBalance(node->left.get()) > 0) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
    }

    bool insert_node(UnqPtr<Node>& node, const T& value) {
        if (!node.get()) {
            node = UnqPtr<Node>(new Node(value));
            tree_size++;
            return true;
        }

        bool added = false;

        if (value < node->value) {
            added = insert_node(node->left, value);
        } else if (value > node->value) {
            added = insert_node(node->right, value);
        } else {
            return false;
        }

        if (added) {
            balance(node);
        }

        return added;
    }

    void print_in_order(Node* node) const {
        if (!node) return;
        print_in_order(node->left.get());
        std::cout << node->value << " ";
        print_in_order(node->right.get());
    }

    bool contains_node(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->value) return true;

        if (value < node->value)
            return contains_node(node->left.get(), value);

        return contains_node(node->right.get(), value);
    }

    bool erase_node(UnqPtr<Node>& node, const T& value) {
        if (!node.get()) return false;
        bool removed = false;

        if (value > node->value) {
            removed = erase_node(node->right, value);
        } else if (value < node->value) {
            removed = erase_node(node->left, value);
        } else {
            removed = true;

            if (!node->left.get()) {
                UnqPtr<Node> child = std::move(node->right);
                node = std::move(child);
            } else if (!node->right.get()) {
                UnqPtr<Node> child = std::move(node->left);
                node = std::move(child);
            } else {
                Node* minNode = node->right.get();

                while (minNode->left.get()) {
                    minNode = minNode->left.get();
                }

                T minValue = minNode->value;
                node->value = minValue;
                erase_node(node->right, minValue);
            }
        }

        if (removed && node.get()) {
            balance(node);
        }

        return removed;
    }

    template <typename Func>
    void for_each_node(Node* node, Func& action) const {
        if (!node) return;
        for_each_node(node->left.get(), action);
        action(node->value);
        for_each_node(node->right.get(), action);
    }

public:
    Avl_tree() = default;

    size_t size() const {
        return tree_size;
    }

    bool empty() const {
        return tree_size == 0;
    }

    int height() const {
        return getHeight(root);
    }

    bool insert(const T& value) {
        return insert_node(root, value);
    }

    void print() const {
        print_in_order(root.get());
        std::cout << std::endl;
    }

    bool contains(const T& value) const {
        return contains_node(root.get(), value);
    }

    bool erase(const T& value) {
        if (!erase_node(root, value)) return false;
        --tree_size;
        return true;
    }

    template <typename Func>
    void for_each(Func action) const {
        for_each_node(root.get(), action);
    }

    template <typename Func>
    Avl_tree map(Func transform) const {
        Avl_tree result;

        for_each([&result, &transform](const T& val) {
            result.insert(transform(val));
        });

        return result;
    }

    template <typename Predicate>
    Avl_tree where(Predicate predicate) const {
        Avl_tree result;

        for_each([&result, &predicate](const T& val) {
            if (predicate(val)) {
                result.insert(val);
            }
        });

        return result;
    }

    template <typename Accumulator, typename Func>
    Accumulator reduce(Accumulator initial, Func combine) const {
        Accumulator result = initial;

        for_each([&result, &combine](const T& val) {
            result = combine(result, val);
        });

        return result;
    }
};

}
