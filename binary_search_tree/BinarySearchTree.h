/**
    @file    BinarySearchTree.h
    @brief   Header for class BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    05/03/2020
    @version 2.1
*/

#ifndef _BINARYSEARCHTREE_h
#define _BINARYSEARCHTREE_h

/** < Macro for the [] operator, in case the node is not found*/
#define DEFAULT_VALUE 0

/** < BinarySearchTree CHECKER */
#define _BINARYSEARCHTREE_CHECK_CONSTRUCTORS_ 0
#define _BINARYSEARCHTREE_CHECK_SUPPORT_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTIONS_ 0

#define _BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTION_FIND_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_ 0

#define _BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_ 0
#define _BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_ 0

/** < Iterator CHECKER */
#define _ITERATOR_CHECK_CONSTRUCTORS_ 0
#define _ITERATOR_CHECK_OPERATORS_ 0
#define _ITERATOR_CHECK_FUNCTIONS_ 0

/** < Node CHECKER */
#define _NODE_CHECK_CONSTRUCTORS_ 0

/** < Used Libraries. */
#include <iostream> // std::cout
#include <memory> // std::unique_pr<>, std::make_unique<>
#include <utility> // 
#include <vector> // std::vector<>

/** < Class based Iterator and Node Class. */
#include "Iterator.h" // class Iterator
#include "Node.h" // class Node

template<typename KeyType, typename ValueType, class CompareType = std::less<KeyType>>
class BinarySearchTree
{

    typedef std::pair<const KeyType, ValueType> pair_t;
    typedef Node<pair_t> node_t;
    typedef Iterator<node_t, pair_t> iterator;
    typedef Iterator<node_t, const pair_t> const_iterator;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Object ############################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    private:

        /** @brief unique_ptr to the root. */
        std::unique_ptr<node_t> m_Root;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Constructor ########################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    public:

        /**
         * DEFAULT CTOR
         */
        BinarySearchTree () noexcept {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "\nBinarySearchTree: default ctor\n";};

