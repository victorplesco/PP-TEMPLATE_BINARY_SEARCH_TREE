/**
    @file    Benchmark.h
    @brief   Header for class Benchmark
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

#ifndef _BENCHMARK_h
#define _BENCHMARK_h

/** < BinarySearchTree CHECKER */
#define _BENCHMARK_CHECK_CONSTRUCTORS_ 0

/** < Used Libraries */
#include <iostream>
#include <chrono>
#include <memory>

class Timer
{

    using chrono_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

    /* ####################################################################################################################################################################### */
    /* ## Timing ############################################################################################################################################################# */
    /* ####################################################################################################################################################################### */


    private:

        chrono_t* m_EndPoint;

    public:

        Timer(chrono_t* StartPoint, chrono_t* EndPoint) : m_EndPoint{EndPoint}
        {*StartPoint = std::chrono::high_resolution_clock::now();};

       ~Timer()
        {*m_EndPoint = std::chrono::high_resolution_clock::now();};
};

class Benchmark
{

    using chrono_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

    /* ####################################################################################################################################################################### */
    /* ## Caller ############################################################################################################################################################# */
    /* ####################################################################################################################################################################### */


    private:

        chrono_t* m_StartPoint = new chrono_t;
        chrono_t* m_EndPoint   = new chrono_t; 

    public:

        Benchmark() noexcept {std::cout << "\nBenchmark: default ctor\n";};
       
       ~Benchmark() noexcept 
        {
           delete m_StartPoint, delete m_EndPoint;
           if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: destructor\n";
        };

        template<class Class, typename Return, typename... Args, typename... ArgsBis>
        Benchmark(Class classcp, Return (Class::*funcptr)(Args...), ArgsBis... args)
        {if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: overloaded_1 [CLASS FUNCTION]\n";
            
            Timer Run(m_StartPoint, m_EndPoint);
            (classcp.*funcptr)(args...);     

            classcp.clear();         
        };
        
        template<typename Return, typename... Args, typename... ArgsBis>
        Benchmark(Return (*funcptr)(Args...), ArgsBis... args)
        {
            std::cout << "\nBenchmark: overloaded_2 [FUNCTION]\n";
            Timer Run(m_StartPoint, m_EndPoint);
            (*funcptr)(args...);               
        };
      

    /* ####################################################################################################################################################################### */
    /* ## Menu ############################################################################################################################################################### */
    /* ####################################################################################################################################################################### */


    private:

    public:    

        double Duration() 
        {   
            auto l_StartPoint = std::chrono::time_point_cast<std::chrono::microseconds>(*m_StartPoint).time_since_epoch().count();
            auto l_EndPoint   = std::chrono::time_point_cast<std::chrono::microseconds>(*m_EndPoint  ).time_since_epoch().count();

            return (l_EndPoint - l_StartPoint) * 10e-6;
        };
};

#endif