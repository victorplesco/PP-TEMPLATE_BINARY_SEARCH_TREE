/**
    @file    functions.BinarySearchTree.inl
    @brief   Inline file for member functions for class BinarySearchTree
    @authors Thomas Deponte, Pietro Morichetti, Victor Plesco
    @date    01/01/1970
*/

/** @brief insert() */
template<typename KeyType, typename ValueType, class CompareType>
std::pair<Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>, bool>
BinarySearchTree<KeyType, ValueType, CompareType>::insert(pair_t&& l_Data)
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

                if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
                std::cout << "\ninsert()[switch]: LEFT CHILD [CREATE]\n";
                p_Node = new node_t{l_Data};
                sinked.first -> m_LeftChild.reset(p_Node);
                break;

            case (go_right) :

                if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
                std::cout << "\ninsert()[switch]: RIGHT CHILD [CREATE]\n";
                p_Node = new node_t{l_Data};
                sinked.first -> m_RightChild.reset(p_Node);
                break;
        };

        p_Node -> m_Parent = sinked.first;
            return std::make_pair(iterator{p_Node}, true);
    };

/** @brief emplace() */
template<typename KeyType, typename ValueType, class ComparyType>
template<class... Args>
std::pair<Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>, bool>
BinarySearchTree<KeyType, ValueType, ComparyType>::emplace(Args&&... args)
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nemplace(): [CALLED]\n";
        return insert(pair_t{std::forward<Args>(args)...});
    };

/** @brief erase() */
template<typename KeyType, typename ValueType, class ComparyType>
void BinarySearchTree<KeyType, ValueType, ComparyType>::erase(const KeyType& l_Key) 
    {
        iterator itr = find(l_Key); 
        
        if(itr.m_CurrentNode == nullptr) {return;}
        
        /**<  A pointer to the (current) node of the iterator "itr". */
        node_t* p_Node = itr.m_CurrentNode; 
        /**<  A pointer to the parent of the (current) node "p_Node". */
        node_t* p_GrandParent = itr.m_CurrentNode -> m_Parent;
        
        if(p_Node -> m_RightChild != nullptr)
        {
            ++itr; 

            if(p_Node == p_GrandParent -> m_RightChild.get())
            {
                /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                p_GrandParent -> m_RightChild = (itr.m_CurrentNode == itr.m_CurrentNode -> m_Parent -> m_RightChild.get()) ? 
                    std::move(itr.m_CurrentNode -> m_Parent -> m_RightChild) : std::move(itr.m_CurrentNode -> m_Parent -> m_LeftChild);
            }
            
            else  // CHECK ! //
            {
                /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                p_GrandParent -> m_LeftChild = (itr.m_CurrentNode == itr.m_CurrentNode -> m_Parent -> m_RightChild.get()) ? 
                    std::move(itr.m_CurrentNode -> m_Parent -> m_RightChild) : std::move(itr.m_CurrentNode -> m_Parent -> m_LeftChild);
            } 
        
            itr.m_CurrentNode -> m_Parent = p_GrandParent;
        
            /**< Checking if the current node is my right child. */
            if(p_Node -> m_RightChild != nullptr && itr.m_CurrentNode != p_Node -> m_RightChild.get())
            {
                p_Node -> m_RightChild -> m_Parent = itr.m_CurrentNode;
                itr.m_CurrentNode -> m_RightChild = std::move(p_Node -> m_RightChild);
            }
        
            if(p_Node -> m_LeftChild != nullptr)
            {
                p_Node -> m_LeftChild -> m_Parent = itr.m_CurrentNode;
                itr.m_CurrentNode -> m_LeftChild = std::move(p_Node -> m_LeftChild);
            }
        } 
        
        else if(p_Node -> m_LeftChild != nullptr)
        { 
            if(p_Node == p_GrandParent -> m_RightChild.get())
            {p_GrandParent -> m_RightChild = std::move(p_Node -> m_LeftChild);}
            
            else
            {p_GrandParent -> m_LeftChild = std::move(p_Node -> m_LeftChild);}
        
            p_Node -> m_LeftChild -> m_Parent = p_GrandParent;
        }
        
        else
        {
            if(p_Node == p_GrandParent -> m_RightChild.get())
            {p_GrandParent -> m_RightChild.release();}
            
            else
            {p_GrandParent -> m_LeftChild.release();}
        }
    };

/** @brief find() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::find(const KeyType& l_Key)
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nfind(): [CALLED]\n";

        if(m_Root.get() == nullptr) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nfind(): Root doesn't exist [EXIT]\n";
            return iterator{nullptr};
        }

        std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
        if(sinked.second == kin::equal) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nfind(): Key found [EXIT]\n";
            return iterator{sinked.first};
        }

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nfind(): Key not found[EXIT]!\n";
        return iterator{nullptr};
    };

/** @brief const find() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::find(const KeyType& l_Key) const
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nfind(): [CALLED]\n";

        if(m_Root.get() == nullptr) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nfind(): Root doesn't exist [EXIT]\n";
            return const_iterator{nullptr};
        }

        std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
        if(sinked.second == kin::equal) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << "\nfind(): Key found [EXIT]\n";
            return const_iterator{sinked.first};
        }

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nfind(): Key not found[EXIT]!\n";
        return const_iterator{nullptr};
    };

/** @brief end() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::end() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nend(): [CALLED]\n";
        
        return iterator{nullptr};
    };

/** @brief const end() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::end() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nconst end(): [CALLED]\n";

        return const_iterator{nullptr};
    };

/** @brief cend() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::cend() const noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\ncend(): [CALLED]\n";

        return const_iterator{nullptr};
    };

/** @brief begin() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::begin() noexcept
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
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::begin() const noexcept
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
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::cbegin() const noexcept
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
template<typename KeyType, typename ValueType, class ComparyType>
void BinarySearchTree<KeyType, ValueType, ComparyType>::balance()
    {
        if(m_Root == nullptr) {return;}
        std::vector<node_t*> array;

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nbalance(): [CALLED]\n";

        for(iterator itr{begin()}; itr != end(); ++itr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
                std::cout << itr.m_CurrentNode -> m_Data.first;

                array.push_back(itr.m_CurrentNode);    
            };

        m_Root.reset(order(array, 0, array.size() - 1));
        m_Root -> m_Parent = nullptr;
    };

/** @brief clear() */
template<typename KeyType, typename ValueType, class ComparyType>
void BinarySearchTree<KeyType, ValueType, ComparyType>::clear() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nclear(): Root set to nullptr\n";

        m_Root.reset(nullptr);
    };
