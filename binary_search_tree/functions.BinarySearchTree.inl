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
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_)
        std::cout << "\n\ninsert(): Key " << l_Data.first << "\n\n";
        
        if(m_Root.get() == nullptr)
        {
            m_Root.reset(new node_t{l_Data});

            if(_BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_)
            std::cout << "\ninsert(): Root not found [CREATE ROOT]\n";

                return std::make_pair(iterator{m_Root.get()}, true);
        }

        node_t* p_Root = m_Root.get();
        node_t* p_Node;

        std::pair<node_t*, kin> sinked = sink(p_Root, l_Data.first);

        switch (sinked.second)
        {
            case (equal)   :

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_)
                std::cout << "\ninsert()[switch]: KEY EQUAL [EXIT]\n";
                return std::make_pair(iterator{sinked.first}, false);	
                break;	

            case (go_left) :

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_)
                std::cout << "\ninsert()[switch]: LEFT CHILD [CREATE]\n";
                p_Node = new node_t{l_Data};
                sinked.first -> m_LeftChild.reset(p_Node);
                break;

            case (go_right) :

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_INSERT_)
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
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
        {std::cout << "\n[ERASE CALLED]\n";}

        iterator itr = find(l_Key); 
        
        if(itr.getCurrentNode() == nullptr) {return;}
        
        /**<  A pointer to the (current) node of the iterator "itr". */
        node_t* p_Node = itr.getCurrentNode(); 
        /**<  A pointer to the parent of the (current) node "p_Node". */
        node_t* p_GrandParent = p_Node -> m_Parent;

        if(p_Node == m_Root.get())
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_){std::cout << "[ERASE] target node is the root\n";}

            int check_right = 0; 
            int check_left = 0;
            
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
            {
                std::cout << "[ERASE] p_Node (root) - addr: \n" << p_Node << " value: " << p_Node->m_Data.first << "\n";            
            }
            if(p_Node -> m_RightChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                {
                    std::cout << "[ERASE] exist the right child\n";
                }
                check_right = 1;
                ++itr;

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                {
                    std::cout << "[ERASE] itr - addr: " << itr.getCurrentNode() << " value: " << itr.getCurrentNode()->m_Data.first << "\n";
                }
                
                if(itr.getCurrentNode() != p_Node -> m_RightChild.get())
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] itr is not the p_Node RightChild\n";
                    }
                    if(itr.getCurrentNode() -> m_RightChild != nullptr)
                    {
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                        {
                            std::cout << "[ERASE] itr has a RightChild\n";
                        }
                        p_Node -> m_RightChild -> m_LeftChild.release();
                        p_Node -> m_RightChild -> m_LeftChild.reset(itr.getCurrentNode()-> m_RightChild.get());
                        itr.getCurrentNode() -> m_RightChild -> m_Parent = p_Node -> m_RightChild.get();
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                        {
                            std::cout << "[ERASE] RightChild of p_Node has released it's LeftChild\n" 
                                      << "[ERASE] RightChild of p_Node adopted itr as a LeftChild\n"
                                      << "[ERASE] RightChild of itr recognised RightChild of p_Node as parent\n";
                        }
                    }

                    p_Node -> m_RightChild -> m_Parent = itr.getCurrentNode();
                    itr.getCurrentNode() -> m_RightChild.release();
                    itr.getCurrentNode() -> m_RightChild.reset(p_Node -> m_RightChild.get());
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] RightChild of p_Node recognised itr as parent\n"
                                  << "[ERASE] itr released its RightChild\n"
                                  << "[ERASE] itr adopted ex-p_node RightChild as RightChild\n";
                    }
                }
                
                if(p_Node -> m_LeftChild != nullptr)
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] p_Node has a LeftChild\n";
                    }
                    p_Node -> m_LeftChild -> m_Parent = itr.getCurrentNode();
                    itr.getCurrentNode() -> m_LeftChild.release();
                    itr.getCurrentNode() -> m_LeftChild.reset(p_Node -> m_LeftChild.get());

                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] LeftChild of p_Node recognised itr as parent\n"
                                  << "[ERASE] itr released its LeftChild\n"
                                  << "[ERASE] itr adopted ex-p_Node LeftChild as LeftChild\n";
                    }
                }
                
                if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_LeftChild.get())
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr is not the p_Node LeftChild\n";}
                    itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_){std::cout << "[ERASE] itr released its LeftChild\n";}
                }
                
                itr.getCurrentNode() -> m_Parent = p_GrandParent;
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) 
                {std::cout << "[ERASE] itr new parent addr: " << itr.getCurrentNode()-> m_Parent << "\n";}
            }           
            else if(p_Node -> m_LeftChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node has not a RightChild, but it has a LeftChild\n";}
                
                check_left = 1;
                p_Node -> m_LeftChild -> m_Parent = p_GrandParent;
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] LeftChild of p_Node recognised GranParent as parent";}
            }
            
            m_Root.release();
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
            {
                std::cout << "[ERASE] Root addr: " << m_Root.get() << "\n"
                          << "[ERASE] p_Node addr: " << p_Node << "\n"
                          << "[ERASE] p_Node RightChild addr: " << p_Node->m_RightChild.get() << "\n"
                          << "[ERASE] p_Node LeftChild addr: " << p_Node->m_LeftChild.get() << "\n";
            }

            if(check_right == 1)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) 
                {std::cout << "[ERASE] check_right was true: we can reset Root with itr\n";}
                m_Root.reset(itr.getCurrentNode());
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                {std::cout << "[ERASE] new Root is itr\n";}
            }
            else if(check_left == 1)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) 
                {std::cout << "[ERASE] check_right was false but check_left is true: we can reset Root with itr\n";}
                m_Root = std::move(p_Node->m_LeftChild); //
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                {std::cout << "[ERASE] new Root is p_Node LeftChild\n";}
            }

            if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
            {
                std::cout << "[ERASE] p_Node addr: " << p_Node << "\n"
                          << "root new addr: " << m_Root.get() << "\n"
                          << "itr addr: " << itr.getCurrentNode() << "\n";                    
            }            
        }
        else 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_){std::cout << "[ERASE] p_Node is not the Root\n";}

            if (p_Node -> m_RightChild != nullptr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node has a RightChild\n";}
                ++itr; 
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {
                    /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                   if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node is the RightChild of the GranParent\n";}
                   if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_RightChild.get())
                   {
                       if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr is the p_Node RightCHild\n";}
                       itr.getCurrentNode() -> m_Parent -> m_RightChild.release();
                       if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node released itr\n";}
                   }
                   else
                   {
                       if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node is the LeftChild of the GranParent\n";}
                       itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();  
                       if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] Parent of itr released its LeftChild (itr)\n";} 
                   }

                    p_GrandParent -> m_RightChild.release();
                    p_GrandParent -> m_RightChild.reset(itr.getCurrentNode());
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] GranParent released its RightChild (p_Node)\n"
                                  << "[ERASE] GranParent adopted itr as RightChild\n";
                    }
                }
                else
                {
                    /**< Assign to my parent the current node (so the actual parent of the current node will release his ownership). */
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node is the LeftChild of GranParent\n";}
                    if(itr.getCurrentNode() == itr.getCurrentNode() -> m_Parent -> m_RightChild.get())
                    {
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr is the RightChild\n";}
                        itr.getCurrentNode() -> m_Parent -> m_RightChild.release();
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr Parent released its RightChild (itr)\n";}
                    }
                    else
                    {
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr is the LeftChild\n";}
                        itr.getCurrentNode() -> m_Parent -> m_LeftChild.release();
                        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr Parent released its LeftChild (itr)\n";}
                    }

                    p_GrandParent -> m_LeftChild.release();
                    p_GrandParent -> m_LeftChild.reset(itr.getCurrentNode());
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) 
                    {
                        std::cout << "[ERASE] GranParent released its LeftChild (p_Node)\n"
                                  << "[ERASE] GranParent adopted itr as LeftChild\n";
                    }
                } 

                itr.getCurrentNode() -> m_Parent = p_GrandParent;
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] itr recognised GranParent as its Parent\n";}
            
                /**< Checking if the current node is my right child. */
                if(p_Node -> m_RightChild != nullptr && itr.getCurrentNode() != p_Node -> m_RightChild.get())
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node RightChild exist and it is not itr\n";}
                    
                    p_Node -> m_RightChild -> m_Parent = itr.getCurrentNode();
                    itr.getCurrentNode() -> m_RightChild.release();
                    itr.getCurrentNode() -> m_RightChild.reset(p_Node -> m_RightChild.get());
                    p_Node -> m_RightChild.release();

                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] p_Node RightChild recognised itr as Parent\n"
                                  << "[ERASE] itr released its RightChild\n"
                                  << "[ERASE] itr adopted ex-p_Node RightChild as its RightChild\n"
                                  << "[ERASE] p_Node released its (ex-)RightChild\n";
                    }
                }

                if(p_Node -> m_LeftChild != nullptr)
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node has a LeftChild\n";}
                    itr.getCurrentNode() -> m_LeftChild.release();
                    std::cout << "itr ha rilasciato figlio sinistro\n";
                    itr.getCurrentNode() -> m_LeftChild.reset(p_Node -> m_LeftChild.get());
                    std::cout << "itr ha adottato figlio sinistro di p_Node\n";
                    p_Node -> m_LeftChild -> m_Parent = itr.getCurrentNode();
                    std::cout << "figlio sinistro di p_Node ha riconosciuto itr come padre\n";
                    p_Node -> m_LeftChild.release();
                    std::cout << "p_node ha rilasciato figlio sinitro\n";

                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] itr released its LeftChild\n"
                                  << "[ERASE] itr adopted p_Node LeftChild as its LeftChild\n"
                                  << "[ERASE] p_Node LeftChild recognised itr as Parent\n"
                                  << "[ERASE] p_Node released its (ex-)LeftChild\n";
                    }
                }
            } 
            else if(p_Node -> m_LeftChild != nullptr)
            { 
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node has only a LeftChild\n";}
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {   
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node is the RightChild of GranParent\n";}
                    
                    p_GrandParent -> m_RightChild.release();
                    p_GrandParent -> m_RightChild.reset(p_Node -> m_LeftChild.get());

                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] GranParent released its RightChild (p_Node)\n"
                                  << "[ERASE] GranParent adopted p_Node LeftChild as its RightChild\n";
                    }
                }
                else
                {
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node is the LeftChild of the GranParent\n";}

                    p_GrandParent -> m_LeftChild.release();
                    p_GrandParent -> m_LeftChild.reset(p_Node -> m_LeftChild.get()); 
                    
                    if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
                    {
                        std::cout << "[ERASE] GranParent released its LeftChild (p_Node)\n"
                                  << "[ERASE] GranParent adopted itr as LeftChild\n";
                    }                
                }

                p_Node -> m_LeftChild -> m_Parent = p_GrandParent;
                p_Node -> m_LeftChild.release();

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {
                    std::cout << "[ERASE] p_Node LeftChild recognised GranParent as Parent\n"
                              << "[ERASE] P_Node released its (ex-)LeftChild\n";
                }
            }        
            else
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] p_Node has not children (it is a leaf)\n";}
                if(p_Node == p_GrandParent -> m_RightChild.get())
                {p_GrandParent -> m_RightChild.release();}
                
                else
                {p_GrandParent -> m_LeftChild.release();}

                if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std::cout << "[ERASE] GranParent released its Child (p_Node)\n";}
            }
        }

        p_Node->m_Parent = nullptr;
        p_Node->m_RightChild.release();
        p_Node->m_LeftChild.release();
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_) {std:: cout << "[ERASE] p_Node isolated itself\n";}

        delete p_Node;
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_ERASE_)
        {
            std::cout << "[ERASE] p_Node deleted\n" 
                      << "[ERASE ENDED]\n\n";
        }
    };

