#include "dual_betree.h"
#define DEFAULT -1

template <typename _Key, typename _Value>
DualBeTree<_Key, _Value>::DualBeTree()
{
    // constructor
    BeTree<_Key, _Value> sorted("sortedT", "./tree_dat", 4096, 10000);
    BeTree<_Key, _Value> unsorted("unsortedT", "./tree_dat", 4096, 10000);
    this->sorted = sorted;
    this->unsorted =  unsorted;
    this->last_element = DEFAULT;
    
}

template <typename _Key, typename _Value>
void DualBeTree<_Key, _Value>::insert(_Key key, _Value value) {
    /** build dual bplus tree
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    if (key < this->last_element) {
        this->unsorted.insert(key, value);
    } else {
        this->sorted.insert_to_tail_leaf(key, value);
        this->last_element = key;
    }
}
//  bulkload_leaf

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query(_Key key) {
    // point query
    if(key > sorted.getMaximumKey()){
        return this->unsorted.query(key);
    }else{
        return this->unsorted.query(key) || this->sorted.query(key);
    }
}

