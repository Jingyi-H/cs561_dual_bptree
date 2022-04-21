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
    uint sorted_size;
    uint unsorted_size;
    uint sum;
    float ss;
    float sd;

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
    bool insert(_Key key, _Value value, int num_sd);

   /**
     * Purpose: Query a key using the dual bplus tree 
     * Param: Key to be queried  
     * returns: True if element is found, else returns false 
     */
    bool query(_Key key);

    void analysis();

    bool outlierCheck(_Key key, int num_sd) {
        return key <= (num_sd * this->sd + this->tail_max);
    }
};
#endif
