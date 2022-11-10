// @author: Selan
//
#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>     // cout, endl, ostream
#include <forward_list> // forward_list
#include <algorithm>    // copy, find_if, for_each
#include <cmath>        // sqrt
#include <iterator>     // std::begin(), std::end()
#include <initializer_list>
#include <utility> // std::pair
#include <list>

namespace ac // Associative container
{
	template<class KeyType, class DataType>
	struct HashEntry {
        KeyType m_key;   //! Data key
        DataType m_data; //! The data

        // Regular constructor.
        HashEntry( KeyType kt_, DataType dt_ ) : m_key{kt_} , m_data{dt_}
        {/*Empty*/}

        friend std::ostream & operator<<( std::ostream & os_, const HashEntry & he_ ) {
            // os_ << "{" << he_.m_key << "," << he_.m_data << "}";
            os_ << he_.m_data;
            return os_;
        }
    };

	template< class KeyType,
		      class DataType,
		      class KeyHash = std::hash< KeyType >,
		      class KeyEqual = std::equal_to< KeyType > >
	class HashTbl {
        public:
            // Aliases
            using entry_type = HashEntry<KeyType,DataType>;
            using list_type = std::forward_list< entry_type >;
            using size_type = std::size_t;

            /**
             * @brief Construct a new Hash Tbl object with DEFAULT_SIZE or the next prime after "table_sz_"
             * 
             * @param table_sz_ HashTbl size
             */
            explicit HashTbl( size_type table_sz_ = DEFAULT_SIZE );
            
            /**
             * @brief Construct a new Hash Tbl object with a copy of each of the elements in other object
             * 
             */
            HashTbl( const HashTbl& );
            
            /**
             * @brief Construct a new Hash Tbl object with a copy of each of the elements in initializer list
             * 
             */
            HashTbl( const std::initializer_list< entry_type > & );
            
            
            /**
             * @brief Copies all the elements from the object passed as argument into the hash table.
             * 
             * @return HashTbl& hashtbl after copy
             */
            HashTbl& operator=( const HashTbl& );
            
            /**
             * @brief Copies all the elements from the initializer_list passed as argument into the hash table.
             * 
             * @return HashTbl& hashtbl after copy
             */
            HashTbl& operator=( const std::initializer_list< entry_type > & );

            /**
             * @brief Destroy the Hash Tbl object
             * 
             */
            virtual ~HashTbl();

            /**
             * @brief Inserts into the table the information contained in second argument and associated with a key(first argument).
             * 
             * @return true if everything goes well
             * @return false otherwise
             */
            bool insert( const KeyType &, const DataType &  );
            
            /**
             * @brief Retrieves in second argument the information associated with key passed as first argument to the method
             * 
             * @return true if the key is found
             * @return false otherwise
             */
            bool retrieve( const KeyType &, DataType & ) const;
            
            /**
             * @brief Removes a table item identified by its key passed as argument
             * 
             * @return true true if the key is found
             * @return false otherwise
             */
            bool erase( const KeyType & );
            
            /**
             * @brief Clears (erases) all memory associated with the collision lists from the table, removing all its elements
             * 
             */
            void clear();
            
            /**
             * @brief Check if Hash Table is empty
             * 
             * @return true if it's empty
             * @return false if not
             */
            bool empty() const;
            
            /**
             * @brief Returns the number of elements currently stored in the table.
             * 
             * @return size_type number of elements currently stored in the table.
             */
            inline size_type size() const { return m_count; };
            
            /**
             * @brief Returns a reference to the data associated with the given key 
             * 
             * @return DataType& reference to the data associated with the given key
             */
            DataType& at( const KeyType& );
            
            /**
             * @brief Returns a reference to the data associated with the given key, if exist.
             * 
             * @return DataType& reference to the data associated with the given key
             */
            DataType& operator[]( const KeyType& );
            
            /**
             * @brief Returns the number of table elements that are in the associated collision list the key passed as argument
             * 
             * @return size_type number of table elements that are in the associated collision list the key passed as argument
             */
            size_type count( const KeyType& ) const;
            
            /**
             * @brief Returns the load factor value
             * 
             * @return float load factor value
             */
            float max_load_factor() const;
            
            /**
             * @brief Modifies the load factor value
             * 
             * @param mlf the new value
             */
            void max_load_factor(float mlf);

            friend std::ostream & operator<<( std::ostream & os_, const HashTbl & ht_ ) {
                for(size_t i{0};i<ht_.m_size;i++){
                    std::cout << i << ":\n";
                    for(auto it = ht_.mpDataTable[i].begin();it!=ht_.mpDataTable[i].end();it++){
                        std::cout <<"\t"<< *it << std::endl;
                    }
                }
                return os_;
            }
        private:
            
            /**
             * @brief check if "x" is a prime
             * 
             * @param x number that will be checked
             * @return true if it's prime
             * @return false if not
             */
            static bool isPrime(size_type x); 
            
            /**
             * @brief find the next prime number after the number passed as argument
             * 
             * @return size_type next prime after the number passed as argument
             */
            static size_type find_next_prime( size_type );
            
            /**
             * @brief create a new table whose size will be equal to smallest prime number >= 2*(size of hash table) before call function
             * 
             */
            void rehash( void );

        private:
            float m_max_load_factor =1.0;
            size_type m_size; //!< Tamanho da tabela.
            size_type m_count=0;//!< Numero de elementos na tabel.
            //std::unique_ptr< std::forward_list< entry_type > [] > m_table;
            std::list< entry_type > *mpDataTable; //!< Tabela de listas para entradas de tabela.
            //static const short DEFAULT_SIZE = 10;
            static const short DEFAULT_SIZE = 11;
    };

} // MyHashTable
#include "hashtbl.inl"
#endif
