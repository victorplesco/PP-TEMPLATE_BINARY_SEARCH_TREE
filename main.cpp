#include <iostream>

#include "Node.h"
#include "Iterator.h"
#include "BinarySearchTree.h"

void PrintOutput(bool EXISTING_CHILD)
{
    if(EXISTING_CHILD) {std::cout << "\nTRUE: NODE CREATED!\n";}
    else{std::cout << "\nFALSE: EXIT.\n";}
};

int main()
{
    
    BinarySearchTree<int, int> tree;

    bool tmp;
    
    tmp = tree.insert(std::pair<int, int>(1, 1)).second;
    PrintOutput(tmp);

    tmp = tree.insert(std::pair<int, int>(10, 1)).second;
    PrintOutput(tmp);

    tmp = tree.insert(std::pair<int, int>(10, 1)).second;
    PrintOutput(tmp);

    tmp = tree.insert(std::pair<int, int>(9, 1)).second;
    PrintOutput(tmp);
    
    tmp = tree.insert(std::pair<int, int>(8, 1)).second;
    PrintOutput(tmp);


    tree.find(8);

    return 0;
};