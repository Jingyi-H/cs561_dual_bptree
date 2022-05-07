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
    sorted = new BeTree<_Key,_Value>("sortedT", "./tree_dat", 4096, 50000);
    unsorted= new BeTree<_Key,_Value>("unsortedT", "./tree_dat", 4096, 50000);
    this->sorted = sorted;
    this->unsorted =  unsorted;
    this->tail_min = DEFAULT;
    this->tail_max = DEFAULT;
    this->sorted_size = 0;
    this->unsorted_size = 0;
    // this->sum = 0;
    // this->ss = 0;
    // this->sd = 1;
    // this->fail = 0;
    // this->failThres = _failThres;
    // this->num_sd = _num_sd;
    
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::insert(_Key key, _Value value) {
    /** insert element to 
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    bool flag;
    if (key >= this->tail_max) {
        flag = this->sorted->insert_to_tail_leaf(key, value, this->tail_min);
        if (flag) {
            this->tail_max = key;
            this->sorted_size++;
        }
    }
    else if (key >= this->tail_min) {
        flag = this->sorted->insert_to_tail_first(key, value, tail_min);
        this->sorted_size++;
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

template <typename _Key, typename _Value>
void DualBeTree<_Key, _Value>::analysis() {
    cout << "Sorted Tree Size = " << this->sorted_size << endl;
    cout << "Unsorted Tree Size = " << this->unsorted_size << endl;
    cout << "-------------------------Test Dual B+ Tree-------------------------" << endl;
    cout << "insert_time=" << this->sorted->timer.insert_time + this->unsorted->timer.insert_time << endl;
    cout << "point_query_time=" << this->sorted->timer.point_query_time + this->unsorted->timer.point_query_time << endl;

    this->sorted->fanout();
    cout << "------Statistics of sorted tree------" << endl;
    cout << "num_internal_nodes=" << this->sorted->traits.num_internal_nodes << endl;
    cout << "depth = " << this->sorted->depth() << endl;
    cout << "average fanout =" << this->sorted->traits.average_fanout << endl;
    
    this->unsorted->fanout();
    cout << "------Statistics of unsorted tree------" << endl;
    cout << "num_internal_nodes=" << this->unsorted->traits.num_internal_nodes << endl;
    cout << "depth = " << this->unsorted->depth() << endl;
    cout << "average fanout=" << this->unsorted->traits.average_fanout << endl;

}
