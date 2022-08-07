#ifndef BLOOM_H__
#define BLOOM_H__

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned long long ull;

struct bloom_filter {

  unsigned int size;

  vector<bool> table;

  
};

unsigned int DJB2(std::string key);


unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap);

class Bloom
{
public:
    Bloom();
    ~Bloom();
    vector<bool> Hash(string str);
    shared_ptr<bloom_filter> InitTable(unsigned int cap);
    void AddToBloom(shared_ptr<bloom_filter> bloom, string username);
    bool IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username);
    float FalsePositiveChance(int bitsInArray, int numberOfHashF);
private:
    /* data */
    int Hash_1(string str);
    int Hash_2(string str);
    int Hash_3(string str);
    int Hash_4(string str);
    shared_ptr<bloom_filter> h_table;

};






#endif  // BLOOM_H__
