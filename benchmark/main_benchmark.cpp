/**
    @file    main_benchmark.cpp
    @brief   Main file for Benchmark
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

/** < BinarySearchTree Class containing Iterator and Node and Benchmark Class containing Timer. */

#include "/home/pietro/Desktop/Github/BINARY-SEARCH-TREE/binary_search_tree/BinarySearchTree.h"
#include "/home/pietro/Desktop/Github/BINARY-SEARCH-TREE/benchmark/Benchmark.h"

/** Used Libraries. */
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>

/** < COMPILE: c++ -g -ggdb3 -Wall -Wextra -std=c++14 main_\benchmark.cpp */
/** < RUN: valgrind --leak-check=full --show-leak-kinds=all -v ./a.out */

int main()
{
        
    #define NODES 10 /** < Number of nodes to be created. */
    #define ITERATIONS 10 /** < Number of iterations for each operation. */

/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><> BENCHMARK find() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

    std::vector<int> m_ContainerStraight(NODES);
    std::iota(std::begin(m_ContainerStraight), std::end(m_ContainerStraight), 1);
    /** < for(int i = 0; i < NODES; i++) {std::cout << " " << m_ContainerStraight.at(i) << " \n";}; */

    /** < CREATE 2D ARRAY */
    double** m_Find = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_Find[i] = new double[NODES];}

    /** < FILL 2D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {m_Find[j][i] = 0;};
    };

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

/** < PRINT MATRIX of DATA */
#define PRINTER_MATRIX_FIND
#ifndef PRINTER_MATRIX_FIND
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_Find[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
#endif

    /** < CREATE 1D ARRAY */
    std::vector<double> m_FindTotal(NODES);
    
    /** < FILL 1D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {m_FindTotal.at(i) = 0;};

    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        m_FindTotal.at(i) += m_Find[j][i];
    };

/** < PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifndef PRINTER_MEAN_FIND
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << m_FindTotal[i] << std::endl;
    };
#endif

    /** < CREATE .csv FROM 2D ARRAY */
    std::ofstream out_F("FIND.csv");
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            out_F << std::fixed;
            out_F << std::setprecision(6) << m_Find[j][i] << ",";}
        out_F << "\n";
    };

    for (int i = 0; i < ITERATIONS; i++) {delete[] m_Find[i];}
    delete[] m_Find;

/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>< */
/** <><> BENCHMARK balance() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>< */

    /** < BSC: CREATE 2D ARRAY */
    double** m_BalancedBCS = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_BalancedBCS[i] = new double[NODES];}

    /** < BSC: FILL 2D ARRAY for with 0's */
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {m_BalancedBCS[j][i] = 0;};
    };

    /** < WSC: CREATE 2D ARRAY */
    double** m_BalancedWCS = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_BalancedWCS[i] = new double[NODES];}

    /** < WSC: FILL 2D ARRAY for with 0's */
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {m_BalancedWCS[j][i] = 0;};
    };

    /** < TEST balance() with iterations == ITERATIONS */
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
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_BalancedBCS[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
#endif

/** < WCS: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_BALANCEDWCS
#ifndef PRINTER_MATRIX_BALANCEDWCS
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_BalancedWCS[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
#endif

    /** < BCS: CREATE 1D ARRAY */
    std::vector<double> m_BalancedBCSTotal(NODES);
    
    /** < BCS: FILL 1D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {m_BalancedBCSTotal.at(i) = 0;};

    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        m_BalancedBCSTotal.at(i) += m_BalancedBCS[j][i];
    };

/** < PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifndef PRINTER_MEAN_FIND
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << m_BalancedBCSTotal[i] << std::endl;
    };
#endif

    /** < WCS: CREATE 1D ARRAY */
    std::vector<double> m_BalancedWCSTotal(NODES);
    
    /** < WCS: FILL 1D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {m_BalancedWCSTotal.at(i) = 0;};

    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        m_BalancedWCSTotal.at(i) += m_BalancedWCS[j][i];
    };

/** < WCS: PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifndef PRINTER_MEAN_FIND
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << m_BalancedWCSTotal[i] << std::endl;
    };
#endif

    /** < BCS: CREATE .csv FROM 2D ARRAY */
    std::ofstream out_BBCS("BALANCE_BCS.csv");
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            out_BBCS << std::fixed;
            out_BBCS << std::setprecision(6) << m_BalancedBCS[j][i] << ",";}
        out_BBCS << "\n";
    };

    /** < WCS: CREATE .csv FROM 2D ARRAY */
    std::ofstream out_WBCS("BALANCE_WCS.csv");
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            out_WBCS << std::fixed;
            out_WBCS << std::setprecision(6) << m_BalancedWCS[j][i] << ",";}
        out_WBCS << "\n";
    };

    for (int i = 0; i < ITERATIONS; i++) {delete[] m_BalancedBCS[i];}
    delete[] m_BalancedBCS;
    for (int i = 0; i < ITERATIONS; i++) {delete[] m_BalancedWCS[i];}
    delete[] m_BalancedWCS;

