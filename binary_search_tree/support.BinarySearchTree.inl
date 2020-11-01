/**
    @file    support.BinarySearchTree.inl 
    @brief   Inline file for support functions of class BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    05/03/2020
    @version 2.1
*/

/** @brief copy(). */
template<typename KeyType, typename ValueType, class CompareType>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, CompareType>::copy(const node_t* p_Me, node_t* p_Parent)
{
    if(p_Me == nullptr) {return 0;}

    node_t* p_Node = new node_t{p_Me -> m_Data};
    p_Node -> m_Parent = p_Parent;

    if(p_Me -> m_RightChild.get() != nullptr)
    {p_Node -> m_RightChild.reset(copy(p_Me -> m_RightChild.get(), p_Node));}

    if(p_Me -> m_LeftChild.get() != nullptr)
    {p_Node -> m_LeftChild.reset(copy(p_Me -> m_LeftChild.get(), p_Node));}

    return p_Node;
};

/** @brief sink(). */
template<typename KeyType, typename ValueType, class CompareType>
std::pair<Node<std::pair<const KeyType, ValueType>>*, typename BinarySearchTree<KeyType, ValueType, CompareType>::kin> 
BinarySearchTree<KeyType, ValueType, CompareType>::sink(node_t* p_Root, const KeyType& l_Key)
    {
        if(LESS(l_Key, p_Root -> m_Data.first))
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
            std::cout << "\nsink(): Key is smaller [CHECK LEFTCHILD]\n";

            if(p_Root -> m_LeftChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
                std::cout << "\nsink(): LeftChild exists [MOVE LEFT]\n";

                return sink(p_Root -> m_LeftChild.get(), l_Key);
            }
                        if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
                        std::cout << "\nsink(): LeftChild doesn't exist [STOP]\n";

                        return std::make_pair(p_Root, kin::go_left);
        }

        else if(LESS(p_Root -> m_Data.first, l_Key))
        {
            if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
            std::cout << "\nsink(): Key is bigger [CHECK RIGHTCHILD]\n";

            if(p_Root -> m_RightChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
                std::cout << "\nsink(): RightChild exists [MOVE RIGHT]\n";

                return sink(p_Root -> m_RightChild.get(), l_Key);
            }
                        if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
                        std::cout << "\nsink(): RightChild doesn't exist [STOP]\n";

                        return std::make_pair(p_Root, kin::go_right);
        }

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_SINKED_)
        std::cout << "\nsink(): Key exists [STOP]\n";

        return std::make_pair(p_Root, kin::equal);
    };

/** @brief order(). */
template<typename KeyType, typename ValueType, class CompareType>
Node<std::pair<const KeyType, ValueType>>*
BinarySearchTree<KeyType, ValueType, CompareType>::order(const std::vector<node_t*>& array, const KeyType& start, const KeyType& end) const noexcept
    {       
        if(LESS(end, start)) {return nullptr;}

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_) {std::cout << "\n[ORDER CALLED]\n";}
        
        const KeyType median{(start + end)/2};        
        node_t* l_Node{array[median]};

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_) {std::cout << "[ORDER] l_Node is the median for the actual array\n";}

        l_Node -> m_RightChild.release();
        l_Node -> m_LeftChild.release();

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_) {std::cout << "[ORDER] l_Node RightChild and LeftChild released\n";}

        l_Node -> m_RightChild.reset(order(array, median + 1, end));
        l_Node -> m_LeftChild.reset(order(array, start, median - 1));

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_) {std::cout << "[ORDER] l_Node RightChild and LeftChild resetted\n";}

        if(l_Node -> m_RightChild.get()) {l_Node -> m_RightChild -> m_Parent = l_Node;}
        if(l_Node -> m_LeftChild.get())  {l_Node -> m_LeftChild  -> m_Parent = l_Node;}

        if(_BINARYSEARCHTREE_CHECK_SUPPORT_ORDER_) 
        {
            std::cout << "[ORDER] new l_Node RightChild and LeftChild recognised l_Node us Parent\n"
                      << "[ORDER ENDED]\n";
        }
        
        return l_Node;
    };
