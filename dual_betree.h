#include <iostream>
#include <vector>
#define TTYPE int
#ifndef DUALBETREE_H
#define DUALBETREE_H
#include "betree.h"

template <typename _Key, typename _Value>
class DualBeTree
{
    public:
    BeTree<_Key, _Value>* sorted;
    BeTree<_Key, _Value>* unsorted;
    _Key tail_min;
    _Key tail_max;
    std::pair<_Key, _Value> outlier;
    uint sorted_size;
    uint unsorted_size;

public:
    /**
     * Purpose: basic constructor that initializes all data members. 
     * Param: data (key-value pairs), buffer_size
     * returns: N/A
     */
    DualBeTree();

    /**
    * Purpose: insert key value pair to dual bplus tree
    * Param: key, value
    * returns: N/A
    */
    bool insert(_Key key, _Value value);

   /**
     * Purpose: Query a key using the dual bplus tree 
     * Param: Key to be queried  
     * returns: True if element is found, else returns false 
     */
    bool query(_Key key);

    void analysis();

};
#endif
