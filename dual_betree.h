#include <iostream>
#include <vector>
#include "betree.h"

template <typename _Key, typename _Value>
class DualBeTree
{
    std::vector<std::pair<_Key, _Value>> key_value_pairs;
    BeTree<_Key, _Value> sorted;
    BeTree<_Key, _Value> unsorted;
    uint buffer_size;                        // set to 1 for current version
    // std::vector<_Key> buffer_elements;   // TODO: inserted by key or value?

public:
    /**
     * Purpose: basic constructor that initializes all data members. 
     * Param: data (key-value pairs), buffer_size
     * returns: N/A
     */
    DualBeTree(std::vector<std::pair<_Key, _Value>> _key_value_pairs, uint _buffer_size);

    /**
    * Purpose: builds the dual bplus tree given kv pairs
    * Param: N/A
    * returns: N/A
    */
    void build();

   /**
     * Purpose: Query a key using the zonemap 
     * Param: Key to be queried  
     * returns: True if element is found, else returns false 
     */
    _Value query(_Key key); // TODO: what is the return type: bool or _Value?

}