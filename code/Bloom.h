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

  vector<bool> bitTable;

  vector<int> hashValues;

  unsigned int hashes;

  unsigned int elements;

};


class Bloom
{
public:
    Bloom();
    ~Bloom();
    vector<int> Hash(string str, shared_ptr<bloom_filter> bloom);
    shared_ptr<bloom_filter> InitTable(unsigned int size, bool automatic = false);
    void AddToBloom(shared_ptr<bloom_filter> bloom, string username);
    bool IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username);
    float FalsePositiveChance(shared_ptr<bloom_filter> bloom);
    void Clear(shared_ptr<bloom_filter> bloom);
private:
    /* data */
    shared_ptr<bloom_filter> BloomFilter;
    int Hash_1(string str, shared_ptr<bloom_filter> bloom);
    int Hash_2(string str, shared_ptr<bloom_filter> bloom);
    int Hash_3(string str, shared_ptr<bloom_filter> bloom);
    int Hash_4(string str, shared_ptr<bloom_filter> bloom);
    int Hash_5(string str, shared_ptr<bloom_filter> bloom);
    int Hash_6(string str, shared_ptr<bloom_filter> bloom);
    int Hash_7(string str, shared_ptr<bloom_filter> bloom);
    int Hash_8(string str, shared_ptr<bloom_filter> bloom);

};






#endif  // BLOOM_H__
