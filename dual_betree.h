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
    uint fail;
    int num_sd;
    int failThres;
    float ss;
    float sd;


public:
    /**
     * Purpose: basic constructor that initializes all data members. 
     * Param: data (key-value pairs), buffer_size
     * returns: N/A
     */
    DualBeTree(int _num_sd, int _failThres);

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

    bool outlierCheck(_Key key) {
        if (this->fail > this->failThres) {
            this->num_sd = this->num_sd * 2;
        }
        return key <= (this->num_sd * this->sd + this->sum / this->sorted_size);
    }

    void updateSs(_Key key) {
        this->sum += key;
        this->ss += key * key;
        float new_sd = sqrt((this->sorted_size * this->ss - this->sum * this->sum)/float(this->sorted_size * (this->sorted_size - 1)));
        if (new_sd > 1) {
            this->sd = new_sd;
        }
        // std::cout << "key = " << key << " stdev = " << this->sd << std::endl;
    }
};
#endif
