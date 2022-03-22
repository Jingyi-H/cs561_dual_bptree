#include "dual_betree.h"

template <typename _Key, typename _Value>
DualBeTree<_Key, _Value>::DualBeTree(std::vector<std::pair<_Key, _Value>> _key_value_pairs, uint _buffer_size)
{
    // constructor
    this->key_value_pairs = _key_value_pairs;
    this->buffer_size = _buffer_size;
}

template <typename _Key, typename _Value>
void DualBeTree<_Key, _Value>::build() {
    /** build dual bplus tree
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */

}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::query(_Key key) {
    // point query

    return false;
}

template <typename _Key, typename _Value>
std::vector<std::pair<_Key, _Value>> rangeQuery(_Key low, _Key high, BeTraits &traits) {
    // range query

    return nullptr;
}
