#ifndef BLOOM_H__
#define BLOOM_H__

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>


using namespace std;

// Define unsigned long long as new type ull. 
// This is just to shorten it.
typedef unsigned long long ull;

// bloom_filter is a struct that holds all items needed to 
// implement a bloom filter.
struct bloom_filter {

  // size is the length of the bit vector which is the bloom filter.
  unsigned int size;

  // vector<bool> bitTable is the actual bloom filter. It is a vector
  // of size length and contains only false values initially. Individual
  // elements get set to true as usernames are hashed.
  vector<bool> bitTable;

  // vector<int> hashValues holds the returns from the hash functions.
  // These value give the indices in bitTable that need to be set to
  // true given an inputted username.
  vector<int> hashValues;

  // hashes is the current number of hash functions being used in
  // any bloom_filter that is created. This is either 4 or an optimized.
  // value depending the parameters given to InitTable.
  unsigned int hashes;

  // elements is a tracker for the number of usernames added to the filter.
  unsigned int elements;

};


class Bloom
{
public:
  // constructor
  Bloom();
  // deconstructor
  ~Bloom();

  // Hash takes a username and shared_ptr<bloom_filter> as parameters.
  // It then returns a vector<int> that contains the returns of the  
  // individual hashing functions hash values created from the inputted
  // username.
  vector<int> Hash(string str, shared_ptr<bloom_filter> bloom);

  // InitFilter takes a size integer as a required parameter. It has a
  // optional boolean parameter named automatic which defaults to false. 
  // automatic is used to determine if the default number of hashing
  // functions will be used or an optimized number will be. The return
  // of InitFilter is a new instance of shared_ptr<bloom_filter>.
  shared_ptr<bloom_filter> InitFilter(unsigned int size, bool automatic = false);
  
  // AddToBloom takes a shared_ptr<bloom_filter> and a username as 
  // parameters. It uses these inputs to call Hash, it uses Hash's
  // return to set the appropriate values of the bitTable to true.
  // Last it adds one to the value of elements to track the number of
  // inputted usernames.
  void AddToBloom(shared_ptr<bloom_filter> bloom, string username);

  // IsUsernamePossiblyAvailable takes a shared_ptr<bloom_filter> and a 
  // username as parameters. It uses these inputs to call Hash, it uses 
  // Hash's return to test the appropriate truth values of bitTable to
  // check if a username has been added. If this function returns true
  // then the username for sure hasn't been added to bitTable and is 
  // available to the user.
  bool IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username);
  
  // FalsePositiveChance takes a shared_ptr<bloom_filter> as a parameter.
  // It then uses values contain in this bloom filter to calculate the
  // probability of a false positive, i.e. the chance that 
  // IsUsernamePossiblyAvailable returns false when the username
  // hasn't actually been added.
  float FalsePositiveChance(shared_ptr<bloom_filter> bloom);

  // Clear takes a shared_ptr<bloom_filter> as a parameter. It then
  // sets all the values of the bloom filter to what they were initially
  // set to when InitFilter was originally called.
  void Clear(shared_ptr<bloom_filter> bloom);
private:

  int hash_primes[32] = {5227, 5231, 5233, 5237, 5261, 5273, 5279, 5281,
   5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387, 5393, 5399, 5407, 
   5413, 5417, 5419, 5431, 5437, 5441, 5443, 5449, 5471, 5477, 5479, 5483};

  // These 8 functions take a username and a shared_ptr<bloom_filter>
  // as parameters. They then give hash values that are uses to 
  // set the corresponding indices of bitTable to true.
  int Hash_1(string str, shared_ptr<bloom_filter> bloom);
  int Hash_2(string str, shared_ptr<bloom_filter> bloom);
  int Hash_3(string str, shared_ptr<bloom_filter> bloom);
  int Hash_4(string str, shared_ptr<bloom_filter> bloom);
  int Hash_5(string str, shared_ptr<bloom_filter> bloom);
  int Hash_6(string str, shared_ptr<bloom_filter> bloom);
  int Hash_7(string str, shared_ptr<bloom_filter> bloom);
  int Hash_8(string str, shared_ptr<bloom_filter> bloom);
  int Hasher(string str, shared_ptr<bloom_filter> bloom, ull hash);

};






#endif  // BLOOM_H__
