#include <gtest/gtest.h>
#include "avl_tree.hpp"
#include "tree_set.hpp"

    
TEST(AvlTree, Insert) {
    my_labs::Avl_tree<int> tree;
    EXPECT_TRUE(tree.insert(10));
    EXPECT_TRUE(tree.insert(20));
    EXPECT_FALSE(tree.insert(10)); // дубликат
    EXPECT_EQ(tree.size(), 2);
}

TEST(AvlTree, Balance) {
    my_labs::Avl_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_EQ(tree.height(), 2);
}

TEST(AvlTree, Contains) {
    my_labs::Avl_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    EXPECT_TRUE(tree.contains(10));
    EXPECT_FALSE(tree.contains(99));
}

TEST(AvlTree, Erase) {
    my_labs::Avl_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.erase(10);
    EXPECT_FALSE(tree.contains(10));
    EXPECT_EQ(tree.size(), 1);
}


TEST(AvlTree, Map) {
    my_labs::Avl_tree<int> tree;
    tree.insert(5);
    tree.insert(15);
    auto mapped = tree.map([](int x) { return x * 2; });
    EXPECT_TRUE(mapped.contains(10));
    EXPECT_TRUE(mapped.contains(30));
}

TEST(AvlTree, Where) {
    my_labs::Avl_tree<int> tree;
    tree.insert(5);
    tree.insert(15);
    auto filtered = tree.where([](int x) { return x > 10; });
    EXPECT_EQ(filtered.size(), 1);
    EXPECT_FALSE(filtered.contains(5));
}

TEST(AvlTree, Reduce) {
    my_labs::Avl_tree<int> tree;
    tree.insert(5);
    tree.insert(15);
    int sum = tree.reduce(0, [](int acc, int x) { return acc + x; });
    EXPECT_EQ(sum, 20);
}


TEST(TreeSet, InsertAndContains) {
    tree::tree_set<int> set;
    set.insert(1); set.insert(2);
    EXPECT_TRUE(set.contains(1));
    EXPECT_FALSE(set.contains(99));
    EXPECT_EQ(set.size(), 2);
}

TEST(TreeSet, Union) {
    tree::tree_set<int> A, B;
    A.insert(1); A.insert(2);
    B.insert(2); B.insert(3);
    auto U = A.Union(B);
    EXPECT_EQ(U.size(), 3);
    EXPECT_TRUE(U.contains(1));
    EXPECT_TRUE(U.contains(3));
}

TEST(TreeSet, Intersection) {
    tree::tree_set<int> A, B;
    A.insert(1); A.insert(2);
    B.insert(2); B.insert(3);
    auto I = A.Intersection(B);
    EXPECT_EQ(I.size(), 1);
    EXPECT_TRUE(I.contains(2));
}

TEST(TreeSet, Difference) {
    tree::tree_set<int> A, B;
    A.insert(1); A.insert(2);
    B.insert(2); B.insert(3);
    auto D = A.Difference(B);
    EXPECT_EQ(D.size(), 1);
    EXPECT_TRUE(D.contains(1));
    EXPECT_FALSE(D.contains(2));
}

TEST(TreeSet, IsSubsetOf) {
    tree::tree_set<int> A, B;
    A.insert(1); A.insert(2);
    B.insert(1); B.insert(2); B.insert(3);
    EXPECT_TRUE(A.IsSubsetOf(B));
    EXPECT_FALSE(B.IsSubsetOf(A));
}

TEST(TreeSet, Equals) {
    tree::tree_set<int> A, B;
    A.insert(1); A.insert(2);
    B.insert(1); B.insert(2);
    EXPECT_TRUE(A.equals(B));
}

TEST(TreeSet, Map) {
    tree::tree_set<int> set;
    set.insert(5);
    set.insert(15);
    auto mapped = set.map([](int x) { return x * 3; });
    EXPECT_TRUE(mapped.contains(15));
    EXPECT_TRUE(mapped.contains(45));
}

TEST(TreeSet, Where) {
    tree::tree_set<int> set;
    set.insert(5);
    set.insert(15);
    auto filtered = set.where([](int x) { return x > 10; });
    EXPECT_EQ(filtered.size(), 1);
    EXPECT_FALSE(filtered.contains(5));
}

TEST(TreeSet, Reduce) {
    tree::tree_set<int> set;
    set.insert(5);
    set.insert(15);
    int sum = set.reduce(0, [](int acc, int x) { return acc + x; });
    EXPECT_EQ(sum, 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}