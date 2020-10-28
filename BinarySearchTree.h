/**
    @file    BinarySearchTree.h
    @brief   Header for class BinarySearchTree
    @authors Victor Plesco
    @date    01/01/1970
*/

#ifndef _BST_
#define _BST_

#define _BINARYSEARCHTREE_CHECK_CONSTRUCTORS_ 0
#define _BINARYSEARCHTREE_CHECK_SUPPORT_ 0
#define _BINARYSEARCHTREE_CHECK_FUNCTIONS_ 1

#define _ITERATOR_CHECK_CONSTRUCTORS_ 0
#define _ITERATOR_CHECK_OPERATORS_ 0

#define _NODE_CHECK_CONSTRUCTORS_ 0

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "Iterator.h"
#include "Node.h"

template<typename KeyType, typename ValueType, class Comparison = std::less<KeyType>>
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
         * @brief DEFAULT CTOR. 
         * @see insert();
         */
        BinarySearchTree () noexcept
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "\nBinarySearchTree: default ctor\n";};

        /** 
         * @brief DEEP COPY CTOR. Performs a deep copy of a given tree.
         * @param other const lvalue reference to an existing tree.
         * @see main();
         */
        BinarySearchTree (const BinarySearchTree& other)
        {
            if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_)
            std::cout << "\nBinarySearchTree: deep copy ctor\n";

            copy(other.m_Root);
        };

        /** 
         * @brief MOVE CTOR. Constructs a new tree given an existing tree.
         * @param other const rvalue reference to an existing tree.
         * @see main();
         */
        BinarySearchTree (const BinarySearchTree&& other) noexcept : m_Root{std::move(other.m_Root)}
        {if(_BINARYSEARCHTREE_CHECK_CONSTRUCTORS_) std::cout << "BinarySearchTree: move ctor\n";};
        

    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    private: 

        /** 
         * @brief Contains the possible outcomes when comparing keys. Gives directions.
         * @see sink();
         */
        enum kin {equal, go_left, go_right};

        /** @brief COMPARISON(std::less<>) OPERATOR. */
        Comparison LESS;

        /** @brief */

        //copy();

        /**
         * @brief SINK. Support function to insert(). Navigates through the tree basing its movements
         *        on the LESS() comparison between the inserted key and the keys present in the tree.
         *        Goes left whenever the inserted key is smaller and right when its bigger. It stops
         *        whenever the function doesn't find a left or right child or the keys are equal (aka 
         *        the key is already present in the tree).
         * 
         * @param p_Node pointer to the root.
         * @param l_Key const lvalue reference to a key.
         * @return std::pair<node_t*, kin>: node_t* is a pointer to node, kin is the output of the comparison.
         * @see insert(); _find();
         */
        std::pair<node_t*, kin> sink(node_t* p_Root, const KeyType& l_Key);
       
        /**
         * @brief _find(). Support function to find(). Is used to reduce lines of code when returning
         *        const_iterator and iterator. The function calls sink().
         * 
         * @param l_Key const lvalue reference to the key to be found in the tree.
         * @return node_t*: pointer to the node containing the key or nullptr if not found.
         * @see BinarySearchTree::find();erase()
         */ 
        node_t* _find(const KeyType& l_Key);

        /**
         * @brief SUPPORT to erase().
         * @param vector
         * @param start
         * @param end
         * @return 
         * @see
         */ 
        node_t* reorder(const std::vector<node_t*>& vector, const KeyType& start, const KeyType& end) const noexcept;

        /**
         * @brief findmin():
         * @param l_Node const lvalue reference to the key to be found in the tree
         * @return Pointer to the node containing the key or nullptr if not found.
         * @see sink();
         * @note Reduces code lines for iterator and const_iterator output.
         */ 
        node_t* findmin(node_t* l_Node) const noexcept;
        
        /**
         * @brief leftmost(). Support function to erase().
         * @param l_Key const lvalue reference to the key to be found in the tree
         * @return Pointer to the node containing the key or nullptr if not found.
         * @see sink();
         * @note Reduces code lines for iterator and const_iterator output.
         */
        node_t* leftmost(node_t* l_Node) const noexcept;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Member Functions ##################################################################################################################################### */
    /* ########################################################################################################################################################################### */
  

    public: 

        /**
         * @brief 
         * @param
         * @return 
         * @note
         */ 
        std::pair<iterator, bool> insert(pair_t&& l_Data);

        /**
         * @brief 
         * @param
         * @return 
         * @note
         */ 
        template<class... Args>
        std::pair<iterator, bool> emplace(Args&&... args)
        {
            std::cout << "\nemplace(): [CREATE].\n";
            return insert(pair_t{std::forward<Args>(args)...});
        };

        /**
         * @brief 
         * @param
         * @return 
         * @note
         */ 
        void erase(const KeyType& l_Key)
        {
            node_t* p{_find(l_Key)};
            if(!p) return;
            
            auto l=leftmost(p);
            std::cout << "KEY IS " << l -> m_Data.first;
            if(p == m_Root.get()){
                m_Root.release();
                if(p->m_RightChild){
                    p->m_RightChild->m_Parent=nullptr;
                    m_Root.reset(p->m_RightChild.release());
                    if(p->m_LeftChild){
                        p->m_LeftChild->m_Parent=l;
                        l->m_LeftChild.reset(p->m_LeftChild.release());
                    }
                }
                if(p->m_LeftChild){
                    p->m_LeftChild->m_Parent=nullptr;
                    m_Root.reset(p->m_LeftChild.release());
                }
            }
            else if(p->m_Parent->m_LeftChild.get()==p){
                p->m_Parent->m_LeftChild.release();
                if(p->m_RightChild){
                    p->m_RightChild->m_Parent=p->m_Parent;
                    p->m_Parent->m_LeftChild.reset(p->m_RightChild.release());
                }
                if(p->m_LeftChild){
                    p->m_LeftChild->m_Parent=l;
                    l->m_LeftChild.reset(p->m_LeftChild.release());
                }
            }
            else{
                p->m_Parent->m_RightChild.release();
                if(p->m_LeftChild){
                    p->m_LeftChild->m_Parent=l;
                    if(p->m_RightChild) l->m_LeftChild.reset(p->m_LeftChild.release());
                    else l->m_RightChild.reset(p->m_LeftChild.release());
                }
                if(p->m_RightChild){
                    p->m_RightChild->m_Parent=p->m_Parent;
                    p->m_Parent->m_RightChild.reset(p->m_RightChild.release());
                }
            }
            delete p;  
        }

        /**
         * @brief find the node in the tree with a given key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return iterator to the node containing the key or nullptr otherwise.
         * @note uses _find() to reduce code lines.
         */ 
        iterator find(const KeyType& l_Key);

        /**
         * @brief find the node in the tree with a given key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return const_iterator to the node containing the key or nullptr otherwise.
         * @note uses _find() to reduce code lines.
         */ 
        const_iterator find(const KeyType& l_Key) const;

        /**
         * @brief
         * @return
         * @note
         */
        iterator end() noexcept;

        /**
         * @brief
         * @return
         * @note
         */
        const_iterator end() const noexcept;
        
        /**
         * @brief
         * @return
         * @note
         */
        const_iterator cend() const noexcept;

        /**
         * @brief
         * @return
         * @note
         */
        iterator begin() noexcept;

        /**
         * @brief
         * @return
         * @note
         */
        const_iterator begin() const noexcept;

        /**
         * @brief
         * @return
         * @note
         */
        const_iterator cbegin() const noexcept;

        /** brief */
        void balance();

        /** @brief empties out the tree by releasing the memory occupied by the nodes. */
        void clear() noexcept;
};

#include "support.BinarySearchTree.inl"
#include "functions.BinarySearchTree.inl"

#endif