#include <iostream>
#include <vector>
#ifndef DUALBETREE_H
#define DUALBETREE_H
#include "betree.h"

template <typename _Key, typename _Value>
class DualBeTree
{
    std::vector<std::pair<_Key, _Value>> key_value_pairs;
    BeTree<_Key, _Value> sorted;
    BeTree<_Key, _Value> unsorted;
    uint buffer_size;                        // set to 1 for current version
    _Key buffer_elements;
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
     * Purpose: Query a key using the dual bplus tree 
     * Param: Key to be queried  
     * returns: True if element is found, else returns false 
     */
    bool query(_Key key); // TODO: what is the return type: bool or _Value?

     /**
     * Purpose: Query a range of key using the dual bplus tree 
     * Param: range to be queried  
     * returns: vector of keys within the range
     */
    std::vector<std::pair<_Key, _Value>> rangeQuery(_Key low, _Key high, BeTraits &traits);
};
#endif