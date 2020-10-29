/**
    @file    Iterator.h
    @brief   Header file for class Iterator
    @authors Victor Plesco, Pietro Morichetti
    @date    01/01/1970
*/

#ifndef _ITERATOR_h
#define _ITERATOR_h

template<class NodeType, typename PairType>
class Iterator
{	

    typedef NodeType node_t;
    typedef PairType pair_t;
    typedef Iterator iterator;
    

    /* ########################################################################################################################################################################### */
    /* ## Iterator: Object ####################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public: 

        /** @brief POINTER to the curent node. */
        node_t* m_CurrentNode = nullptr; 


    /* ########################################################################################################################################################################### */
    /* ## Iterator: Constructor ################################################################################################################################################## */
    /* ########################################################################################################################################################################### */


    public: 

        /** @brief DEFAULT CTOR. @see NONE */
        Iterator() = delete;

        /** @brief DEEP COPY CTOR. @see NONE */
        Iterator (const iterator& other) = delete;

        /** 
         * @brief MOVE CTOR. Constructs a new iterator given an existing iterator.
         * @param other const rvalue reference to an existing iterator or nullptr. 
         * @see 
         */
        Iterator (iterator&& other) noexcept : m_CurrentNode{std::move(other.m_CurrentNode)}
        {if(_ITERATOR_CHECK_CONSTRUCTORS_) std::cout << "\nIterator: move ctor\n";};

        /** 
         * @brief OVERLOADED CTOR. Constructs a new iterator given a pointer to a node.
         * @param other pointer to a node or nullptr.
         * @see 
         */
        explicit Iterator (node_t* other) noexcept : m_CurrentNode{other}
        {if(_ITERATOR_CHECK_CONSTRUCTORS_) std::cout << "\nIterator: overloaded (node_t* other) ctor\n";};

        /** @brief DESTRUCTOR. */
        ~Iterator () noexcept {if(_ITERATOR_CHECK_CONSTRUCTORS_) std::cout << "\nIterator: destructor\n";};


    /* ########################################################################################################################################################################### */
    /* ## Iterator: Operator ##################################################################################################################################################### */
    /* ########################################################################################################################################################################### */


    public:

        /**
         * @brief PRE-INCREMENT(++) operator. In an in-order traversal, we visit a node only after visiting all of its left descendents.
         * @return iterator&: reference to an iterator.
         * @see
         */
        iterator& operator++ () noexcept
        {
            if(_ITERATOR_CHECK_OPERATORS_)
            std::cout << "\nIterator: [operator++]\n";

            if(m_CurrentNode -> m_RightChild.get())
            {
                if(_ITERATOR_CHECK_OPERATORS_)
                std::cout << "\nIterator::operator++: RightChild exists [MOVE RIGHT]\n";

                node_t* p_Node = m_CurrentNode -> m_RightChild.get();
                
                while(p_Node -> m_LeftChild.get()) 
                {
                    if(_ITERATOR_CHECK_OPERATORS_)
                    std::cout << "\nIterator::operator++: LeftChild exists [MOVE LEFT]\n";

                    p_Node = p_Node -> m_LeftChild.get();
                }
                
                if(_ITERATOR_CHECK_OPERATORS_)
                std::cout << "\nIterator::operator++: LeftChild doesn't exist [STOP]\n";

                m_CurrentNode = p_Node;
            }

            else
            {
                if(_ITERATOR_CHECK_OPERATORS_)
                std::cout << "\nIterator::operator++: RightChild doesn't exist [MOVE UP]\n";

                node_t* p_Node = m_CurrentNode;
                
                while(p_Node -> m_Parent && p_Node -> m_Parent -> m_LeftChild.get() != p_Node) 
                {
                    if(_ITERATOR_CHECK_OPERATORS_)
                    std::cout << "\nIterator::operator++: LeftChild exists [MOVE UP]\n";

                    p_Node = p_Node -> m_Parent;
                }

                if(_ITERATOR_CHECK_OPERATORS_)
                std::cout << "\nIterator::operator++: LeftChild doesn't exist [STOP]\n";

                m_CurrentNode = p_Node -> m_Parent;
            }

            return *this;
        };

        /**
         * @brief COPY ASSIGNMENT(=) operator.
         * @param other const lvalue reference to an iterator.
         * @return iterator&: reference to an iterator.
         * @see
         */
        iterator& operator= (const iterator& other) = delete;

        /**
         * @brief MOVE ASSIGNMENT(=) operator.
         * @param other rvalue reference to an iterator.
         * @return iterator&: reference to an iterator.
         * @see
         */
        iterator& operator= (iterator&& other) noexcept
        {
            if(_ITERATOR_CHECK_OPERATORS_)
            std::cout << "\nIterator: [operator=] MOVE\n";

            m_CurrentNode = std::move(other.m_CurrentNode);
            return *this;
        };

        /**
         * @brief BOOLEAN EQUALITY(==) operator.
         * @param other const lvalue reference to an iterator.
         * @return bool: TRUE for EQUALITY, FALSE for INEQUALITY.
         * @see
         */
        bool operator== (const iterator& other) const noexcept
        {
            if(_ITERATOR_CHECK_OPERATORS_)
            std::cout << "\nIterator: [operator==]\n";

            return other.m_CurrentNode == m_CurrentNode;
        };

        /**
         * @brief BOOLEAN INEQUALITY(!=) operator.
         * @param other const lvalue reference to an iterator.
         * @return bool: TRUE for INEQUALITY, FALSE for EQUALITY.
         * @see
         */
        bool operator!= (const iterator& other) const noexcept
        {
            if(_ITERATOR_CHECK_OPERATORS_)
            std::cout << "\nIterator: [operator!=]\n";

            return !(other.m_CurrentNode == m_CurrentNode);
        };

        /**
         * @brief DEREFERENCE(*) operator.
         * @return reference to a tuple(Key, Value).
         * @see
         */
        pair_t& operator* () const noexcept
        {
            if(_ITERATOR_CHECK_OPERATORS_)
            std::cout << "\nIterator: [operator*]\n";

            return m_CurrentNode -> m_Data;
        };

};

#endif