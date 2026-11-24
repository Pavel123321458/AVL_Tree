#include "avl_tree.hpp"
#include "tree_set.hpp"
#include "TreePrinter.h"
#include <iostream>
#include <limits>

using namespace my_labs;

void print_menu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
    std::cout << "1. Добавить элемент в дерево\n";
    std::cout << "2. Удалить элемент из дерева\n";
    std::cout << "3. Проверить наличие элемента\n";
    std::cout << "4. Показать размер и высоту дерева\n";
    std::cout << "5. Вывести все элементы дерева\n";
    std::cout << "6. Демонстрация map (умножить все на 2)\n";
    std::cout << "7. Демонстрация where (оставить элементы > 10)\n";
    std::cout << "8. Демонстрация reduce (найти сумму)\n";
    std::cout << "9. Тест множеств (Union, Intersection, Difference)\n";
    std::cout << "10. Вывести структуру дерева\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";
}

int main() {
    Avl_tree<int> tree;
    int choice, value;

    while (true) {
        print_menu();
        if (!(std::cin >> choice)) break;
        switch (choice) {
        case 1:
            std::cout << "Введите целое число: ";
            std::cin >> value;
            if (tree.insert(value)) std::cout << "Добавлено.\n";
            else std::cout << "Элемент уже есть.\n";
            break;
        case 2:
            std::cout << "Введите целое число: ";
            std::cin >> value;
            if (tree.erase(value)) std::cout << "Удалено.\n";
            else std::cout << "Элемент не найден.\n";
            break;
        case 3:
            std::cout << "Введите целое число: ";
            std::cin >> value;
            std::cout << (tree.contains(value) ? "Элемент есть.\n" : "Элемента нет.\n");
            break;
        case 4:
            std::cout << "Размер: " << tree.size()
                      << ", Высота: " << tree.height() << "\n";
            break;
        case 5:
            std::cout << "Элементы: ";
            tree.for_each([](int x) { std::cout << x << " "; });
            std::cout << "\n";
            break;
        case 6:
            tree = tree.map([](int x) { return x * 2; });
            std::cout << "Все элементы умножены на 2.\n";
            break;
        case 7:
            tree = tree.where([](int x) { return x > 10; });
            std::cout << "Оставлены элементы > 10.\n";
            break;
        case 8: {
            int sum = tree.reduce(0, [](int acc, int x) { return acc + x; });
            std::cout << "Сумма элементов: " << sum << "\n";
            break;
        }
        case 9: {
            tree::tree_set<int> A, B;
            A.insert(1); A.insert(2); A.insert(3);
            B.insert(3); B.insert(4); B.insert(5);
            std::cout << "Множество A: 1 2 3\n";
            std::cout << "Множество B: 3 4 5\n";
            auto U = A.Union(B);
            std::cout << "Объединение (A U B): ";
            U.for_each([](int x) { std::cout << x << " "; });
            std::cout << "\n";
            auto I = A.Intersection(B);
            std::cout << "Пересечение (A n B): ";
            I.for_each([](int x) { std::cout << x << " "; });
            std::cout << "\n";
            auto D = A.Difference(B);
            std::cout << "Разность (A - B): ";
            D.for_each([](int x) { std::cout << x << " "; });
            std::cout << "\n";
            std::cout << "A является подмножеством B? " << (A.IsSubsetOf(B) ? "Да" : "Нет") << "\n";
            break;
        }
        case 10:
            TreePrinter<int>::print(tree);
            break;
        case 0:
            std::cout << "Выход...\n";
            return 0;
        default:
            std::cout << "Неверный ввод.\n";
        }
    }
    return 0;
}
