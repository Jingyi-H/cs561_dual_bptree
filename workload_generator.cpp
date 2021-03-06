#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <random>
#include <iomanip>
#include <cassert>


typedef unsigned int key_type;


inline bool ledger_exists();
void generate_one_file(key_type pTOTAL_NUMBERS, key_type pdomain, key_type windowSize, key_type k, int l, int pseed, std::string type, std::string pathToDirectory);
std::string generate_partitions_stream(key_type TOTAL_NUMBERS, key_type domain, key_type windowSize, key_type K, int L, int seed, std::string folder, std::string type);

inline bool ledger_exists()
{
    std::ifstream f("dataledger.txt");
    return f.good();
}

void generate_one_file(key_type pTOTAL_NUMBERS, key_type pdomain, key_type windowSize, key_type k, int l, int pseed, std::string type, std::string pathToDirectory)
{
    std::ofstream outfile;

    srand(time(NULL));
    outfile.open("dataledger.txt", std::ios_base::app);

    std::string folder_name = pathToDirectory+"/";

    outfile << generate_partitions_stream(pTOTAL_NUMBERS, pdomain, windowSize, k, l, pseed, folder_name, type) << std::endl;

    outfile.close();
}



key_type generate_random_in_range(key_type position, key_type Total_Numbers, int L)
{
    int l = L;
    int ret;

    uint min_jump = 1;
    uint max_jump = l;

    // a jump can be only of l windowSizeaces
    int jump = rand() % (max_jump) + min_jump;

    if (position <= l)
    {

        // we can only jump forward
        ret = position + jump;
    }
    else if ((key_type)(position + l) >= Total_Numbers)
    {

        // we can only jump backward
        ret = position - jump;
    }
    else
    {
    
        // we can jump forward or backward
        // let's toss a coin to find out what to do
        float p = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        // we move backwards with p < 0.5
        if (p < 0.5)
            ret = position - jump;
        else
            ret = position + jump;
    }
    if (ret < 0)
    {
        std::cout << "oops (negative index)" << std::endl;
    }

    return (key_type)ret;
}

std::string generate_partitions_stream(key_type TOTAL_NUMBERS, key_type domain, key_type windowSize, key_type K, int L, int seed, std::string folder = "./Data", std::string type = "bin")
{
    float p_outOfRange = (double)K / TOTAL_NUMBERS;

    std::srand(seed);


    key_type *array = new key_type[TOTAL_NUMBERS];

    std::string f1name = folder;
    f1name += "/createdata_";
    f1name += std::to_string(TOTAL_NUMBERS);
    f1name += "-elems_";
    f1name += std::to_string(K);
    f1name += "-K_";
    f1name += std::to_string(L);
    f1name += "-L_";
    f1name += std::to_string(seed);
    f1name += "seed";
    f1name += std::to_string(std::time(nullptr));

    std::ofstream myfile1;
    
    if (type.compare("txt") == 0)
    {
        f1name += ".txt";
        myfile1.open(f1name);
    }

    else
    {
        f1name += ".dat";
        myfile1.open(f1name, std::ios::binary);
    }

    

    key_type noise_limit = TOTAL_NUMBERS * p_outOfRange;
    assert(noise_limit == K);
    key_type noise_counter = 0;

    std::unordered_set<key_type> myset;
    key_type w = 0;
    for (key_type i = 0; i < TOTAL_NUMBERS; i++, w += windowSize)
    {
        array[i] = w;
    }

    // loop through the domain and randomly start picking positions
    for (key_type i = 0; i < TOTAL_NUMBERS; i++)
    {
        float ran = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        //randomize generation
        if (ran < p_outOfRange && noise_counter < noise_limit)
        {
            //generate position of shuffle
            key_type r;
            while (true)
            {
                r = generate_random_in_range(i, TOTAL_NUMBERS, L);
                if (myset.find(r) != myset.end())
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            myset.insert(r);

            key_type temp = array[i];
            array[i] = array[r];
            array[r] = temp;

            noise_counter++;
            if (noise_counter == noise_limit)
                break;
        }
    }

    if (type.compare("txt") == 0)
    {
        for (key_type j = 0; j < TOTAL_NUMBERS; ++j)
        {
            myfile1 << array[j] << ",";
        }
    }
    else
    {
        for (key_type j = 0; j < TOTAL_NUMBERS; ++j)
        {
            myfile1.write(reinterpret_cast<char *>(&array[j]), sizeof(key_type));
        }
    }

    myfile1.close();
    delete[] array;
    return f1name;
}

int main(int argc, char **argv)
{
    if (argc < 7)
    {
        std::cout << "Program requires 7 inputs as parameters. \n Use format: ./workload_generator <totalNumbers> <domain> <kNumber> <lNumber> <seedValue> <typeOfFile> <pathToDirectory>" << std::endl;
        return 0;
    }

    key_type totalNumbers = atoi(argv[1]);
    key_type domain = atoi(argv[2]);
    key_type K = atoi(argv[3]);
 
    // since we are using rand() function, we only have to take l as an int
    int L = atoi(argv[4]);
    int seedValue = atoi(argv[5]);
    std::string type = argv[6];
    std::string pathToDirectory = argv[7];

    // for simplicity lets use window size = 1
    key_type windowSize = 1; 

    generate_one_file(totalNumbers, domain, windowSize, K, L, seedValue, type, pathToDirectory);
}