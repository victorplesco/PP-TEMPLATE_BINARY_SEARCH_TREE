#include <iostream>
#include "BinarySearchTree.h"

// compile with -Wall -Wextra -g, run with valgrind --leak-check = yes -v ./a.out.

int main()
{
    
    BinarySearchTree<int, int> nulltree;   
    nulltree.find(1);
    nulltree.erase(1);
    nulltree.end();
    nulltree.cend();
    nulltree.begin();
    nulltree.cbegin();
    nulltree.balance();
    nulltree.clear(); 


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
    tree.erase(34);
    tree.end();
    tree.cend();
    tree.begin();
    tree.cbegin();
    tree.balance();
    tree.erase(20);
    tree.erase(9);
    std::cout << tree << std::endl;

    BinarySearchTree<int, int> copiedtree{tree};
    std::cout << copiedtree << std::endl;

    std::cout << tree << std::endl;

    tree.clear(); 

    return 0;
};