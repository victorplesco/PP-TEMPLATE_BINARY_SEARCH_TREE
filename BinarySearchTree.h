/**
    @file    BinarySearchTree.h
    @brief   Header for class BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

#ifndef _BST_
#define _BST_

/** < BinarySearchTree checker */
#define _BINARYSEARCHTREE_CHECK_CONSTRUCTORS_ 1
#define _BINARYSEARCHTREE_CHECK_SUPPORT_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTIONS_ 0

/** < Iterator checker */
#define _ITERATOR_CHECK_CONSTRUCTORS_ 0
#define _ITERATOR_CHECK_OPERATORS_ 0

/** < Node checker */
#define _NODE_CHECK_CONSTRUCTORS_ 0


#include <iostream>
#include <memory>
#include <utility>
#include <vector>


#include "Iterator.h"
#include "Node.h"


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

        /** @brief DEFAULT CTOR. @see insert() */
        BinarySearchTree () noexcept {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "\nBinarySearchTree: default ctor\n";};

        /** 
         * @brief DEEP COPY CTOR. Performs a deep copy of a given tree.
         * @param other const lvalue reference to an existing tree.
         */
        BinarySearchTree (const BinarySearchTree& other) : m_Root{copy(other.m_Root.get(), nullptr)}
        {
            if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_)
            std::cout << "\nBinarySearchTree: deep copy ctor\n";
        };

        /** 
         * @brief MOVE CTOR. Constructs a new tree given an existing tree.
         * @param other const rvalue reference to an existing tree.
         */
        BinarySearchTree (const BinarySearchTree&& other) noexcept : m_Root{std::move(other.m_Root)}
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "BinarySearchTree: move ctor\n";};
        

    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    private: 

        /** 
         * @brief Enum class containing the possible outcomes when comparing keys.
         * @see sink();
         */
        enum kin {equal, go_left, go_right};

        /** @brief CompareType(std::less<>) OPERATOR. */
        CompareType LESS;

        /**
         * @brief copy(). SUPPORT to COPY CTOR.
         * @param p_Me
         * @param p_Parent
         * @return 
         * @see
         */ 
        node_t* copy(const node_t* p_Me, node_t* p_Parent);

        /**
         * @brief sink(). SUPPORT function to insert() and find(). Navigates through the tree basing 
         *        its movements on the LESS() comparison between the inserted key and the keys present 
         *        in the tree. Goes left whenever the inserted key is smaller and right when its bigger. 
         *        It stops whenever the function doesn't find a left or right child or the keys are 
         *        equal (aka the key is already present in the tree).
         * 
         * @param p_Node pointer to the root.
         * @param l_Key const lvalue reference to a key.
         * @return std::pair<node_t*, kin>: node_t* is a pointer to node, kin is the output of the comparison.
         * @see
         */
        std::pair<node_t*, kin> sink(node_t* p_Root, const KeyType& l_Key);
       
        /**
         * @brief SUPPORT to erase().
         * @param vector
         * @param start
         * @param end
         * @return 
         * @see
         */ 
        node_t* order(const std::vector<node_t*>& vector, const KeyType& start, const KeyType& end) const noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Member Functions ##################################################################################################################################### */
    /* ########################################################################################################################################################################### */
  

    public: 

        /**
         * @brief insert().
         * @param
         * @return 
         * @see
         */ 
        std::pair<iterator, bool> insert(pair_t&& l_Data);

        /**
         * @brief emplace().
         * @param
         * @return 
         * @see
         */ 
        template<class... Args>
        std::pair<iterator, bool> emplace(Args&&... args);

        /**
         * @brief erase().
         * @param
         * @return 
         * @see
         */ 
        void erase(const KeyType& l_Key);

        /**
         * @brief find(). Finds the node in the tree given a key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return iterator to the node containing the key or nullptr otherwise.
         * @see
         */ 
        iterator find(const KeyType& l_Key);

        /**
         * @brief const find(). Finds the node in the tree given a key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return const_iterator to the node containing the key or nullptr otherwise.
         * @see
         */ 
        const_iterator find(const KeyType& l_Key) const;

        /**
         * @brief end().
         * @return nullptr.
         * @see
         */
        iterator end() noexcept;

        /**
         * @brief const end().
         * @return nullptr.
         * @see
         */
        const_iterator end() const noexcept;
        
        /**
         * @brief cend().
         * @return nullptr.
         * @see
         */
        const_iterator cend() const noexcept;

        /**
         * @brief begin().
         * @return
         * @see
         */
        iterator begin() noexcept;

        /**
         * @brief const begin().
         * @return
         * @see
         */
        const_iterator begin() const noexcept;

        /**
         * @brief cbegin().
         * @return
         * @see
         */
        const_iterator cbegin() const noexcept;

        /**
         * @brief balance().
         * @see
         */
        void balance();

        /**
         * @brief clear(). Empties out the tree by releasing the memory occupied by the nodes.
         * @see
         */
        void clear() noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Operator ############################################################################################################################################# */
    /* ########################################################################################################################################################################### */


        /**
         * @brief
         * @param
         * @param
         * @return
         * @see
         */
        friend std::ostream& operator<< (std::ostream& os, const BinarySearchTree& other) 
        {
            for(const auto& i : other) 
            {os << i.first << " " << i.second << std::endl;}
            return os;
        };
};

#include "support.BinarySearchTree.inl"
#include "functions.BinarySearchTree.inl"

#endif