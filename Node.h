/**
    @file    Node.h
    @brief   Header file for class Node
    @authors Victor Plesco
    @date    01/01/1970
*/

#ifndef _NODE_h
#define _NODE_h

template<typename PairType>
class Node
{

    typedef PairType pair_t;


    /* ########################################################################################################################################################################### */
    /* ## Node: Object ########################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /** @brief POINTER to the parent node. */
        Node* m_Parent = nullptr;

        /** @brief unique_ptr to the right child. */
        std::unique_ptr<Node> m_RightChild; 

        /** @brief unique_ptr to the left child. */
        std::unique_ptr<Node> m_LeftChild; 

        /** 
         * @brief DATA of type std::pair<KeyType, ValueType>: KeyType is the PK, ValueType is customizable. 
         * @see BinarySearchTree<KeyType, ValueType, Comparison = std::less<KeyType>>
         */
        pair_t m_Data; 


    /* ########################################################################################################################################################################### */
    /* ## Node: Constructor ###################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /** 
         * @brief OVERLOADED_1 CTOR. Constructs a new node given a tuple(Key, Value).
         * @param other const lvalue reference to the tuple(Key, Value) to be inserted in the node.
         * @see BinarySearchTree::insert();
         */
        explicit Node (const pair_t& other) : m_Data{other}
        {if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: overloaded_1 (const pair_t&) ctor\n";};

        /** 
         * @brief OVERLOADED_2 CTOR. Constructs a new node given a tuple(Key, Value).
         * @param other const rvalue reference to the tuple(Key, Value) to be inserted in the node.
         * @see NONE
         */
        explicit Node (const pair_t&& other) : m_Data{other}
        {if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: overloaded_2 (const pair_t&&) ctor\n";};

        /** @brief DESTRUCTOR. */
        ~Node () noexcept 
        {if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: destructor\n";};
};

#endif
