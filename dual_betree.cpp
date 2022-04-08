#include "dual_betree.h"
#define DEFAULT -1
#define SORTED 1
#define UNSORTED 0
#define FREQ_QUEUE_SIZE 10
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
    this->sorted_size = 0;
    this->unsorted_size = 0;
    
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::insert(_Key key, _Value value) {
    /** insert element to 
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    bool flag;
    // if (!this->sorted->tail_leaf || key >= this->sorted->tail_leaf->getDataPairKey(0)) {
    if (key >= this->sorted->getMaximumKey()) {
        flag = this->sorted->insert_to_tail_leaf(key, value);
        if (flag) {
            this->last_element = key;
            this->sorted_size++;
        }
    }
    else if (!this->sorted->tail_leaf || key >= this->sorted->tail_leaf->getDataPairKey(0)) {
        flag = this->sorted->insert_to_tail_first(key, value);
    }
    else {
        flag = this->unsorted->insert(key, value);
        if (flag) {
            this->unsorted_size++;
        }
    }
    return flag;
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query(_Key key) {
    // point query
    if (this->sorted_size < this->unsorted_size) {
        return this->sorted->query(key) || this->unsorted->query(key);
    } else {
        return this->unsorted->query(key) || this->sorted->query(key);
    }
}


