#include "dual_betree.h"

template <typename _Key, typename _Value>
DualBeTree<_Key, _Value>::DualBeTree(std::vector<std::pair<_Key, _Value>> _key_value_pairs, uint _buffer_size)
{
    // constructor
    this->key_value_pairs = _key_value_pairs;
    this->buffer_size = _buffer_size;
    BeTree<_Key, _Value> sorted("sortedT", "./tree_dat", 4096, 10000);
    BeTree<_Key, _Value> unsorted("unsortedT", "./tree_dat", 4096, 10000);
    this-> sorted = sorted;
    this-> unsorted =  unsorted;
}

template <typename _Key, typename _Value>
void DualBeTree<_Key, _Value>::build() {
    /** build dual bplus tree
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    for (auto& pair : _key_value_pairs) {
        if (pair.first < this->buffer_elements) {
            this->unsorted.insert(pair.first, pair.second);
        } else {
            this->sorted.insert(pair.first, pair.second);
        }
        buffer_elements = pair.first;
    }
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query(_Key key) {
    // point query
    if(key > sorted.getMaximumKey()){
        return this->unsorted.query(key);
    }else{
        return this->unsorted.query(key) || this->sorted.query(key);
    }
}

template <typename _Key, typename _Value>
std::vector<std::pair<_Key, _Value>> rangeQuery(_Key low, _Key high, BeTraits &traits) {
    // range query

    return nullptr;
}