        /** 
         * DEEP COPY CTOR
         * 
         * @brief Performs a deep copy of a given tree.
         * @param other const lvalue reference to an existing tree.
         * @see copy
         */
        BinarySearchTree (const BinarySearchTree& other) : m_Root{copy(other.m_Root.get(), nullptr)}
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "\nBinarySearchTree: deep copy ctor\n";};

        /** 
         * MOVE CTOR
         * 
         * @brief Constructs a new tree given an existing tree.
         * @param other rvalue reference to an existing tree.
         */
        BinarySearchTree (BinarySearchTree&& other) noexcept : m_Root{std::move(other.m_Root)}
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "BinarySearchTree: move ctor\n";};
        

    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    private: 

        /**
         * ENUM
         * 
         * this enum is used to decide if you have to visit a specific Node
		 * between the left child and the right child, or just remain in the
		 * current node. It is used in the insert function and find function 
         * */
        enum kin {equal, go_left, go_right};

        /** < CompareType(std::less<>) OPERATOR. */
        CompareType LESS;

        /**
         * COPY 
         * 
         * @brief support function for the copy ctor.
         * @param p_Me it is a pointer to the actual node
         * @param p_Parent it is a pointer to the parent of the actual node
         * @return pointer to a node
         */ 
        node_t* copy(const node_t* p_Me, node_t* p_Parent);

        /**
         * SINK
         * 
         * @brief support function to insert() and find(). Navigates through the tree basing 
         *        its movements on the LESS() comparison between the inserted key and the keys present 
         *        in the tree. Goes left whenever the inserted key is smaller and right when its bigger. 
         *        It stops whenever the function doesn't find a left or right child or the keys are 
         *        equal (aka the key is already present in the tree).
         * 
         * @param p_Node pointer to the root.
         * @param l_Key const lvalue reference to a key.
         * @return std::pair<node_t*, kin>: node_t* is a pointer to node, kin is the output of the comparison.
         */
        std::pair<node_t*, kin> sink(node_t* p_Root, const KeyType& l_Key);
       
        /**
         * ORDER
         * 
         * @brief support function for balance(). It is recursively to re-organize the tree.
         * @param vector a reference to an array of pointers to node
         * @param start const reference to the first position of the vector
         * @param end const reference to the last position of the vector
         * @return pointer to a node (new root)
         */ 
        node_t* order(const std::vector<node_t*>& vector, const KeyType& start, const KeyType& end) const noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Member Functions ##################################################################################################################################### */
    /* ########################################################################################################################################################################### */
  

    public: 

        /**
         * INSERT
         * 
         * @brief this function is used by the user to insert a new node into the tree
         * @param l_Data it is a reference to an rvalue, i.e. the data for the new node
         * @return std::pair<iterator, bool> that is a pair of the iterator over the position
         *         of the inserted node and a bool value used to check if the node already exist
         * @see sink(node_t* p_Root, const KeyType& l_Key)
         */ 
        std::pair<iterator, bool> insert(pair_t&& l_Data);

        /**
         * EMPLACE
         * 
         * @brief this function is used to insert emplace new node in the tree
         * @param Args it is a bag of data
         * @return std::pair<iterator, bool> same return of the insert function
         * @see insert(pair_t&& l_Data)
         */ 
        template<class... Args>
        std::pair<iterator, bool> emplace(Args&&... args);

        /**
         *  ERASE
         * 
         * @brief it is used to delete an existing node of the tree, when it is discarded a subset of
         *        pointers from different nodes are moved according the tree structure
         * @param l_key it is a const reference to an existing key
         * @see find(const KeyType &l_Key)
         */ 
        void erase(const KeyType& l_Key);

        /**
         * FIND
         * 
         * @brief finds the node in the tree given a key
         * @param l_Key: const lvalue reference to the key to be found in the tree
         * @return iterator to the node containing the key or nullptr otherwise
         * @see sink(node_t* p_Root, const KeyType& l_Key)
         */ 
        iterator find(const KeyType& l_Key);

        /**
         * FIND (CONST)
         * 
         * @brief finds the node in the tree given a key
         * @param l_Key: const lvalue reference to the key to be found in the tree
         * @return const_iterator to the node containing the key or nullptr otherwise
         * @see sink(node_t* p_Root, const KeyType& l_Key)
         */ 
        const_iterator find(const KeyType& l_Key) const;

        /**
         * END
         * 
         * @brief it is used to point to the last posistion of the last position of the tree
         * @return iterator containing a pointer to the last position
         */
        iterator end() noexcept;

        /**
         * END (CONST)
         * 
         * @brief it is used to point to the last posistion of the last position of the tree
         * @return const_iterator containing a pointer to the last position
         */
        const_iterator end() const noexcept;
        
        /**
         * CEND
         * 
         * @brief it is used to point to the last posistion of the last position of the tree
         * @return const_iterator containing a pointer to the last position
         */
        const_iterator cend() const noexcept;

        /**
         * BEGIN
         * 
         * @brief it is used to move to the left-most node that is the node with smalle key
         * @return iterator to the left-most node, according with the tree traversal method
         */
        iterator begin() noexcept;

        /**
         * BEGIN (CONST)
         * 
         * @brief it is used to move to the left-most node that is the node with smalle key
         * @return const iterator to the left-most node, according with the tree traversal method
         */
        const_iterator begin() const noexcept;

        /**
         * CBEGIN
         * 
         * @brief it is used to move to the left-most node that is the node with smalle key
         * @return const iterator to the left-most node, according with the tree traversal method
         */
        const_iterator cbegin() const noexcept;

        /** 
         * BALANCE
         * 
         * @brief order the nodes in a vector based on the key value,
		 *	      than call the Bst_ordered function to balance the tree and set the 
		 *	      parent of the new root as nullptr
         * @see order(const std::vector<node_t*>& array, const KeyType& start, const KeyType& end) 
         * */
        void balance();

        /** 
         * CLEAR
         * 
         * @brief Empties out the tree by releasing the memory occupied by the nodes
         * */
        void clear() noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Operator ############################################################################################################################################# */
    /* ########################################################################################################################################################################### */

        /**
         * OPERATOR[] (CONST)
         * 
         * @brief it is used to deference the value of a node, given its key (if exist) 
         * @param l_Key a const reference to a key
         * @return a reference to the associated value of the node with the given key
         * @see find(const KeyType &l_Key) 
         * @see insert(std::pair<...> &&l_Data)
         **/

        ValueType& operator[](const KeyType& l_Key)
        {
            iterator itr{find(l_Key)}; 
            if(itr.getCurrentNode() != nullptr) return itr -> second;

            /**< A pair made up by an iterator on the inserted element, and a bool to notify if the element alerady exists or not. */
            std::pair<iterator, bool> tmp = insert(pair_t(l_Key, DEFAULT_VALUE)); 
            
            return tmp.first -> second;
        }

        /**
         * OPERATOR[]
         * 
         * @brief it is used to deference the value of a node, given its key (if exist) 
         * @param l_Key a const reference to a key
         * @return a reference to the associated value of the node with the given key
         * @see find(const KeyType &l_Key)
         * @see insert(std::pair<...> &&l_Data)
         **/
        ValueType& operator[](KeyType&& l_Key)
        {
            iterator itr{find(std::forward<KeyType>(l_Key))}; 
            if(itr.getCurrentNode() != nullptr) return itr -> second;

            /**< A pair made up by an iterator on the inserted element, and a bool to notify if the element alerady exists or not. */
            std::pair<iterator, bool> tmp = insert(pair_t(std::forward<KeyType>(l_Key), DEFAULT_VALUE)); 
            
            return tmp.first -> second;
        }
        
        /**
         * OPERATOR<<
         * 
         * @brief it is used to print the tree
         * @param os it is a reference to a Stream channel
         * @param other it is a const reference to a tree
         * @return reference to a Stream variable
         */
        friend std::ostream& operator<< (std::ostream& os, const BinarySearchTree& other) 
        {
            for(const auto& i : other) 
            {os << i.first << " " << i.second << std::endl;}
            return os;
        };
};

#include "support.BinarySearchTree.inl" // copy, sink, order
#include "functions.BinarySearchTree.inl" // tree functions

#endif