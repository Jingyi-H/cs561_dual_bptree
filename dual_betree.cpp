#include "dual_betree.h"
#define DEFAULT -1

using namespace std;

template <typename _Key, typename _Value>
DualBeTree<_Key,_Value>::DualBeTree()
{
    // constructor
    sorted = new BeTree<_Key,_Value>("sortedT", "./tree_dat", 4096, 10000);
    unsorted= new BeTree<_Key,_Value>("unsortedT", "./tree_dat", 4096, 10000);
    this->sorted = sorted;
    this->unsorted =  unsorted;
    this->last_element = DEFAULT;
    
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::insert(_Key key, _Value value) {
    /** insert element to 
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    bool flag;
    
    if (key < this->last_element) {
        flag = this->unsorted->insert(key, value);
    } else {
        flag = this->sorted->insert_to_tail_leaf(key, value);
        this->last_element = key;
    }
    return flag;
}
//  bulkload_leaf

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query(_Key key) {
    // point query
    if(key > this->sorted->getMaximumKey()){
        return this->unsorted->query(key);
    }else{
        return this->unsorted->query(key) || this->sorted->query(key);
    }
}

