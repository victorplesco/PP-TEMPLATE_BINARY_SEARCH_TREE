/**
    @file    main_benchmark.cpp
    @brief   Main file for Benchmark
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

/** < BinarySearchTree Class containing Iterator and Node and Benchmark Class containing Timer. */
#include "../binary_search_tree/BinarySearchTree.h"
#include "./Benchmark.h"

/** Used Libraries. */
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <array>
#include <string>

/** < COMPILE: c++ -g -ggdb3 -Wall -Wextra -std=c++14 main_benchmark.cpp */
/** < RUN: valgrind --leak-check=full --show-leak-kinds=all -v ./a.out */

#define NODES 100 /** < Number of nodes to be created. */
#define ITERATIONS 10 /** < Number of iterations for each operation. */

/**
 * createArray
 * 
 * @brief Allocates a 2D array on the heap and fills it with 0's.
*/
double** createArray()
{
    /** < CREATE 2D ARRAY */
    double** x = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i) {x[i] = new double[NODES];};

    /** < FILL 2D ARRAY with 0's */
    for(int i = 0; i < NODES; i++) {for(int j = 0; j < ITERATIONS; j++) {x[j][i] = 0;};};

    return x;
};

/**
 * printMatrix
 * 
 * @brief Prints the 2D array.
*/
void printMatrix(double** x)
{
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << x[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
};

/**
 * printITRMean
 * 
 * @brief Calculates the means over the iterations on a certain level of complexity and prints them. 
*/
void printITRMean(double** x)
{
    /** < CREATE 1D ARRAY */
    std::vector<double> v(NODES);
    
    /** < FILL 1D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {v.at(i) = 0;};

    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        v.at(i) += x[j][i];
    };
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << v[i] << std::endl;
    };
};

/**
 * createCSV
 * 
 * @brief Outputs a .csv file with times for iterations on columns and complexity on rows.
*/
void createCSV(double** x, std::string name)
{
    std::ofstream out(name);
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            out << std::fixed;
            out << std::setprecision(6) << x[j][i] << ",";}
        out << "\n";
    };
};

/**
 * deallocMatrix
 * 
 * @brief Deallocates the 2D array from the heap.
*/
void deallocMatrix(double** x)
{
    for (int i = 0; i < ITERATIONS; i++) {delete[] x[i];}
    delete[] x;
};

