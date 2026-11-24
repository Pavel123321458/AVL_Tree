#pragma once

#include <iostream>
#include <string>

namespace my_labs {

template <typename T>
class Avl_tree;

template <typename T>
struct TreePrinter {
private:
    using Node = typename Avl_tree<T>::Node;

    static void printNode(const Node* node, std::ostream& out,
                          const std::string& prefix, bool last) {
        if (!node) return;
        out << prefix << (last ? "└── " : "├── ")
            << node->value << '\n';
        printChildren(node, out, prefix + (last ? "    " : "│   "));
    }

    static void printChildren(const Node* node, std::ostream& out,
                              const std::string& prefix) {
        const Node* left = node->left.get();
        const Node* right = node->right.get();
        if (left) printNode(left, out, prefix, !right);
        if (right) printNode(right, out, prefix, true);
    }

public:
    static void print(const Avl_tree<T>& tree,
                      std::ostream& out = std::cout) {
        const Node* root = tree.root.get();
        if (!root) {
            out << "(empty tree)\n";
            return;
        }
        out << root->value << '\n';
        printChildren(root, out, "");
    }
};

}
