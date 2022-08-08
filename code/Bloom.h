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

  int hashes;

  int elements;

  
};


class Bloom
{
public:
    Bloom();
    ~Bloom();
    vector<int> Hash(string str, shared_ptr<bloom_filter> h_table);
    shared_ptr<bloom_filter> InitTable(unsigned int size, unsigned int hashes);
    void AddToBloom(shared_ptr<bloom_filter> bloom, string username);
    bool IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username);
    float FalsePositiveChance(shared_ptr<bloom_filter> bloom);
    void Clear(shared_ptr<bloom_filter> bloom);
private:
    /* data */
    shared_ptr<bloom_filter> BloomFilter;
    int Hash_1(string str, shared_ptr<bloom_filter> h_table);
    int Hash_2(string str, shared_ptr<bloom_filter> h_table);
    int Hash_3(string str, shared_ptr<bloom_filter> h_table);
    int Hash_4(string str, shared_ptr<bloom_filter> h_table);
    

};






#endif  // BLOOM_H__