/** @brief find() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::find(const KeyType& l_Key)
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
        std::cout << "\nfind(): [CALLED]\n";

        if(m_Root.get() == nullptr) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
            std::cout << "\nfind(): Root doesn't exist [EXIT]\n";
            return iterator{nullptr};
        }

        std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
        if(sinked.second == kin::equal) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
            std::cout << "\nfind(): Key found [EXIT]\n";

            return iterator{sinked.first};
        }

        if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
        std::cout << "\nfind(): Key not found[EXIT]!\n";
        return iterator{nullptr};
    };

/** @brief const find() */
template<typename KeyType, typename ValueType, class ComparyType>
Iterator<Node<std::pair<const KeyType, ValueType>>, const std::pair<const KeyType, ValueType>>
BinarySearchTree<KeyType, ValueType, ComparyType>::find(const KeyType& l_Key) const
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
        std::cout << "\nfind(): [CALLED]\n";

        if(m_Root.get() == nullptr) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
            std::cout << "\nfind(): Root doesn't exist [EXIT]\n";
            return const_iterator{nullptr};
        }

        std::pair<node_t*, kin> sinked = sink(m_Root.get(), l_Key);
        if(sinked.second == kin::equal) 
        {
            if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
            std::cout << "\nfind(): Key found [EXIT]\n";
            return const_iterator{sinked.first};
        }

        if(_BINARYSEARCHTREE_CHECK_FUNCTION_FIND_)
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

        if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_) {std::cout << "\n[BALANCE CALLED]\n";}

        for(iterator itr{begin()}; itr != end(); ++itr)
            {
                if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_)
                std::cout << itr.getCurrentNode() -> m_Data.first << "\t";

                array.push_back(itr.getCurrentNode());    
            };

            if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_)
            std::cout << std::endl;

        m_Root.release();
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_) {std::cout << "[BALANCE] Root released\n";}
        m_Root.reset(order(array, 0, array.size() - 1));
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_) {std::cout << "[BALANCE] Root resetted\n";}
        m_Root -> m_Parent = nullptr;
        if(_BINARYSEARCHTREE_CHECK_FUNCTION_BALANCE_) {std::cout << "[BALANCE ENDED]\n\n";}
    };

/** @brief clear() */
template<typename KeyType, typename ValueType, class ComparyType>
void BinarySearchTree<KeyType, ValueType, ComparyType>::clear() noexcept
    {
        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_)
        {
            std::cout << "[CLEAR CALLED]\n";
            std::cout << "[CLEAR] reset root addr: " << m_Root.get() << "\n";
        }

        m_Root.reset(nullptr);

        if(_BINARYSEARCHTREE_CHECK_FUNCTIONS_) {std::cout << "[CLEAR ENDED]\n\n";}
    };
