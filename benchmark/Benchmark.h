/**
    @file    Benchmark.h
    @brief   Header for class Benchmark
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    05/03/2020
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
        /* < Only end point is stored in Timer, to avoid useless allocation which are time consuming. */
        chrono_t* m_EndPoint;

    public:
        
        /**
         * CTOR OVERLOADED
         * 
         * @brief The class timer is activated before executing a function. Its constructor connects the pointer 
         * from the class Benchmark with the one present in the object of the class Timer. It activates chrono.
         * 
         * @param StartPoint pointer passed from Benchmark class, used to store starting time value.
         * @param EndPoint pointer passed from Benchmark class, used to store ending time value.
        */
        Timer(chrono_t* StartPoint, chrono_t* EndPoint) : m_EndPoint{EndPoint}
        {*StartPoint = std::chrono::high_resolution_clock::now();};

        /**
         * DESTRUCTOR
         * 
         * @brief The destructor is activated once the function within class Benchmark has ended execution. It stores
         * the ending time inside a pointer within the Benchmark class before destroying the object of type Timer. 
        */
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

        /** Time is taken in microseconds therefore we prefer to store those values in the heap. */
        chrono_t* m_StartPoint = new chrono_t;
        chrono_t* m_EndPoint   = new chrono_t; 

    public:

        /**
         * DEFAULT CTOR
         * 
         * @brief Used to handle errors whenever the class is called without passing a pointer to 
         * a function to be analyzed. Conceptually won't create any problems. Still work in progress.
         */
        Benchmark() noexcept 
        {if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: default ctor\n";};
       
        /**
         * DESTRUCTOR
         * 
         * @brief Deletes previously allocated chunk of memories on the heap.
         */
       ~Benchmark() noexcept 
        {
           delete m_StartPoint, delete m_EndPoint;
           if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: destructor\n";
        };

        /**
         * CTOR OVERLOADED 1
         * 
         * @brief A mess but cool, at least seems to be. Requests an object of a class, passed by value (in our case
         * it triggers the deep copy constructor of the tree), a pointer to a member function of the latter with
         * specified returns and arguments, and the arguments needed within the passed function. We had to specify
         * twice the Args... twice (ArgsBis...) for semantic necessities of the language. Should handle all functions.  
         * 
         * @param classcp is an object of a class passed by value. The reason behind this is that in this way you can
         * compute several iterations, by copying and destroying every time the object (not efficient, I know, but
         * precision is everything for a statistician), without modifying the original object (e.g. insert won't change
         * the original tree).
         * 
         * @param funcptr is a pointer to a class. Return is the return of the considered function. Args... are its arguments.
         * @param args represent the arguments requested by the function. Templatized for number and type.
        */
        template<class Class, typename Return, typename... Args, typename... ArgsBis>
        Benchmark(Class classcp, Return (Class::*funcptr)(Args...), ArgsBis... args)
        {if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: overloaded_1 [CLASS FUNCTION]\n";
            
            Timer Run(m_StartPoint, m_EndPoint); /* < Timer activated. Chrono starts here. */
            (classcp.*funcptr)(args...); /* < Tested function activated here. */   
        }; /* < Timer destroyed. Chrono ends here. */
        
        /**
         * CTOR OVERLOADED 2
         * 
         * @brief Basically same as CTOR OVERLOADED 1, but focused on normal functions. The big problem is computing iterations
         * on the inserted function. Since it doesn't belong to an object, it may modify one. Work in progress.
         * 
         * @param funcptr is a pointer to a class. Return is the return of the considered function. Args... are its arguments.
         * @param args represent the arguments requested by the function. Templatized for number and type.        
         */
        template<typename Return, typename... Args, typename... ArgsBis>
        Benchmark(Return (*funcptr)(Args...), ArgsBis... args)
        {if(_BENCHMARK_CHECK_CONSTRUCTORS_) std::cout << "\nBenchmark: overloaded_2 [NORMAL FUNCTION]\n";

            Timer Run(m_StartPoint, m_EndPoint); /* < Timer activated. Chrono starts here. */
            (*funcptr)(args...); /* < Tested function activated here. */
        }; /* < Timer destroyed. Chrono ends here. */
      

    /* ####################################################################################################################################################################### */
    /* ## Menu ############################################################################################################################################################### */
    /* ####################################################################################################################################################################### */

    public:    

        /**
         * DURATION
         * 
         * @brief Simply computes the difference between the ending and starting point of chrono. 
         * @return microseconds transformed to seconds.
        */
        double Duration() 
        {   
            auto l_StartPoint = std::chrono::time_point_cast<std::chrono::microseconds>(*m_StartPoint).time_since_epoch().count();
            auto l_EndPoint   = std::chrono::time_point_cast<std::chrono::microseconds>(*m_EndPoint  ).time_since_epoch().count();

            return std::move((l_EndPoint - l_StartPoint) * 10e-6);
        };
};

#endif