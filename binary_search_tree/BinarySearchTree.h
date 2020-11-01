/**
    @file    BinarySearchTree.h
    @brief   Header for class BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

#ifndef _BINARYSEARCHTREE_h
#define _BINARYSEARCHTREE_h

/** < */
#define DEFAULT_VALUE = 0;

/** < BinarySearchTree CHECKER */
#define _BINARYSEARCHTREE_CHECK_CONSTRUCTORS_ 0
#define _BINARYSEARCHTREE_CHECK_SUPPORT_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTIONS_ 0

/** < Iterator CHECKER */
#define _ITERATOR_CHECK_CONSTRUCTORS_ 0
#define _ITERATOR_CHECK_OPERATORS_ 0
#define _ITERATOR_CHECK_FUNCTIONS_ 0

/** < Node CHECKER */
#define _NODE_CHECK_CONSTRUCTORS_ 0

/** < Used Libraries. */
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

/** < Class based Iterator and Node Class. */
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
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "\nBinarySearchTree: deep copy ctor\n";};

        /** 
         * @brief MOVE CTOR. Constructs a new tree given an existing tree.
         * @param other rvalue reference to an existing tree.
         */
        BinarySearchTree (BinarySearchTree&& other) noexcept : m_Root{std::move(other.m_Root)}
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "BinarySearchTree: move ctor\n";};
        

    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    private: 

        /** @brief Enum class containing the possible outcomes when comparing keys. */
        enum kin {equal, go_left, go_right};

        /** @brief CompareType(std::less<>) OPERATOR. */
        CompareType LESS;

        /**
         * @brief copy(). SUPPORT to COPY CTOR.
         * @param p_Me
         * @param p_Parent
         * @return 
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
         */
        std::pair<node_t*, kin> sink(node_t* p_Root, const KeyType& l_Key);
       
        /**
         * @brief SUPPORT to erase().
         * @param vector
         * @param start
         * @param end
         * @return 
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
         */ 
        std::pair<iterator, bool> insert(pair_t&& l_Data);

        /**
         * @brief emplace().
         * @param
         * @return 
         */ 
        template<class... Args>
        std::pair<iterator, bool> emplace(Args&&... args);

        /**
         * @brief erase().
         * @param
         * @return 
         */ 
        void erase(const KeyType& l_Key);

        /**
         * @brief find(). Finds the node in the tree given a key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return iterator to the node containing the key or nullptr otherwise.
         */ 
        iterator find(const KeyType& l_Key);

        /**
         * @brief const find(). Finds the node in the tree given a key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return const_iterator to the node containing the key or nullptr otherwise.
         */ 
        const_iterator find(const KeyType& l_Key) const;

        /**
         * @brief end().
         * @return nullptr.
         */
        iterator end() noexcept;

        /**
         * @brief const end().
         * @return nullptr.
         */
        const_iterator end() const noexcept;
        
        /**
         * @brief cend().
         * @return nullptr.
         */
        const_iterator cend() const noexcept;

        /**
         * @brief begin().
         * @return
         */
        iterator begin() noexcept;

        /**
         * @brief const begin().
         * @return
         */
        const_iterator begin() const noexcept;

        /**
         * @brief cbegin().
         * @return
         */
        const_iterator cbegin() const noexcept;

        /** @brief balance(). */
        void balance();

        /** @brief clear(). Empties out the tree by releasing the memory occupied by the nodes. */
        void clear() noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Operator ############################################################################################################################################# */
    /* ########################################################################################################################################################################### */


        ValueType& operator[](const KeyType& l_Key)
        {
            iterator itr{find(l_Key)}; 
            if(itr.getCurrentNode() != nullptr) return itr -> second;

            /**< A pair made up by an iterator on the inserted element, and a bool to notify if the element alerady exists or not. */
            std::pair<iterator, bool> tmp = insert(pair_t(l_Key, DEFAULT_VALUE)); 
            
            return tmp.first -> second;
        }

        ValueType& operator[](KeyType&& l_Key)
        {
            iterator itr{find(std::forward<KeyType>(l_Key))}; 
            if(itr.getCurrentNode() != nullptr) return itr -> second;

            /**< A pair made up by an iterator on the inserted element, and a bool to notify if the element alerady exists or not. */
            std::pair<iterator, bool> tmp = insert(pair_t(std::forward<KeyType>(l_Key), DEFAULT_VALUE)); 
            
            return tmp.first -> second;
        }
        
        /**
         * @brief
         * @param
         * @param
         * @return
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