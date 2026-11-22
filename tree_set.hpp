#pragma once
#include "avl_tree.hpp"
using my_labs::Avl_tree;

namespace tree{

template <typename T>
class tree_set{
private:
    Avl_tree<T> tree;
public:
    bool insert(const T& value){
        return tree.insert(value);
    }

    size_t size() const { return tree.size(); }
    bool empty() const { return tree.empty(); }
    bool contains(const T& value) const { return tree.contains(value); }
    bool erase(const T& value) { return tree.erase(value); }


    template <typename Func>
    void for_each(Func action) const {
        tree.for_each(action);
    }

    tree_set Union(const tree_set& other) const {
        tree_set result;
        tree.for_each([&result](const T& val) { result.insert(val); });
        other.for_each([&result](const T& val) { result.insert(val); });
        return result;
    }

    tree_set Intersection(const tree_set& other) const {
        tree_set result;
        
        tree.for_each([&result, &other](const T& val) {
            if (other.contains(val)) {
                result.insert(val);
            }
        });
        return result;
    }

    tree_set Difference(const tree_set& other) const {
        tree_set result;
        
        tree.for_each([&result, &other](const T& val) {
            if (!other.contains(val)) {
                result.insert(val);
            }
        });
        
        return result;
    }

    bool equals(const tree_set& other) const {
        if (this->size() == other.size()){
            bool equal = true;
            tree.for_each([&equal, &other](const T& val){
                if (!other.contains(val)){
                    equal = false;
                }
            });
            return equal;
        }
        return false;
    }

    bool IsSubsetOf(const tree_set& other) const {
        bool is_subset = true;
        
        tree.for_each([&is_subset, &other](const T& val) {
            if (!other.contains(val)) {
                is_subset = false;
            }
        });
        
        return is_subset;
    }

    template <typename Func>
    tree_set map(Func transform) const {
        tree_set result;
        result.tree = tree.map(transform);
        return result;
    }

    template <typename Predicate>
    tree_set where(Predicate predicate) const {
        tree_set result;
        result.tree = tree.where(predicate);
        return result;
    }

    template <typename Accumulator, typename Func>
    Accumulator reduce(Accumulator initial, Func combine) const {
        return tree.reduce(initial, combine);
    }
};

}