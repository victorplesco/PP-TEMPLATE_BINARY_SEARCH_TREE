/**
    @file    iterator.h
    @brief   Header for class iterator
    @authors Victor Plesco
    @date    01/01/1970
*/

#ifndef _ITR_
#define _ITR_

#include <iostream>

template<class NodeType, typename PairType>
class Iterator
{	
    

    /* ########################################################################################################################################################################### */
    /* ## Iterator: Object ####################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    private: 

        NodeType* m_CurrentNode = nullptr; 


    /* ########################################################################################################################################################################### */
    /* ## _iterator: Constructor ################################################################################################################################################# */
    /* ########################################################################################################################################################################### */


    public: 

        /** 
         * @brief DEFAULT CTOR. 
         * @param 
         * @note 
         */

        Iterator () : m_CurrentNode{nullptr}
        {std::cout << "Iterator: default ctor\n";};

        /** 
         * @brief OVERLOADED CTOR. 
         * @param other pointer to an object of type Node.
         * @note 
         */

        explicit Iterator (NodeType* other) : m_CurrentNode{other}
        {std::cout << "Iterator: overloaded ctor\n";};

        /** 
         * @brief COPY CTOR. 
         * @param other reference to existing iterator. 
         * @note 
         */

        Iterator (const Iterator& other) noexcept : m_CurrentNode{other.m_CurrentNode}
        {std::cout << "Iterator: copy ctor\n";};

        /** 
         * @brief MOVE CTOR. 
         * @param other rvalue reference to existing iterator. 
         * @note 
         */

        Iterator (const Iterator&& other) noexcept : m_CurrentNode{other.m_CurrentNode}
        {std::cout << "Iterator: move ctor\n";};


    /* ########################################################################################################################################################################### */
    /* ## _iterator: Operator #################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /**
         * @brief COPY ASSIGNMENT(=) operator.
         * @param other: const lvalue reference to an iterator.
         * @note
         */

        Iterator& operator= (const Iterator& other) noexcept
        {
            m_CurrentNode = other.m_CurrentNode;
            return *this;
        };

        /**
         * @brief DEREFERENCE(*) operator.
         * @return 
         * @note
         */

        PairType& operator* () const noexcept
        {return m_CurrentNode -> m_Data;};

        /**
         * @brief BOOLEAN EQUALITY(==) operator.
         * @param other: const lvalue reference to an iterator.
         * @return TRUE for EQUALITY, FALSE for INEQUALITY.
         * @note
         */

        bool operator== (const Iterator& other) const noexcept
        {return other.m_CurrentNode == m_CurrentNode;};

        /**
         * @brief BOOLEAN INEQUALITY(!=) operator.
         * @param other: const lvalue reference to an iterator.
         * @return TRUE for INEQUALITY, FALSE for EQUALITY.
         * @note
         */

        bool operator!= (const Iterator& other) const noexcept
        {return !(other.m_CurrentNode == m_CurrentNode);};
};

#endif