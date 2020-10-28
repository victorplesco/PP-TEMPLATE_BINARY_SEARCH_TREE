/**
    @file    functions.BinarySearchTree.inl
    @brief   Inline file for member functions for class BinarySearchTree
    @authors Victor Plesco
    @date    01/01/1970
*/

#include "BinarySearchTree.h"

/** @brief insert() */
template<typename KeyType, typename ValueType, class Comparison>
std::pair<Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>, bool>
BinarySearchTree<KeyType, ValueType, Comparison>::insert(pair_t&& l_Data)
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\n\ninsert(): Key " << l_Data.first << "\n\n";
        
        if(m_Root.get() == nullptr)
        {
            m_Root.reset(new node_t{l_Data});

            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\ninsert(): Root not found [CREATE ROOT]\n";

                /** @brief The below return will call overloaded and move iterator ctors. */
                return std::make_pair(iterator{m_Root.get()}, true);
        }

        node_t* p_Root = m_Root.get();
        node_t* p_Node;

        std::pair<node_t*, kin> sinked = sink(p_Root, l_Data.first);

        switch (sinked.second)
        {
        case (equal)   :

            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\ninsert()[switch]: KEY EQUAL [EXIT]\n";
            return std::make_pair(iterator{sinked.first}, false);	
            break;	

        case (go_left) :

            std::cout << "\ninsert()[switch]: LEFT CHILD [CREATE]\n";
            p_Node = new node_t{l_Data};
            sinked.first -> m_LeftChild.reset(p_Node);
            break;

        case (go_right) :
        
            std::cout << "\ninsert()[switch]: RIGHT CHILD [CREATE]\n";
            p_Node = new node_t{l_Data};
            sinked.first -> m_RightChild.reset(p_Node);
            break;
        };

        p_Node -> m_Parent = sinked.first;
            return std::make_pair(iterator{p_Node}, true);
    };

/** @brief emplace() */
//template<typename KeyType, typename ValueType, class Comparison>
//BinarySearchTree<KeyType, ValueType, Comparison>::

/** @brief erase() */
//template<typename KeyType, typename ValueType, class Comparison>

//BinarySearchTree<KeyType, ValueType, Comparison>::

/** @brief find() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::find(const KeyType& l_Key)
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nfind(): [CALLED]\n";

        return iterator{_find(l_Key)};
    };

/** @brief const find() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::find(const KeyType& l_Key) const
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nconst find(): [CALLED]\n";

        return const_iterator{_find(l_Key)};
    };

/** @brief end() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::end() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nend(): [CALLED]\n";
        
        return iterator{nullptr};
    };

/** @brief const end() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::end() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nconst end(): [CALLED]\n";

        return const_iterator{nullptr};
    };

/** @brief cend() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::cend() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\ncend(): [CALLED]\n";

        return const_iterator{nullptr};
    };

/** @brief begin() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::begin() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nbegin(): [CALLED]\n";

        if(!m_Root) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nbegin(): Root not found [EXIT]\n";

            return iterator{nullptr};
        }

        node_t* p_Node = m_Root.get();
        while(p_Node -> m_LeftChild.get()) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nbegin(): LeftChild exists and is " << p_Node -> m_LeftChild -> m_Data.first << " [MOVE LEFT]\n";

            p_Node = p_Node -> m_LeftChild.get();
        };

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nbegin(): LeftChild doesn't exist [EXIT]\n";

        return iterator{p_Node};
    };

/** @brief const begin() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::begin() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nconst begin(): [CALLED]\n";

        if(!m_Root) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nconst begin(): Root not found [EXIT]\n";

            return const_iterator{nullptr};
        }

        node_t* p_Node = m_Root.get();
        while(p_Node -> m_LeftChild.get()) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nconst begin(): LeftChild exists and is " << p_Node -> m_LeftChild -> m_Data.first << " [MOVE LEFT]\n";

            p_Node = p_Node -> m_LeftChild.get();
        };

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nconst begin(): LeftChild doesn't exist [EXIT]\n";

        return const_iterator{p_Node};
    };

/** @brief cbegin() */
template<typename KeyType, typename ValueType, class Comparison>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, Comparison>::cbegin() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\ncbegin(): [CALLED]\n";

        if(!m_Root) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\ncbegin(): Root not found [EXIT]\n";

            return const_iterator{nullptr};
        }

        node_t* p_Node = m_Root.get();
        while(p_Node -> m_LeftChild.get()) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\ncbegin(): LeftChild exists and is " << p_Node -> m_LeftChild -> m_Data.first << " [MOVE LEFT]\n";

            p_Node = p_Node -> m_LeftChild.get();
        };

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\ncbegin(): LeftChild doesn't exist [EXIT]\n";

        return const_iterator{p_Node};
    };

/** @brief balance() */
template<typename KeyType, typename ValueType, class Comparison>
void BinarySearchTree<KeyType, ValueType, Comparison>::balance()
    {
        std::vector<node_t*> ordered;
        iterator itr{begin()};

        for(; itr != end(); ++itr)
            {ordered.push_back(itr.m_CurrentNode);}

        m_Root.reset(reorder(ordered, 0, ordered.size() - 1));
        m_Root -> m_Parent = nullptr;
    };

/** @brief clear() */
template<typename KeyType, typename ValueType, class Comparison>
void BinarySearchTree<KeyType, ValueType, Comparison>::clear() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nclear(): Root set to nullptr\n";

        m_Root.reset(nullptr);
    };
