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
    uint tree_min;
    uint sum;
    uint fail;
    int num_sd;
    // int failThres;
    float ss;
    float sd;


public:
    /**
     * Purpose: basic constructor that initializes all data members. 
     * Param: data (key-value pairs), buffer_size
     * returns: N/A
     */
    DualBeTree(int _num_sd);

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
        // if (this->fail > this->failThres) {
        //     this->num_sd = this->num_sd * 2;
        // }
        // std::cout<< "key = "<<key<<" bound = "<<this->num_sd * this->sd + this->sum / this->sorted_size<<" sd = "<<this->sd<<std::endl;
        // return key <= (this->num_sd * this->sd + this->sum / this->sorted_size);
        return key <= tail_max+sd;

    }

    void updateSs(_Key key) {
        // this->sum += key;
        // this->ss += key * key;
        // // float new_sd = sqrt((this->sorted_size * this->ss - this->sum * this->sum)/float(this->sorted_size * (this->sorted_size - 1)));
        // float new_sd = );
        // if (new_sd > 1) {
        //     this->sd = new_sd;
        // }
    
        sd = (tail_max - tail_min)/sqrt(12);

        if(sd<sqrt(12)){
            if(tail_max == tail_min && tail_max > sqrt(12) && sorted_size!= 1){
                sd = (tail_max - tree_min)/sqrt(12);
            }else{
                sd = sqrt(12);
                // sd = 1;
            }
        }
        // std::cout << "key = " << key << " stdev = " << this->sd <<" sorted_size = "<<sorted_size <<" tail_max = "<<tail_max << std::endl;

    }
};
#endif
