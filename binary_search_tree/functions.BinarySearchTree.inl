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
        
        if(itr.getCurrentNode() == nullptr) {return;}
        
        /**<  A pointer to the (current) node of the iterator "itr". */
        node_t* p_Node = itr.getCurrentNode(); 
        /**<  A pointer to the parent of the (current) node "p_Node". */
        node_t* p_GrandParent = p_Node -> m_Parent;

        if(p_Node == m_Root.get())
        {
            std::cout << "p_node è la root\n";
            int check_right = 0; 
            int check_left = 0;

            std::cout << "p_Node addr (root): " << p_Node << "\n";
            std::cout << "p_Node: " << p_Node->m_Data.first << "\n";
            if(p_Node -> m_RightChild != nullptr)
            {
                std::cout << "exist the right child!\n";
                check_right = 1;
                ++itr;

                std::cout << "itr addr: " << itr.getCurrentNode() << "\n";
                std::cout << "itr: " << itr.getCurrentNode()->m_Data.first << "\n";
                
                if(itr.getCurrentNode() != p_Node -> m_RightChild.get())
                {
                    if(itr.getCurrentNode() -> m_RightChild != nullptr)
                    {
                        p_Node -> m_RightChild -> m_LeftChild.release();
                        p_Node -> m_RightChild -> m_LeftChild.reset(itr.getCurrentNode()-> m_RightChild.get());
                        itr.getCurrentNode() -> m_RightChild -> m_Parent = p_Node -> m_RightChild.get();
                    }

                    p_Node -> m_RightChild -> m_Parent = itr.getCurrentNode();
                    itr.getCurrentNode() -> m_RightChild.release();
                    itr.getCurrentNode() -> m_RightChild.reset(p_Node -> m_RightChild.get());
                }
                
                if(p_Node -> m_LeftChild != nullptr)
                {
                    p_Node -> m_LeftChild -> m_Parent = itr.getCurrentNode();
                    itr.getCurrentNode() -> m_LeftChild.release();
                    itr.getCurrentNode() -> m_LeftChild.reset(p_Node -> m_LeftChild.get());
                }
                
                if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_LeftChild.get())
                {
                    itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();
                }
                
                itr.getCurrentNode() -> m_Parent = p_GrandParent;
                std::cout << "itr new parent: " << itr.getCurrentNode()-> m_Parent << "\n";
            }           
            else if(p_Node -> m_LeftChild != nullptr)
            {
                std::cout << "exist the left child!\n";
                check_left = 1;
                p_Node -> m_LeftChild -> m_Parent = p_GrandParent;
            }
            
            m_Root.release();
            std::cout << "root addr: " << m_Root.get() << "\n";
            std::cout << "p_Node addr: " << p_Node << "\n";
            std::cout << "p_Node->m_RightChild addr: " << p_Node->m_RightChild.get() << "\n";
            std::cout << "p_Node->m_LeftChild addr: " << p_Node->m_LeftChild.get() << "\n";

            if(check_right == 1)
            {
                std::cout << "check_right\n";
                m_Root.reset(itr.getCurrentNode());
                std::cout << "p_Node addr: " << p_Node << "\n";
                std::cout << "root new addr: " << m_Root.get() << "\n";
                std::cout << "itr addr: " << itr.getCurrentNode() << "\n";
            }
            else if(check_left == 1)
            {
                std::cout << "check_left\n";
                m_Root = std::move(p_Node->m_LeftChild);
                std::cout << "p_Node addr: " << p_Node << "\n";
                std::cout << "root new addr: " << m_Root.get() << "\n";
                std::cout << "itr addr: " << itr.getCurrentNode() << "\n";
            }
        }
        else 
        {
            std::cout << "p_non non è la root\n";
            if (p_Node -> m_RightChild != nullptr)
            {
                ++itr; 
                std::cout << "esiste il figlio di destra\n";
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {
                    /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                   std::cout << "p_node è il figlio di destra di suo padre\n";
                   if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_RightChild.get())
                   {
                       std::cout << "itr è il figlio destro di suo padre (p_node)\n";
                       itr.getCurrentNode() -> m_Parent -> m_RightChild.release();
                       std::cout << "p_ node rilascia itr\n";
                   }
                   else
                   {
                       std::cout << "itr è il figlio sinistro di suo padre (p_node)\n";
                       itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();   
                       std::cout << "p_ node rilascia itr\n";                
                   }

                    std::cout << "nonno rilascia figlio destro (p_node)\n";
                    p_GrandParent -> m_RightChild.release();
                    std::cout << "nonno adotta itr come figlio destro\n";
                    p_GrandParent -> m_RightChild.reset(itr.getCurrentNode());
                }
                else
                {
                    /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                    std::cout << "p_node è il figlio di sinistra di suo padre\n";
                    if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_RightChild.get())
                    {
                        std::cout << "itr è figlio destro di suo padre\n";
                        itr.getCurrentNode() -> m_Parent -> m_RightChild.release();
                        std::cout << "padre di itr ha rilasciato suo figlio destro (itr)\n";
                    }
                    else
                    {
                        std::cout << "itr è figlio sinistro di suo padre\n";
                        itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();
                        std::cout << "padre di itr ha rilasciato suo figlio sinistro (itr)\n";
                    }

                    std::cout << "nonno rilascia figlio sinistro (p_node)\n";
                    p_GrandParent -> m_LeftChild.release();
                    std::cout << "nonnno adotta itr come figlio sinistro\n";
                    p_GrandParent -> m_LeftChild.reset(itr.getCurrentNode());
                } 

                std::cout << "itr riconosce nonno come padre\n";
                itr.getCurrentNode() -> m_Parent = p_GrandParent;
            
                /**< Checking if the current node is my right child. */
                if(p_Node -> m_RightChild != nullptr && itr.getCurrentNode() != p_Node -> m_RightChild.get())
                {
                    std::cout << "p_node ha ancora figlio a destra e non è itr\n";
                    p_Node -> m_RightChild -> m_Parent = itr.getCurrentNode();
                    std::cout << "il figlio destro di p_node ha riconosciuto itr come padre\n";
                    itr.getCurrentNode() -> m_RightChild.release();
                    std::cout << "itr ha rilasciato il figlio destro\n";
                    itr.getCurrentNode() -> m_RightChild.reset(p_Node -> m_RightChild.get());
                    std::cout << "itr ha adottato il figlio destro di p_node\n";
                    p_Node -> m_RightChild.release();
                    std::cout << "p_node ha rilasciato il figlio destro\n";
                }

                if(p_Node -> m_LeftChild != nullptr)
                {
                    std::cout << "p_node ha anche un figlio sinistro\n";
                    itr.getCurrentNode() -> m_LeftChild.release();
                    std::cout << "itr ha rilasciato figlio sinistro\n";
                    itr.getCurrentNode() -> m_LeftChild.reset(p_Node -> m_LeftChild.get());
                    std::cout << "itr ha adottato figlio sinistro di p_Node\n";
                    p_Node -> m_LeftChild -> m_Parent = itr.getCurrentNode();
                    std::cout << "figlio sinistro di p_Node ha riconosciuto itr come padre\n";
                    p_Node -> m_LeftChild.release();
                    std::cout << "p_node ha rilasciato figlio sinitro\n";
                }
            } 
            else if(p_Node -> m_LeftChild != nullptr)
            { 
                std::cout << "p_node ha solo figlio a sinistra\n";
                p_Node -> m_LeftChild.release();
                std::cout << "p_node rilascia figlio a sinistra\n";
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {   
                    std::cout << "p_node è figlio destro di suo padre (nonno)\n";
                    p_GrandParent -> m_RightChild.release();
                    std::cout << "nonno ha rilasciato figlio destro (p_node)\n";
                    p_GrandParent -> m_RightChild.reset(itr.getCurrentNode());
                    std::cout << "nonno ha adottato itr come figlio destro\n";
                }
                else
                {
                    std::cout << "p_node è il figlio sinistro di suo padre (nonno)\n";
                    p_GrandParent -> m_LeftChild.release();
                    std::cout << "nonno ha rilasciato figlio sinistro (p_node)";
                    p_GrandParent -> m_LeftChild.reset(itr.getCurrentNode()); 
                    std::cout << "nonno ha adottato itr come figlio sinitro\n";                   
                }

                std::cout << "figlio sinistro di p_node riconosce nonno come padre\n";
                p_Node -> m_LeftChild -> m_Parent = p_GrandParent;
            }        
            else
            {
                std::cout << "p_node non ha figli\n";
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {p_GrandParent -> m_RightChild.release();}
                
                else
                {p_GrandParent -> m_LeftChild.release();}
                std::cout << "il nonno ha rilasciato p_node\n";
            }
        }

        std::cout << "p_node si isola\n";
        p_Node->m_Parent = nullptr;
        p_Node->m_RightChild.release();
        p_Node->m_LeftChild.release();

        std::cout << "p_node viene eliminato\n";
        delete p_Node;
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
        std::vector<node_t*> array{};

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nbalance(): [CALLED]\n";

        for(iterator itr{begin()}; itr != end(); ++itr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
                std::cout << itr.getCurrentNode() -> m_Data.first << "\t";

                array.push_back(itr.getCurrentNode());    
            };

            if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
            std::cout << std::endl;

        m_Root.release();
        m_Root.reset(order(array, 0, array.size() - 1));
        m_Root -> m_Parent = nullptr;
    };

/** @brief clear() */
template<typename KeyType, typename ValueType, class ComparyType>
void BinarySearchTree<KeyType, ValueType, ComparyType>::clear() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        std::cout << "\nclear(): Root set to nullptr\n";

        std::cout << "(CLEAR) reset root adr: " << m_Root.get() << "\n";
        m_Root.reset(nullptr);
    };
