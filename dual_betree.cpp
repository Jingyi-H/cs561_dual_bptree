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
    this->sum = 0;
    this->ss = 0;
    this->sd = 0;
    
}

template <typename _Key, typename _Value>
bool DualBeTree<_Key, _Value>::insert(_Key key, _Value value, int num_sd) {

    if(sorted_size < 2){
        this->sorted->insert_to_tail_leaf(key, value);
        sorted_size++;
        //update sd
        sum += key;
        ss += (key-(sum/sorted_size))^2;
        sd = sqrt(ss/(sorted_size-1));        
        // cout << "inserted key: "<< key << endl;

    }else{ 
        // cout<<"tail minimum:"<<sorted->tail_leaf->getDataPairKey(0)<<endl;

        //if key is smaller than tail leaf min key, insert to unordered tree
        if(key < this->sorted->tail_leaf->getDataPairKey(0)){
            this->unsorted->insert(key, value);
            this->unsorted_size++;
            // cout<<"unsorted 1: "<<key<<endl;
        }else{ 
            // cout<<"sorted max: "<<sorted->getMaximumKey()<<endl;
            // cout<< "sd: "<<sd<<endl;
            //otherwise, check if it is within sd range
            //if key is out of sd range, insert to unsorted tree
            if(key >sorted->getMaximumKey() && key < num_sd*sd + this->sorted->getMaximumKey()){
                this->sorted->insert_to_tail_leaf(key, value);
                this->last_element = key;
                this->sorted_size++;
                // cout<<"sorted 1: "<<key<<endl;
                //update sd
            sum += key;
            ss += (key-(sum/sorted_size))^2;
            sd = sqrt(ss/(sorted_size-1)); 
            }else if (key < sorted->getMaximumKey() && key > this->sorted->getMaximumKey()- num_sd*sd & ){
                this->sorted->insert_to_tail_first(key, value);
                this->sorted_size++;
                // cout<<"sorted 2"<<endl;
                //update sd
            sum += key;
            ss += (key-(sum/sorted_size))^2;
            sd = sqrt(ss/(sorted_size-1)); 
            }else{
                this->unsorted->insert(key, value);
                this->unsorted_size++;
                // cout<<"unsorted 2"<<endl;
            }          
                   
        }
    
    }
    return true;


    
    
    // /** insert element to 
    // * insert in-order elements to sorted bplus tree
    // * out-of-order elements to unsorted bplus tree
    // */
    // bool flag;
    // // if (!this->sorted->tail_leaf || key >= this->sorted->tail_leaf->getDataPairKey(0)) {
    // if (key >= this->sorted->getMaximumKey()) {
    //     flag = this->sorted->insert_to_tail_leaf(key, value);
    //     if (flag) {
    //         this->last_element = key;
    //         this->sorted_size++;
    //     }
    // }
    // else if (!this->sorted->tail_leaf || key >= this->sorted->tail_leaf->getDataPairKey(0)) {
    //     flag = this->sorted->insert_to_tail_first(key, value);
    // }
    // else {
    //     flag = this->unsorted->insert(key, value);
    //     if (flag) {
    //         this->unsorted_size++;
    //     }
    // }
    // return flag;
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


