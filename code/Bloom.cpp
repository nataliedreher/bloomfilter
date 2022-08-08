#include "Bloom.h"





Bloom::Bloom() {
    BloomFilter = shared_ptr<bloom_filter>(NULL);
}

Bloom::~Bloom() {

}

vector<int> Bloom::Hash(string str, shared_ptr<bloom_filter> h_table) {
    vector<int> hash;
    hash.push_back(Hash_1(str, h_table));
    hash.push_back(Hash_2(str, h_table));
    hash.push_back(Hash_3(str, h_table));
    hash.push_back(Hash_4(str, h_table));
    
    /*
    for (int i = 0; i < 4; i++) {
        cout << "1: " << hash[i] << "\n";
    }
    */
    return hash;
}

int Bloom::Hash_1(string str, shared_ptr<bloom_filter> h_table) {
    ull hash = 1;
    int size = str.size();
    for (int i = 0; i < size; i++)
	{
		hash = hash + 3 * str[i];
		hash = hash % h_table->size;
	}
    return hash;
}

int Bloom::Hash_2(string str, shared_ptr<bloom_filter> h_table) {

    ull hash = 5;
    int size = str.size();
    for (int i = 0; i < size; i++)
	{
		hash = hash + pow(13, i) * str[i];
		hash = hash % h_table->size;
	}
    return hash;
}

int Bloom::Hash_3(string str, shared_ptr<bloom_filter> h_table) {
    ull hash = 31;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 7 + str[0] * pow(7, i);
		hash = hash % h_table->size;
	}
	return hash;
}

int Bloom::Hash_4(string str, shared_ptr<bloom_filter> h_table) {
    ull hash = 11;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 7 + str[0] * pow(13, i);
		hash = hash % h_table->size;
	}
	return hash;
}

shared_ptr<bloom_filter> Bloom::InitTable(unsigned int size, unsigned int hashes) {
    shared_ptr<bloom_filter> ret(new bloom_filter);
    ret->size = size;
    vector<bool> vec(size, false);
    ret->table = vec;
    ret->hashes = hashes;
    ret->elements = 0;
    return ret;
}

void Bloom::AddToBloom(shared_ptr<bloom_filter> bloom, string username) {
    vector<int> hash = Hash(username, bloom);
    int hashNum = hash.size();
    for (int i = 0; i < hashNum; i++) {
        bloom->table[hash[i]] = true;
    }
    bloom->elements++;
}

bool Bloom::IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username) {

    int size = bloom->table.size();

    bool bit = { false };

    for (int i = 0; i < size; i++) {
        if (bloom->table[i] != bit) {

        }
    }

    return true;
}

float Bloom::FalsePositiveChance(shared_ptr<bloom_filter> bloom) {
    int num = bloom->hashes * bloom->elements;
    double d = -num / (float) bloom->size;
    double e = exp(d);
    return pow((1 - e), bloom->hashes);
}

void Bloom::Clear(shared_ptr<bloom_filter> bloom) {
    int size = bloom->size;
    for (int i = 0; i < size; i++) {
        bloom->table[i] = false;
    }
    bloom->elements = 0;
}