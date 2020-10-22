/**
    @file    BinarySearchTree.h
    @brief   Header for class BinarySearchTree
    @authors Victor Plesco
    @date    01/01/1970
*/

#ifndef _BST_
#define _BST_

#include <iostream>
#include <memory>
#include <utility>

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

        std::unique_ptr<node_t> m_Root;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Constructor ########################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    public:

        /** @brief DEFAULT CTOR. */
        BinarySearchTree () noexcept : m_Root{nullptr} 
        {std::cout << "BinarySearchTree: default ctor\n";};
        

    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    private: 
    
        /** @brief */
        enum kin {equal, go_left, go_right};

        /** @brief */
        Comparison LESS;


    /* ########################################################################################################################################################################### */
    /* ## BinarySearchTree: Support ############################################################################################################################################## */
    /* ########################################################################################################################################################################### */
  

    public:


        /**
         * @brief
         * @return
         * @note
         */
        std::pair<node_t*, kin> sink(node_t* p_Node, const KeyType& l_Key)
        {
            if(LESS(l_Key, p_Node -> m_Data.first))
            {
                std::cout << "\nsink(): Key is smaller.\n";
                if(p_Node -> m_LeftChild != nullptr)
                {
                    std::cout << "\nsink(): LeftChild exists[MOVE LEFT]!\n";
                    return sink(p_Node -> m_LeftChild.get(), l_Key);
                }
                            std::cout << "\nsink(): LeftChild doesn't exist[STOP]!\n";
                            return std::make_pair(p_Node, kin::go_left);
            }

            else if(LESS(p_Node -> m_Data.first, l_Key))
            {
                std::cout << "\nsink(): Key is bigger.\n";
                if(p_Node -> m_RightChild != nullptr)
                {
                    std::cout << "\nsink(): RightChild exists[MOVE RIGHT]!\n";
                    return sink(p_Node -> m_RightChild.get(), l_Key);
                }
                            std::cout << "\nsink(): RightChild doesn't exist[STOP]!\n";
                            return std::make_pair(p_Node, kin::go_right);
            }

            std::cout << "\nsink(): Key exists[STOP]!\n";
            return std::make_pair(p_Node, kin::equal);
        };

        /**
         * @brief SUPPORT to find()
         * @param l_Key const lvalue reference to the key to be found in the tree
         * @return Pointer to the node containing the key or nullptr if not found.
         * @see sink();
         * @note Reduces code lines for iterator and const_iterator output.
         */ 
        node_t* _find(const KeyType& l_Key)
        {
            if(m_Root.get() == nullptr) {return nullptr;}

            std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
            if(sinked.second == kin::equal) {return sinked.first;}

            return nullptr;
        };


        /* ########################################################################################################################################################################### */
        /* ## BinarySearchTree: Member Functions ##################################################################################################################################### */
        /* ########################################################################################################################################################################### */
  

        /**
         * @brief 
         * @param
         * @return 
         * @note
         */ 
        std::pair<iterator, bool> insert(pair_t&& l_Data)
        {
            std::cout << "\nKey " << l_Data.first << std::endl;
            if(m_Root.get() == nullptr)
            {
                m_Root.reset(new node_t{l_Data});
                std::cout << "\ninsert(): CREATING ROOT\n\n";

                    /** @brief The below return will call overloaded and move iterator ctors. */
                    return std::make_pair(iterator{m_Root.get()}, true);
            }

            node_t* p_Root = m_Root.get();
            node_t* p_Node;

            std::pair<node_t*, kin> sinked = sink(p_Root, l_Data.first);

            switch (sinked.second)
            {
            case (equal)   :
                std::cout << "\ninsert()[switch]: KEY EQUAL[EXIT].\n\n";
                return std::pair<iterator, bool>(iterator(sinked.first), false);	
                break;			
            case (go_left) :
                std::cout << "\ninsert()[switch]: LEFT CHILD[CREATE].\n\n";
                p_Node = new node_t{l_Data};
                sinked.first -> m_LeftChild.reset(p_Node);
                break;
            case (go_right) :
                std::cout << "\ninsert()[switch]: RIGHT CHILD[CREATE].\n\n";
                p_Node = new node_t{l_Data};
                sinked.first -> m_RightChild.reset(p_Node);
                break;
            };

            p_Node -> m_Parent = sinked.first;
                return std::pair<iterator, bool>(iterator(p_Node), true);
        };

        /**
         * @brief find the node in the tree with a given key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return iterator to the node containing the key or nullptr otherwise.
         * @note uses _find() to reduce code lines.
         */ 
        iterator find(const KeyType& l_Key)
        {return iterator{_find(l_Key)};};

        /**
         * @brief find the node in the tree with a given key. 
         * @param l_Key: const lvalue reference to the key to be found in the tree.
         * @return const_iterator to the node containing the key or nullptr otherwise.
         * @note uses _find() to reduce code lines.
         */ 
        const_iterator find(const KeyType& l_Key) const
        {return const_iterator{_find(l_Key)};};

        /**
         * @brief
         * @return
         * @note
         */

        iterator end() noexcept {return iterator{nullptr};};

        /**
         * @brief
         * @return
         * @note
         */

        const_iterator end() const noexcept {return const_iterator{nullptr};};
        
        /**
         * @brief
         * @return
         * @note
         */

        const_iterator cend() const noexcept {return const_iterator{nullptr};};

        /**
         * @brief
         * @return
         * @note
         */

        iterator begin() noexcept
        {
            if(!m_Root) {return iterator{nullptr};}

            node_t* tmp = m_Root.get();
            while(tmp -> m_LeftChild.get()) {tmp = tmp -> m_LeftChild.get();};

            return iterator{tmp};
        };

        /**
         * @brief
         * @return
         * @note
         */

        const_iterator begin() const noexcept
        {
            if(!m_Root) {return const_iterator{nullptr};}

            node_t* tmp = m_Root.get();
            while(tmp -> m_LeftChild.get()) {tmp = tmp -> m_LeftChild.get();};

            return const_iterator{tmp};
        };

        /**
         * @brief
         * @return
         * @note
         */

        const_iterator cbegin() noexcept
        {
            if(!m_Root) {return const_iterator{nullptr};}

            node_t* tmp = m_Root.get();
            while(tmp -> m_LeftChild.get()) {tmp = tmp -> m_LeftChild.get();};

            return const_iterator{tmp};
        };
};

#endif