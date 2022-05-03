#include "dual_betree.h"
#define DEFAULT -1
#define SORTED 1
#define UNSORTED 0
#define FREQ_QUEUE_SIZE 10
using namespace std;

template <typename _Key, typename _Value>
DualBeTree<_Key,_Value>::DualBeTree(int _num_sd)
{
    // constructor
    sorted = new BeTree<_Key,_Value>("sortedT", "./tree_dat", 4096, 50000);
    unsorted= new BeTree<_Key,_Value>("unsortedT", "./tree_dat", 4096, 50000);
    this->sorted = sorted;
    this->unsorted =  unsorted;
    this->tail_min = DEFAULT;
    this->tail_max = DEFAULT;
    this->tree_min = DEFAULT;
    this->sorted_size = 0;
    this->unsorted_size = 0;
    this->sum = 0;
    this->ss = 0;
    this->sd = 1;
    this->num_sd = _num_sd;
    
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::insert(_Key key, _Value value) {
    /** insert element to 
    * insert in-order elements to sorted bplus tree
    * out-of-order elements to unsorted bplus tree
    */
    bool flag;
    if (key > this->tail_max) {
        if (this->tail_max == DEFAULT) {
            // insert to sorted tree
            flag = this->sorted->insert_to_tail_leaf(key, value, this->tail_min);
            this->sorted_size++;
            // update maximum key of tail leaf
            this->tail_max = key; 
            this->tree_min = key;
            this-> tail_min = key;
            updateSs(key);

            // cout << "sorted inserted: " <<key<<endl;
        }
        else if (outlierCheck(key)) {
            // insert to sorted tree
            flag = this->sorted->insert_to_tail_leaf(key, value, this->tail_min);
            this->sorted_size++; 
            // tail_min = this->sorted->tail_leaf->getDataPairKey(0);          
            // update sd
            tail_min = this->sorted->tail_leaf->getDataPairKey(0);          

            // update maximum key of tail leaf
            if(tail_max <key ){
                this->tail_max = key;
            }
            updateSs(key);

            // this->fail = 0;

            // cout << "sorted inserted: " <<key<<endl;

        } else {
            flag = this->unsorted->insert(key, value);
            // cout << "outlier check failed: key = " << key <<" sorted size = "<<sorted_size <<" sd = "<<this->sd<< " bound = " << this->sd + tail_max << endl;
            this->unsorted_size++;
            tail_max++;
        }
    } else if (key >= this->tail_min) {
        flag = this->sorted->insert_to_tail_first(key, value, this->tail_min);
        this->sorted_size++;
        // tail_max++;
        tail_min = this->sorted->tail_leaf->getDataPairKey(0);          

        // update sd
        // updateSs(key);
        // cout << "sorted inserted: " <<key<<endl;

    } else {
        flag = this->unsorted->insert(key, value);
        this->unsorted_size++;
        tail_max++;
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
    cout << "------------------------------Test Dual B+ Tree------------------------------" << endl;
    cout << "insert_time=" << this->sorted->timer.insert_time + this->unsorted->timer.insert_time << endl;
    cout << "point_query_time=" << this->sorted->timer.point_query_time + this->unsorted->timer.point_query_time << endl;

    this->sorted->fanout();
    cout << "------Statistics of sorted tree------" << endl;
    // cout << "internal splits=" << this->sorted->traits.internal_splits << endl;
    // cout << "num_leaf_nodes=" << this->sorted->traits.num_leaf_nodes << endl;
    cout << "num_internal_nodes=" << this->sorted->traits.num_internal_nodes << endl;
    cout << "depth = " << this->sorted->depth() << endl;
    cout << "average fanout =" << this->sorted->traits.average_fanout << endl;
    
    this->unsorted->fanout();
    cout << "------Statistics of unsorted tree------" << endl;
    // cout << "internal splits=" << this->unsorted->traits.internal_splits << endl;
    // cout << "num_leaf_nodes=" << this->unsorted->traits.num_leaf_nodes << endl;
    cout << "num_internal_nodes=" << this->unsorted->traits.num_internal_nodes << endl;
    cout << "depth = " << this->unsorted->depth() << endl;
    cout << "average fanout=" << this->unsorted->traits.average_fanout << endl;

}


