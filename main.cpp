#include <iostream>
#include "BinarySearchTree.h"

// compile with -Wall -Wextra -g, run with valgrind --leak-check = yes -v ./a.out.

int main()
{
    BinarySearchTree<int, int> tree;
    tree.insert(std::pair<int, int>(20, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(10, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>( 9, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(11, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(30, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(25, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(26, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(24, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(35, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(36, 1)).second;
        std::cout << "\n";
    tree.insert(std::pair<int, int>(34, 1)).second;
        std::cout << "\n\n\n";

    tree.find(34);
    tree.end();
    tree.cend();
    tree.begin();
    tree.cbegin();
    tree.balance();
    tree.clear();

    return 0;
};