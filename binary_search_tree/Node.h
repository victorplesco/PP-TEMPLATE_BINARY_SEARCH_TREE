/**
    @file    Node.h
    @brief   Header file for class Node
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

#ifndef _NODE_h
#define _NODE_h

template<typename PairType>
class Node
{

    /** < Templatizing for semantic consistency with BinarySearchTree Class. */
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

        /** @brief DATA of type PairType = std::pair<KeyType, ValueType>: KeyType is the PK, ValueType is customizable. */
        pair_t m_Data; 


    /* ########################################################################################################################################################################### */
    /* ## Node: Constructor ###################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /** @brief DEFAULT CTOR. */
        Node() = delete;

        /** @brief COPY CTOR. */
        Node(const Node& other) = delete;

        /** @brief MOVE CTOR. */
        Node(Node&& other) = delete;

        /** 
         * @brief OVERLOADED_1 CTOR. Constructs a new node given a tuple(Key, Value).
         * @param other const lvalue reference to the tuple(Key, Value) to be inserted in the node.
         */
        explicit Node (const pair_t& other) noexcept : m_RightChild{nullptr}, m_LeftChild{nullptr}, m_Data{other}
        {if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: overloaded_1 (const pair_t&) ctor\n";};

        /** pair_t
         * @brief OVERLOADED_2 CTOR. Constructs a new node given a tuple(Key, Value).
         * @param other const lvalue reference to the tuple(Key, Value) to be inserted in the node.
         */
        explicit Node (const pair_t&& other) noexcept : m_RightChild{nullptr}, m_LeftChild{nullptr}, m_Data{std::move(other)}
        {
            if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: overloaded_2 (const pair_t&) ctor\n";
            other.first = other.second = 0;
        };

        /** @brief DESTRUCTOR. */
        ~Node () noexcept {if(_NODE_CHECK_CONSTRUCTORS_) std::cout << "\nNode: destructor\n";};


    /* ########################################################################################################################################################################### */
    /* ## Node: Operator ######################################################################################################################################################### */
    /* ########################################################################################################################################################################### */

    
    public:

        /** @brief COPY ASSIGNMENT. */
        Node& operator= (const Node& other) = delete;

        /** @brief MOVE ASSIGNMENT. */
        Node& operator= (Node&& other) = delete;

};

#endif
