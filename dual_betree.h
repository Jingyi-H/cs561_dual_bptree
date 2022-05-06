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
    bool insert(_Key key, _Value value);

   /**
     * Purpose: Query a key using the dual bplus tree 
     * Param: Key to be queried  
     * returns: True if element is found, else returns false 
     */
    bool query(_Key key);

    void analysis();

    bool outlierCheck(_Key key) {
        //check if key is out of bound
        return key <= tail_max+sd;

    }

    void updateSs(_Key key) { 
        //update sd if tail leaf size > 1 and sorted tree size >1
        if(tail_max != tail_min && sorted_size!= 1){
            sd = (tail_max - tail_min)/sqrt(12);
        }
        //if sd<default vlaue set it to default value
        if(sd<sqrt(12)){
            sd = sqrt(12);
        }      
        // std::cout << "key = " << key << " stdev = " << this->sd <<" sorted_size = "<<sorted_size <<" tail_max = "<<tail_max <<" tail_min = "<<tail_min<<std::endl;
    }
    
};
#endif