int main()
{

    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><> SHARED RESOURCES <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

    std::vector<int> m_ContainerStraight(NODES);
    std::iota(std::begin(m_ContainerStraight), std::end(m_ContainerStraight), 1);
    /** < for(int i = 0; i < NODES; i++) {std::cout << " " << m_ContainerStraight.at(i) << " \n";}; */

    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><> BENCHMARK find() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

    /** < FIND: CREATE 2D ARRAY */
    double** m_Find = createArray();

    /** < TEST find() with Iterations == ITERATIONS */
    BinarySearchTree<int, int> find_tree;
    for(int i = 0; i < NODES; i++)
    {   
        find_tree.insert(std::pair<int, int>(m_ContainerStraight.at(i), 1));
        for(int j = 0; j < ITERATIONS; j++)
        {
            Benchmark PROJECT(find_tree, &BinarySearchTree<int, int>::find, m_ContainerStraight.at(i));
            m_Find[j][i] = PROJECT.Duration();
        };
    };

/** < FIND: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_FIND
#ifndef PRINTER_MATRIX_FIND
printMatrix(m_Find);
#endif

/** < FIND: PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifndef PRINTER_MEAN_FIND
printITRMean(m_Find);
#endif

    /** < FIND: CREATE .csv FROM 2D ARRAY */
    createCSV(m_Find, "FIND.csv");

    /** < FIND: FREE MATRIX FROM HEAP. */
    deallocMatrix(m_Find);

    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>< */
    /** <><> BENCHMARK balance() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>< */

    /** < BSC: CREATE 2D ARRAY */
    double** m_BalancedBCS = createArray();

    /** < WSC: CREATE 2D ARRAY */
    double** m_BalancedWCS = createArray();

    /** < TEST balance() BCS and WCS with iterations == ITERATIONS */
    BinarySearchTree<int, int> balanced_list_tree;
    BinarySearchTree<int, int> balanced_balanced_tree;
    for(int i = 0; i < NODES; i++)
    {   
        balanced_list_tree.insert(std::pair<int, int>(m_ContainerStraight.at(i), 1));
        balanced_balanced_tree.insert(std::pair<int, int>(m_ContainerStraight.at(i), 1));
        for(int j = 0; j < ITERATIONS; j++)
        {
            {
                Benchmark PROJECT(balanced_list_tree, &BinarySearchTree<int, int>::balance);
                m_BalancedBCS[j][i] = PROJECT.Duration();
            };

            balanced_balanced_tree.balance();

            {
                Benchmark PROJECT(balanced_balanced_tree, &BinarySearchTree<int, int>::balance);
                m_BalancedWCS[j][i] = PROJECT.Duration();
            };
        };
    };

/** < BCS: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_BALANCEDBCS
#ifndef PRINTER_MATRIX_BALANCEDBCS
printMatrix(m_BalancedBCS);
#endif

/** < WCS: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_BALANCEDWCS
#ifndef PRINTER_MATRIX_BALANCEDWCS
printMatrix(m_BalancedWCS);
#endif

/** < BCS: PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_BALANCEDBCS
#ifndef PRINTER_MEAN_BALANCEDBCS
printITRMean(m_BalancedBCS);
#endif

/** < WCS: PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_BALANCEDWCS
#ifndef PRINTER_MEAN_BALANCEDWCS
printITRMean(m_BalancedWCS);
#endif

    /** < BCS: CREATE .csv FROM 2D ARRAY */
    createCSV(m_BalancedBCS, "BALANCE_BCS.csv");

    /** < BCS: FREE MATRIX FROM HEAP. */
    deallocMatrix(m_BalancedBCS);

    /** < WCS: CREATE .csv FROM 2D ARRAY */
    createCSV(m_BalancedWCS, "BALANCE_WCS.csv");

    /** < WCS: FREE MATRIX FROM HEAP. */
    deallocMatrix(m_BalancedWCS);

    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><> BENCHMARK insert() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
    /** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

    /** < TEN: CREATE 2D ARRAY */
    double** m_Insert10 = createArray();

    /** < THOUSAND: CREATE 2D ARRAY */
    double** m_Insert1000 = createArray();

    std::array<int, 10>   m__TEN;
    std::array<int, 1000> m__THOUSAND;

    /** < TEST insert() with Iterations == ITERATIONS */
    BinarySearchTree<int, std::array<int, 10>> insert_10_tree;
    BinarySearchTree<int, std::array<int, 1000>> insert_1000_tree;
    for(int i = 0; i < NODES; i++)
    {   
        for(int j = 0; j < ITERATIONS; j++)
        {
            {
                std::array<int, 10> m_TEN;
                Benchmark PROJECT(insert_10_tree, &BinarySearchTree<int, std::array<int, 10>>::insert, std::pair<int, std::array<int, 10>>(m_ContainerStraight.at(i), m_TEN));
                m_Insert10[j][i] = PROJECT.Duration();
            };

            {
                std::array<int, 1000> m_HUNDRED;
                Benchmark PROJECT(insert_1000_tree, &BinarySearchTree<int, std::array<int, 1000>>::insert, std::pair<int, std::array<int, 1000>>(m_ContainerStraight.at(i), m_HUNDRED));
                m_Insert1000[j][i] = PROJECT.Duration();
            };
        };
        insert_10_tree.insert(std::pair<int, std::array<int, 10>>(m_ContainerStraight.at(i), m__TEN));
        insert_1000_tree.insert(std::pair<int, std::array<int, 1000>>(m_ContainerStraight.at(i), m__THOUSAND));
    };

/** < TEN: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_TEN
#ifndef PRINTER_MATRIX_TEN
printMatrix(m_Insert10);
#endif

/** < THOUSAND: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_THOUSAND
#ifndef PRINTER_MATRIX_THOUSAND
printMatrix(m_Insert1000);
#endif

/** < TEN: PRINT MEAN of ITERATIONS */
#define PRINTER_MATRIX_TEN
#ifndef PRINTER_MATRIX_TEN
printITRMean(m_Insert10);
#endif

/** < THOUSAND: PRINT MEAN of ITERATIONS */
#define PRINTER_MATRIX_THOUSAND
#ifndef PRINTER_MATRIX_THOUSAND
printITRMean(m_Insert1000);
#endif

    /** < TEN: CREATE .csv FROM 2D ARRAY */
    createCSV(m_Insert10, "INSERT_10.csv");

    /** < TEN: FREE MATRIX FROM HEAP. */
    deallocMatrix(m_Insert10);

    /** < THOUSAND: CREATE .csv FROM 2D ARRAY */
    createCSV(m_Insert1000, "INSERT_1000.csv");

    /** < THOUSAND: FREE MATRIX FROM HEAP. */
    deallocMatrix(m_Insert1000);

    return 0;
};