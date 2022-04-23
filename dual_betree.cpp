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
    this->tail_max = DEFAULT;
    this->tail_min = DEFAULT;
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
    if (key >= this->tail_max) {
        flag = this->sorted->insert_to_tail_leaf(key, value);
        if (flag) {
            this->tail_max = key;
            this->sorted_size++;
        }
    }
    else if (key >= this->sorted->tail_leaf->getDataPairKey(0)) {
        bool to_sorted = this->sorted->insert_to_tail_first(key, value, this->outlier, this->tail_max);
        // cout << "retrieve outlier = " << this->outlier.first << "current max = " << this->tail_max << endl;
        bool to_unsorted = this->unsorted->insert(this->outlier.first, this->outlier.second);
        // replace one key in sorted tree, so sorted_size is unchanged
        this->unsorted_size++;
        flag = to_sorted && to_unsorted;
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


