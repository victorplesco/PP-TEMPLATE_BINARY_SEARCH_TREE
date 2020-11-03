# ADVANCED PROGRAMMING PROJECT: BINARY SEARCH TREE
A joint effort of [Thomas Deponte](https://github.com/freakontrol), [Victor Aleksandrovic Plesco](https://github.com/victorplesco) and [Pietro Morichetti](https://github.com/wilsonjefferson).

## STRUCTURE OF THE GIT FOLDER
- Folder `binary_search_tree` - contains the BST files: `BinarySeachTree.h` for the class BinarySeachTree, `Iterator.h` for the class Iterator, `Node.h` for the class Node, `functions.BinarySeachTree.inl` and `support.BinarySearchTree.inl` for the inline files of BST.
- Folder `benchmark` - contains the `Benchmark.h` header file with the associated `main source` file to test the BST, and an additional subfolder `data` where you find: csv files, `plots` R used to build plots. 
- File `MakeFile` - is a simple makefile to properly compile the BST and benchmark files.
- File `main.cpp` - is the souce file to play with the Binary Search Tree.
- File `script.sh` - is the Bash file through which you compile and run the source files. Run: ./script.sh main_test standard | valgrind (for memory leaks). 
- File `report.pdf` - is the documentation of the entire project, in which you find a short explanation for each class, the functions and benchmark results.
