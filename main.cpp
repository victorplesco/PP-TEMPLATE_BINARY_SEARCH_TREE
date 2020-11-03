/**
    @file    main.cpp
    @brief   Main file for BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

/** < BinarySearchTree Class containing Iterator and Node. */
#include "./binary_search_tree/BinarySearchTree.h"

/** Used Libraries. */
#include <iostream>

/** < COMPILE: c++ -g -ggdb3 -Wall -Wextra -std=c++14 main.cpp */
/** < RUN: valgrind --leak-check=full --show-leak-kinds=all -v ./a.out */

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
        std::cout << "\n < < < < END OF TESTING NULL TREE > > > > \n";

#define CHECKERS_ON 0
    BinarySearchTree<int, int> tree;
    tree.insert(std::pair<int, int>(20, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.insert(std::pair<int, int>(10, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.insert(std::pair<int, int>( 9, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.insert(std::pair<int, int>(11, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.insert(std::pair<int, int>(30, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.insert(std::pair<int, int>(25, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    
    tree.emplace(std::pair<int, int>(26, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.emplace(std::pair<int, int>(24, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.emplace(std::pair<int, int>(35, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.emplace(std::pair<int, int>(36, 1)); {if(CHECKERS_ON) std::cout << "\n";}
    tree.emplace(std::pair<int, int>(34, 1)); {if(CHECKERS_ON) std::cout << "\n";}
        std::cout << " < < < < END OF INSERT and EMPLACE > > > > \n";
    
    tree.find(20);
    tree.find(36);
    tree.find(9);
    tree.erase(20);
    tree.erase(36);
    tree.erase(9);
    tree.end();
    tree.cend();
    tree.begin();
    tree.cbegin();
    tree.balance();
        std::cout << "\n < < < < PRINTING FILLED TREE:\n\n" << tree << "\nEND OF TESTING FILLED TREE > > > > \n";

    BinarySearchTree<int, int> deepcopiedtree{tree};
        std::cout << "\n < < < < PRINTING DEEP COPIED TREE from FILLED TREE:\n\n" << deepcopiedtree;
        std::cout << "\nEND OF TESTING DEEP COPIED TREE > > > > \n";

    BinarySearchTree<int, int> movedtree{std::move(deepcopiedtree)};
        std::cout << "\n < < < < PRINTING MOVED TREE from DEEP COPIED TREE:\n\n" << movedtree;
        std::cout << "\nEND OF TESTING DEEP COPIED TREE > > > > \n";

    BinarySearchTree<int, int> emptiedtree{deepcopiedtree};
        std::cout << "\n < < < < PRINTING EMPTIED TREE from DEEP COPIED TREE (EMPTIED by MOVED TREE):\n\n" << emptiedtree;
        std::cout << "\nEND OF TESTING EMPTIED TREE > > > > \n";

        std::cout << "\n < < < < CLEARING ALL TREES > > > > \n";
    tree.clear();
    deepcopiedtree.clear();
    movedtree.clear();
    emptiedtree.clear();
        std::cout << "\n < < < < END > > > > \n";

    return 0;
};