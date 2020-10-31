#include "Benchmark.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <cstdint>
#include <math.h>
#include <iomanip>

int main()
{
        
    #define NODES 100
    #define ITERATIONS 10 

    std::vector<float> m_Container(NODES);
    std::iota(std::begin(m_Container), std::end(m_Container), 1);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::shuffle(begin(m_Container), end(m_Container), mersenne_engine);

    double** m_DataContainer = new double*[ITERATIONS];
    for(int i = 0; i < ITERATIONS; ++i)
    {m_DataContainer[i] = new double[NODES];}

    BinarySearchTree<int, int> benchmarktree;
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < ITERATIONS; j++)
        {
            Benchmark PROJECT(benchmarktree, &BinarySearchTree<int, int>::insert, std::pair<int, int>(m_Container.at(i), 1));
            m_DataContainer[j][i] = PROJECT.Duration();
        }
        
        benchmarktree.insert(std::pair<int, int>(m_Container.at(i), 1));
    };
    std::cout << "\nTree: \n" << benchmarktree;

    for(int i = 0; i < NODES; i++) 
    { 
        for (int j = 0; j < ITERATIONS; j++) 
        {
            std::cout << std::fixed;   
            std::cout << std::setprecision(9) << m_DataContainer[j][i] << " ";}; 
      
        std::cout << std::endl; 
    };

    for (int i = 0; i < ITERATIONS; i++) {delete[] m_DataContainer[i];}
    delete[] m_DataContainer;