/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><> BENCHMARK insert() <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
/** <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> */

#define TESTER
#ifndef TESTER

    /** < ARRAYTEN: CREATE 2D ARRAY */
    double** m_Insert_TEN = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_Insert_TEN[i] = new double[NODES];}

    /** < ARRAYTEN: FILL 2D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {m_Insert_TEN[j][i] = 0;};
    };

    /** < ARRAYTEN: TEST find() with Iterations == ITERATIONS */
    BinarySearchTree<int, int*> insert_TEN_tree;
    for(int i = 0; i < NODES; i++)
    {   
        for(int j = 0; j < ITERATIONS; j++)
        {
            int* m_TEN = new int[10];
            Benchmark PROJECT(insert_TEN_tree, &BinarySearchTree<int, int*>::insert, std::pair<int, int*>(m_ContainerStraight.at(i), m_TEN));
            m_Find[j][i] = PROJECT.Duration();
            delete m_TEN;
        };
        int* m_TEN = new int[10];
        insert_TEN_tree.insert(std::pair<int, int*>(m_ContainerStraight.at(i), m_TEN));
        delete m_TEN;
    };

/** < ARRAYTEN: PRINT MATRIX of DATA */
#define PRINTER_MATRIX_FIND
#ifndef PRINTER_MATRIX_FIND
    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_Insert_TEN[j][i] << " ";
        }; 
        std::cout << std::endl; 
    };
#endif

    /** < ARRAYTEN: CREATE 1D ARRAY */
    std::vector<double> m_InsertTENTotal(NODES);
    
    /** < ARRAYTEN: FILL 1D ARRAY with 0's */
    for(int i = 0; i < NODES; i++)
    {m_InsertTENTotal.at(i) = 0;};

    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        m_InsertTENTotal.at(i) += m_Insert_TEN[j][i];
    };

/** < ARRAYTEN: PRINT MEAN of ITERATIONS */
#define PRINTER_MEAN_FIND
#ifndef PRINTER_MEAN_FIND
    for(int i = 0; i < NODES; i++)
    {
        std::cout << "Complexity: " << i + 1 << " has mean ";
        std::cout << std::fixed;   
        std::cout << std::setprecision(9) << m_InsertTENTotal[i] << std::endl;
    };
#endif

    /** < ARRAYTEN: CREATE .csv FROM 2D ARRAY */
    std::ofstream out_ITEN("FIND.csv");
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            out_ITEN << std::fixed;
            out_ITEN << std::setprecision(6) << m_Insert_TEN[j][i] << ",";}
        out_ITEN << "\n";
    };

    for (int i = 0; i < ITERATIONS; i++) {delete[] m_Insert_TEN[i];}
    delete[] m_Insert_TEN;

#endif


#define STOP
#ifndef STOP
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

#endif


    return 0;
}