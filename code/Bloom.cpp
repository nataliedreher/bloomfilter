#include "Bloom.h"


Bloom::Bloom() {
    BloomFilter = shared_ptr<bloom_filter>(NULL);
}

Bloom::~Bloom() {

}

vector<int> Bloom::Hash(string str, shared_ptr<bloom_filter> bloom) {
    vector<int> hash;
    
    hash.push_back(Hash_1(str, bloom));
    hash.push_back(Hash_2(str, bloom));
    hash.push_back(Hash_3(str, bloom));
    hash.push_back(Hash_4(str, bloom));
    hash.push_back(Hash_5(str, bloom));
    hash.push_back(Hash_6(str, bloom));
    hash.push_back(Hash_7(str, bloom));
    hash.push_back(Hash_8(str, bloom));
        
    int diff = 8 - bloom->hashes;

    for (int i = 0; i < diff; i++) {
        hash.pop_back();
    }    
    
    return hash;
}

int Bloom::Hash_1(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 1;
    int size = str.size();
    for (int i = 0; i < size; i++)
	{
		hash = hash + 59 * str[i];
		hash = hash % bloom->size;
	}
    return hash;
}

int Bloom::Hash_2(string str, shared_ptr<bloom_filter> bloom) {

    ull hash = 89;
    int size = str.size();
    for (int i = 0; i < size; i++)
	{
		hash = hash + str[i] * pow(13, i);
		hash = hash % bloom->size;
	}
    return hash;
}

int Bloom::Hash_3(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 29;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 3 + str[i] * pow(17, i);
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_4(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 11;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 5 + str[i] * pow(19, i);
		hash = hash % bloom->size;
	}
	return hash;
}


int Bloom::Hash_5(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 5;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 3 + str[i] * pow(31, i);
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_6(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 13;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 3 + str[i] * 59;
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_7(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 11;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 7 + str[i] * pow(13, i);
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_8(string str, shared_ptr<bloom_filter> bloom) {
    ull hash = 79;
    int size = str.size();
	for (int i = 0; i < size; i++) {
		hash += hash * 17 + str[i] * pow(5, i);
		hash = hash % bloom->size;
	}
	return hash;
}

shared_ptr<bloom_filter> Bloom::InitTable(unsigned int size, bool automatic) {
    shared_ptr<bloom_filter> ret(new bloom_filter);
    ret->size = size;
    vector<bool> vec(size, false);
    ret->table = vec;
    if (!automatic) {
       ret->hashes = 4; 
    } else {
        ret->elements = size * 0.1;
        int hashes = 1;
        float p = 1.0;
        for (int i = 1; i < 9; i++) {
            ret->hashes = i;
            if (FalsePositiveChance(ret) < p) {
                p = FalsePositiveChance(ret);
                hashes = i;
            }
        }
        ret->elements = 0;
        ret->hashes = hashes;  
    }
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
    vector<int> hash = Hash(username, bloom);
    int size = hash.size();
    for (int i = 0; i < size; i++) {
        if (bloom->table[hash[i]] == false) {
            return true;
        }
    }

    return false;
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