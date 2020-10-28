/**
    @file    support.BinarySearchTree.inl 
    @brief   Inline file for support functions of class BinarySearchTree
    @authors Victor Plesco
    @date    01/01/1970
*/

/** @brief sink(). */
template<typename KeyType, typename ValueType, class Comparison>
std::pair<Node<std::pair<const KeyType, ValueType>>*, typename BinarySearchTree<KeyType, ValueType, Comparison>::kin> 
BinarySearchTree<KeyType, ValueType, Comparison>::sink(Node<std::pair<const KeyType, ValueType>>* p_Node, const KeyType& l_Key)
    {
        if(LESS(l_Key, p_Node -> m_Data.first))
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nsink(): Key is smaller [CHECK LEFTCHILD]\n";

            if(p_Node -> m_LeftChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
                std::cout << "\nsink(): LeftChild exists [MOVE LEFT]\n";

                return sink(p_Node -> m_LeftChild.get(), l_Key);
            }
                        if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
                        std::cout << "\nsink(): LeftChild doesn't exist [STOP]\n";

                        return std::make_pair(p_Node, kin::go_left);
        }

        else if(LESS(p_Node -> m_Data.first, l_Key))
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nsink(): Key is bigger [CHECK RIGHTCHILD]\n";

            if(p_Node -> m_RightChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
                std::cout << "\nsink(): RightChild exists [MOVE RIGHT]\n";

                return sink(p_Node -> m_RightChild.get(), l_Key);
            }
                        if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
                        std::cout << "\nsink(): RightChild doesn't exist [STOP]\n";

                        return std::make_pair(p_Node, kin::go_right);
        }

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
        std::cout << "\nsink(): Key exists [STOP]\n";

        return std::make_pair(p_Node, kin::equal);
    };

/** @brief _find(). */
template<typename KeyType, typename ValueType, class Comparison>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, Comparison>::_find(const KeyType& l_Key)
    {
        if(m_Root.get() == nullptr) 
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\n_find(): Root doesn't exist [EXIT]\n";
            return nullptr;
        }

        std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
        if(sinked.second == kin::equal) 
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\n_find(): Key found [EXIT]\n";
            return sinked.first;
        }

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
        std::cout << "\n_find(): Key not found[EXIT]!\n";
        return nullptr;
    };

/** @brief reorder(). */
template<typename KeyType, typename ValueType, class Comparison>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, Comparison>::reorder(const std::vector<Node<std::pair<const KeyType, ValueType>>*>& vector, const KeyType& start, const KeyType& end) const noexcept
    {
        if(LESS(end, start)) {return nullptr;}
        std::cout << "end is: " << end << " and start is " << start << std::endl;
        
        const KeyType median{(end + start)/2};
        node_t* l_Node{vector[median]};

        l_Node -> m_LeftChild.release();
        l_Node -> m_RightChild.release();

        l_Node -> m_LeftChild.reset(reorder(vector, start, median - 1));
        l_Node -> m_RightChild.reset(reorder(vector, median + 1, end));

        if(l_Node -> m_LeftChild.get())
            {l_Node -> m_RightChild -> m_Parent = l_Node;}

        if(l_Node -> m_RightChild.get())
            {l_Node -> m_RightChild -> m_Parent = l_Node;}

        return l_Node;
    };

/** @brief findmin(). */
template<typename KeyType, typename ValueType, class Comparison>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, Comparison>::findmin(Node<std::pair<const KeyType, ValueType>>* l_Node) const noexcept
    {
        if(!l_Node -> m_LeftChild.get()) 
        {   
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nfindmin(): LeftChild doesn't exist [EXIT]\n";

            return l_Node;
        }

        else 
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nfindmin(): LeftChild exists [MOVE LEFT]\n";

            return findmin(l_Node -> m_LeftChild.get());
        }
    };

/** @brief leftmost(). */
template<typename KeyType, typename ValueType, class Comparison>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, Comparison>::leftmost(Node<std::pair<const KeyType, ValueType>>* l_Node) const noexcept
    {
        if(!l_Node -> m_RightChild) 
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nleftmost(): RightChild doesn't exist [EXIT]\n";
            return l_Node -> m_Parent;}

        else 
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_)
            std::cout << "\nleftmost(): RightChild exists [MOVE RIGHT]\n";
            return findmin(l_Node -> m_RightChild.get());}
    };