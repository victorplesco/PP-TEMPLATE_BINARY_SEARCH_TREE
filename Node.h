/**
    @file    Node.h
    @brief   Header for class Node
    @authors Victor Plesco
    @date    01/01/1970
*/

#ifndef _NODE_
#define _NODE_

#include <iostream>
#include <memory>

template<typename PairType>
class Node
{


    /* ########################################################################################################################################################################### */
    /* ## Node: Object ########################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /** 
         * @brief POINTER to the parent node. 
         * @note  raw_ptr vs unique_ptr
         */

        Node* m_Parent;

        /** @brief unique_ptr to the right child. */
        std::unique_ptr<Node> m_RightChild; 

        /** @brief unique_ptr to the left child. */
        std::unique_ptr<Node> m_LeftChild; 

        /** @brief DATA of type std::pair: KeyType is the PK, ValueType is customizable. */
        PairType m_Data; 


    /* ########################################################################################################################################################################### */
    /* ## Node: Constructor ###################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /** @brief DEFAULT CTOR. Children don't need nullptr (std::unique_ptr). */
        Node () noexcept : m_Parent{nullptr} {std::cout << "Node: default ctor\n";};

        /** 
         * @brief OVERLOADED CTOR.
         * @param
         */

        Node (const PairType& l_Data) : m_Parent{nullptr}, m_Data{l_Data}
        {std::cout << "Node: overloaded ctor\n";};

        /** 
         * @brief MOVE CTOR.
         * @param 
         */

        Node (const PairType&& l_Data) : m_Parent{nullptr}, m_Data{l_Data}
        {std::cout << "Node: move ctor\n";};

        /** @brief DESTRUCTOR. */
        ~Node () noexcept = default;
};

#endif
