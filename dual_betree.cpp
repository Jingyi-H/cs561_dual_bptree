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
    if (key < this->last_element) {
        flag = this->unsorted->insert(key, value);
        if (flag) {
            this->unsorted_size++;
            if (this->freq.size() == 10){
                this->freq.erase(log.begin());
                this->freq.push_back(False);
            }
        }
    } else {
        flag = this->sorted->insert_to_tail_leaf(key, value);
        if (flag) {
            this->last_element = key;
            this->sorted_size++;
            if (this->freq.size() == 10){
                this->freq.erase(log.begin());
                this->freq.push_back(True);
            }
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

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query_recent(_Key key) {
    // point query
    if (this->log.back() == True) {
        return this->sorted->query(key) || this->unsorted->query(key);
    } else {
        return this->unsorted->query(key) || this->sorted->query(key);
    }
}

