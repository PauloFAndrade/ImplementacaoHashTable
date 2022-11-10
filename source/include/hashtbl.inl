#include "hashtbl.h"

namespace ac {
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( size_type sz)
	{
        m_count = 0;
        m_size = find_next_prime(sz);
        mpDataTable = new std::list<entry_type>[m_size];
	}

    /// Copy constructor
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( const HashTbl& source )
	{
        if(source.mpDataTable!=NULL){
            m_count=source.size();
            m_size=source.m_size;
            mpDataTable=new std::list<entry_type>[m_size];
            for(int i=0;i<m_size;i++){
                mpDataTable[i]=source.mpDataTable[i];
            }
        }
	}

    /// Initializer constructor
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::HashTbl( const std::initializer_list<entry_type>& ilist )
    {
        mpDataTable=new std::list<entry_type>[ilist.size()];
        m_count=0;
        m_size=ilist.size();
        for(auto i : ilist){
            insert(i.m_key,i.m_data);
        }
    }

    /// Assignment operator.
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>&
    HashTbl<KeyType,DataType,KeyHash,KeyEqual>::operator=( const HashTbl& clone )
    {
        
        if(this!=&clone){
            if(clone.mpDataTable!=NULL){
                delete[] mpDataTable;
            }
            if(clone.mpDataTable!=NULL){
                m_count=clone.size();
                m_size=clone.m_size;
                mpDataTable=new std::list<entry_type>[m_size];
                for(int i=0;i<m_size;i++){
                    mpDataTable[i]=clone.mpDataTable[i];
                }
            }
        }
        return *this;
    }

    /// Assignment initializer list.
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>&
    HashTbl<KeyType,DataType,KeyHash,KeyEqual>::operator=( const std::initializer_list< entry_type >& ilist )
    {
        if(ilist.size()!=0){
            delete[] mpDataTable;
        }
        if(ilist.size()!=0){
            m_count=0;
            m_size=ilist.size();
            mpDataTable=new std::list<entry_type>[m_size];
            for(auto i : ilist){
                insert(i.m_key,i.m_data);
            }
        }
        return *this;
    }


	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	HashTbl<KeyType,DataType,KeyHash,KeyEqual>::~HashTbl( )
	{
        delete [] mpDataTable;
	}

    template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	void HashTbl<KeyType,DataType,KeyHash,KeyEqual>::max_load_factor(float mlf){
        m_max_load_factor = mlf;
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
	bool HashTbl<KeyType,DataType,KeyHash,KeyEqual>::insert(const KeyType & key_,const DataType & new_data_ )
    {
        if(m_count == m_size){
            rehash();
        }
        KeyHash hashFunc;
        entry_type new_entry(key_, new_data_);

        auto end{hashFunc(key_) % m_size};
        
        bool x = false;

        auto & currentList = mpDataTable[end];
        int contador = -1;
        for(auto &i : currentList){
            if(i.m_key == key_){
                x = true;
                contador++;
            }
        }
        if(x){
            at(key_) = new_entry.m_data;
            return false;
        }
        mpDataTable[end].push_back(new_entry);

        m_count++;
        return true;
    }
	
    //! Clears the data table.
    template <typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
    void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear()
    {   
        for(size_t index{0}; index < m_size; index++){
            mpDataTable[index].clear();
        }
        m_count = 0;
    }

    //! Tests whether the table is empty.
    /*!
     * \return true is table is empty, false otherwise.
     */
    template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty() const
    {
        return m_count == 0;
    }

    //----------------------------------------------------------------------------------------
    //! Retrieves data from the table.
    /*! Retrieves a data item from the table, based on the key associated with the data.
     *  If the data cannot be found, false is returned; otherwise, true is returned instead.
     *  \param key_ Data key to search for in the table.
     *  \param data_item_ Data record to be filled in when data item is found.
     *  \return true if the data item is found; false, otherwise.
     */
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & key_, DataType & data_item_ ) const
    {
        
        KeyHash hashFunc;

        auto index{hashFunc(key_) % m_size};

        auto & currentList = mpDataTable[index];

        for(auto &i : currentList){
            if(i.m_key == key_){
                data_item_ = i.m_data;
                return true;
            }
        }

        return false; // This is just a stub. Reaplace it accordinly.
    }

    /// Rehash
    template <typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
    void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash( void )
    {   
        KeyHash hashFunc;
        int x = find_next_prime(2*m_size);
        std::list< entry_type > *auxiliar = new std::list<entry_type>[x];
        for(size_t i{0};i<m_size;i++){
            auto & currentList = mpDataTable[i];
            for(auto &i : currentList){
                int newIndex = hashFunc(i.m_key)%x;
                auxiliar[newIndex].push_back(i);
            }
        }
        mpDataTable = auxiliar;
        m_size = x; 
        max_load_factor((float)m_size/m_count);
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::erase( const KeyType & key_ )
    {   
        KeyHash hashFunc;
        auto index{hashFunc(key_) % m_size};

        auto & currentList = mpDataTable[index];

        auto it = --currentList.begin();
        for(auto &i : currentList){
            it++;
            if(i.m_key == key_){
                currentList.erase(it);
                m_count--;
                return true;
            }
        }
        return false;
    }

    template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl<KeyType,DataType,KeyHash,KeyEqual>::isPrime( size_type  x )
    {
        int div=0;
        for(size_t i{1} ; i<=x ; i++){
            if(x%i==0){
                div++;
            }
        }
        if(div==2){
            return true;
        }
        return false;
    }

    /// Find the next prime >= n_
	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    std::size_t HashTbl<KeyType,DataType,KeyHash,KeyEqual>::find_next_prime( size_type  n_ )
    {
        if(n_ <= 1){
            return 2;
        }
        bool achei = false;
        while(!achei){
            n_++;
            if(isPrime(n_)){
                achei = true;
            }
        }
        return n_;
    }


	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    typename HashTbl< KeyType, DataType, KeyHash, KeyEqual >::size_type
    HashTbl< KeyType, DataType, KeyHash, KeyEqual >::count( const KeyType & key_ ) const
    {
        int count = 0; 
        KeyHash hashFunc;
        auto index{hashFunc(key_) % m_size};
        auto & currentList = mpDataTable[index];
        for(auto &i : currentList){
            count++;
        }
        return count; // Stub
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    DataType& HashTbl<KeyType, DataType, KeyHash, KeyEqual>::at( const KeyType & key_ )
    {   
        KeyHash hashFunc;
        auto index{hashFunc(key_)%m_size};
        for(auto &i : mpDataTable[index]){
            if(key_ == i.m_key){
                return i.m_data;
            }
        }
        throw std::out_of_range("");
    }

	template< typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    DataType& HashTbl<KeyType, DataType, KeyHash, KeyEqual>::operator[]( const KeyType & key_ )
    {
        KeyHash hashFunc;
        auto index{hashFunc(key_)%m_size};
        auto & currentList = mpDataTable[index];
        for(auto &aux : currentList)
        if(aux.m_key == key_){
            return aux.m_data;
        }
        entry_type newEntry{key_,DataType()};
        currentList.push_back(newEntry);
        m_count++;
        return currentList.back().m_data;
    }
} // Namespace ac.
