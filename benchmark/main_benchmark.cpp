/**
    @file    main_benchmark.cpp
    @brief   Main file for Benchmark
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

/** < BinarySearchTree Class containing Iterator and Node and Benchmark Class containing Timer. */
#include "/home/vrpo/BINARY-SEARCH-TREE/binary_search_tree/BinarySearchTree.h"
#include "/home/vrpo/BINARY-SEARCH-TREE/benchmark/Benchmark.h"

/** Used Libraries. */
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <string>
#include <array>

/** < COMPILE: c++ -g -ggdb3 -Wall -Wextra -std=c++14 main.cpp */
/** < RUN: valgrind --leak-check=full --show-leak-kinds=all -v ./a.out */

int main()
{
        
    #define NODES 1000 /** < Number of nodes to be created. */
    #define ITERATIONS 100 /** < Number of iterations for each operation. */

/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><> BENCHMARK find() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

    std::vector<int> m_ContainerStraight(NODES);
    std::iota(std::begin(m_ContainerStraight), std::end(m_ContainerStraight), 1);
    /* for(int i = 0; i < NODES; i++) {std::cout << " " << m_ContainerStraight.at(i) << " \n";}; */

    /** < CREATE 2D ARRAY */
    double** m_DataFind = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_DataFind[i] = new double[NODES];}

    /** < TEST find() with Iteratrions == ITERATIONS */
    BinarySearchTree<int, int> find_tree;
    for(int i = 0; i < NODES; i++)
    {   
        find_tree.insert(std::pair<int, int>(m_ContainerStraight.at(i), 1));
        for(int j = 0; j < ITERATIONS; j++)
        {
            Benchmark PROJECT(find_tree, &BinarySearchTree<int, int>::find, m_ContainerStraight.at(i));
            m_DataFind[j][i] = PROJECT.Duration();
        };
    };

/** < PRINT MATRIX of DATA */
#define PRINTER_MATRIX_FIND
#ifndef PRINTER_MATRIX_FIND
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_DataFind[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
#endif

/** < PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifdef PRINTER_MEAN_FIND
    float m_FindTotal[NODES]; 
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        m_FindTotal[i] += m_DataFind[j][i];
    };
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << m_FindTotal[i]/ITERATIONS << std::endl;
    };
#endif

std::ofstream out("BENCHMARK_FIND.csv");
for (auto& row : m_DataFind) {
  for (auto col : row)
    out << col <<',';
  out << '\n';
};

    /** < Fill a vector with 1:NODES integers and shuffle them randomly. */ 
    std::vector<int> m_ContainerShuffled(NODES);
    std::iota(std::begin(m_ContainerShuffled), std::end(m_ContainerShuffled), 1);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::shuffle(begin(m_ContainerShuffled), end(m_ContainerShuffled), mersenne_engine);


    double** m_DataContainer = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_DataContainer[i] = new double[NODES];}

    BinarySearchTree<int, int> benchmarktree;
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            Benchmark PROJECT(benchmarktree, &BinarySearchTree<int, int>::insert, std::pair<int, int>(m_ContainerShuffled.at(i), 1));
            m_DataContainer[j][i] = PROJECT.Duration();
        }
        
        benchmarktree.insert(std::pair<int, int>(m_ContainerShuffled.at(i), 1));
    };
/*
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_DataContainer[j][i] << " ";}; 
      
        std::cout << std::endl; 
    };
*/
    for (int i = 0; i < ITERATIONS; i++) {delete[] m_DataContainer[i];}
    delete[] m_DataContainer;

    return 0;
}