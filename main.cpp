#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include "dual_betree.cpp"
using namespace std; 

// genetate point query
std::vector<int> generatePointQueries(std::vector<int> data, int n)
{
    std::vector<int> queries;
    int size = n*0.1;
    int non_existing_counter = (n*0.1);
    std::uniform_int_distribution<int> dist{0,n};
    // Initialize the random_device
    std::random_device rd;
     // Seed the engine
    std::mt19937_64 generator(rd());
    std::set<int> non_existing;
    while (non_existing.size() != non_existing_counter)
    {
        non_existing.insert(data[dist(generator)]);
    }
    
    queries.insert(queries.end(),non_existing.begin(),non_existing.end());
    // shuffle indexes
    std::random_shuffle(queries.begin(), queries.end());

    return queries;
}

void testBptree(std::vector<int> data, std::vector<int> queries){
     // instantiate betree
    // cout<<"TEST NORAMAL B+ TREE INSERT:"<<endl;
    BeTree<int,int> tree("manager", "./tree_dat", 4096, 10000);

    // auto insert_start1 = std::chrono::high_resolution_clock::now();
    // Loop through data and insert each element to dual bplus tree
    for(int i : data){
        if (!tree.insert(i,i))
            cout << "B+: Failed to insert key " << i << endl;
    }
    // auto insert_stop1 = std::chrono::high_resolution_clock::now();
    // auto duration1  = std::chrono::duration_cast<std::chrono::microseconds>(insert_stop1 - insert_start1);
    // unsigned long long insert_time1 = duration1.count();
    // cout << "Time take to insert " << data.size() << " keys = " << insert_time1 << " microseconds" << endl;

    // // execute point queries on bptree
    // auto query_start1 = std::chrono::high_resolution_clock::now();
    // query from dualbptree
    int yes1 = 0;
    int no1 = 0;

    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    // cout<<"TEST NORAMAL B+ TREE QUERY:"<<endl;
    for (int i = 0; i < queries.size(); i++){
        if(tree.query(queries[i])){
            yes1++;
        }
        else {
            // std::cout << "Key " << queries[i] << " not found" << endl;
            no1++;
        }
    }
    
    // auto query_stop1 = std::chrono::high_resolution_clock::now();
    // duration1 = std::chrono::duration_cast<std::chrono::microseconds>(query_stop1 - query_start1);
    // unsigned long long point_query_time1 = duration1.count();
    // std::cout << "Time taken to perform " << queries.size() << " point queries = " << point_query_time1 << " microseconds" << endl;
    std::cout << "found:" << yes1 << endl;
    std::cout << "notfound:" << no1 << endl;

    tree.fanout();
#ifdef TIMER
    cout << "-------Test Normal B+ Tree-------" << endl;
    cout << "insert_time=" << tree.timer.insert_time << endl;
    cout << "point_query_time=" << tree.timer.point_query_time << endl;
#endif
    cout << "------Statistics of B+ tree------" << endl;
    cout << "num_internal_nodes=" << tree.traits.num_internal_nodes << endl;
    cout << "depth = " << tree.depth() << endl;
    cout << "average fanout =" << tree.traits.average_fanout << endl;
    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

}

void testDualTree(std::vector<int> data, std::vector<int> queries){
   // Instantiate dual bplus tree
    // cout<<"TEST DUAL B+ TREE INSERT:"<<endl;
    DualBeTree<int,int> dualbptree = DualBeTree<int,int>();
  
    auto insert_start = std::chrono::high_resolution_clock::now();
    // Loop through data and insert each element to dual bplus tree
    for(int i : data){
        // cout << "insert key: " << i << endl;
        if (!dualbptree.insert(i,i))
            cout << "Dual B+: Failed to insert key " << i << endl;
    }
    // auto insert_stop = std::chrono::high_resolution_clock::now();
    // auto duration  = std::chrono::duration_cast<std::chrono::microseconds>(insert_stop - insert_start);
    // unsigned long long insert_time = duration.count();
    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    // cout << "Time taken to insert " << data.size() << " keys = " << insert_time << " microseconds" << endl;

    // auto query_start = std::chrono::high_resolution_clock::now();
    // query from dualbptree
    int yes = 0;
    int no = 0;

    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    // cout<<"TEST DUAL B+ TREE QUERY:"<<endl;

    for (int i = 0; i < queries.size(); i++){
        if(dualbptree.query(queries[i])){
            yes++;
        }
        else {
            std::cout << "Dual B+: Key " << queries[i] << " not found" << endl;
            no++;
        }
    }
    
    // auto query_stop = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(query_stop - query_start);
    // unsigned long long point_query_time = duration.count();
    // std::cout << "Time taken to perform " << queries.size() << " point queries = " << point_query_time << " microseconds" << endl;
    std::cout << "found:" << yes << endl;
    std::cout << "notfound:" << no << endl;

    dualbptree.analysis();
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: ./main <input_file>" << std::endl;
        return 0;
    }

    std::string input_file = argv[1];

    // read data generated by workload generator
    std::ifstream ifs;
    std::vector<int> data;

    ifs.open(input_file, std::ios::binary);
    ifs.seekg(0, std::ios::end);
    size_t filesize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    data.resize(filesize / sizeof(int));
    ifs.read((char *)data.data(), filesize);
    std::vector<int> queries = generatePointQueries(data, data.size());

    // testBptree(data, queries);
    testDualTree(data, queries);

    return 1; 
}
