#include "Bloom.h"

// constructor
Bloom::Bloom() {
    // Constructor starts with BloomFilter as NULL.
    BloomFilter = shared_ptr<bloom_filter>(NULL);
}

//deconstructor
Bloom::~Bloom() {
    // Since smart pointers are being used this can be left empty. 
}

vector<int> Bloom::Hash(string str, shared_ptr<bloom_filter> bloom) {

    // Declare and empty vector<int> named hash.
    vector<int> hash;
    
    // Push back the return values of the 8 hash function into hash.
    hash.push_back(Hash_1(str, bloom));
    hash.push_back(Hash_2(str, bloom));
    hash.push_back(Hash_3(str, bloom));
    hash.push_back(Hash_4(str, bloom));
    hash.push_back(Hash_5(str, bloom));
    hash.push_back(Hash_6(str, bloom));
    hash.push_back(Hash_7(str, bloom));
    hash.push_back(Hash_8(str, bloom));
    
    // Declare int diff as the difference of 8 and bloom->hashes. 
    int diff = 8 - bloom->hashes;

    // Loop from 0 to diff (non-inclusive). Pop the end element from hash,
    // this will make it so hash.size() == bloom->hashes so that we have the 
    // correct number of hash function returns.
    for (int i = 0; i < diff; i++) {
        hash.pop_back();
    }    
    
    // Return hash.
    return hash;
}

shared_ptr<bloom_filter> Bloom::InitTable(unsigned int size, bool automatic) {

    // Create a new bloom_filter named ret.
    shared_ptr<bloom_filter> ret(new bloom_filter);

    // Set ret->size to the inputted value of size.
    ret->size = size;

    // Create a new vector named vec for size number of elements all set to false.
    vector<bool> vec(size, false);

    // Set ret->bitTable equal to vec.
    ret->bitTable = vec;

    // Declare int hashes equal to 4;
    int hashes = 4;

    // If automatic is false set ret->hashes equal to hashes.
    if (!automatic) {
       ret->hashes = hashes; 
    } 
    // If automatic is true we will calculate the optimal number of hash
    // functions to use (up to 8 total).
    else {

        // Temporarily set ret->elements equal to 1/10 the value of size.
        ret->elements = size * 0.1;

        // Set the value of hashes to 1.
        hashes = 1;

        // Declare float p with an initial value of 1.
        float p = 1.0;

        // Loop through values of i from 1 to 8.
        for (int i = 1; i < 9; i++) {

            // Set the value of ret->hashes equal to i.
            ret->hashes = i;

            // If the return of FalsePositiveChance is less than p set p equal
            // to said return and set hashes equal to i.
            if (FalsePositiveChance(ret) < p) {
                p = FalsePositiveChance(ret);
                hashes = i;
            } 
        }

        // Set ret->hashes equal to the value of hashes which is the calculate optimum.
        ret->hashes = hashes;  
    }

    // Create an empty vector<int> named vec2 then set ret->hashValues equal to vec2.
    //vector<int> vec2;
    //ret->hashValues = vec2;

    // Set the current value of ret->elements equal to zero.
    ret->elements = 0;

    // Return ret.
    return ret;
}

void Bloom::AddToBloom(shared_ptr<bloom_filter> bloom, string username) {

    // Create a vector named hashVec with the return of Hash(username, bloom).
    bloom->hashValues = Hash(username, bloom);

    // Loop bloom->hashes times, each loop set the value of bloom->bitTable at the index 
    // whose value is found in bloom->hashValues at index i to true.
    for (unsigned int i = 0; i < bloom->hashes; i++) {
        bloom->bitTable[bloom->hashValues[i]] = true;
    }

    // Iterate the value of bloom->elements up by 1.
    bloom->elements++;
}

bool Bloom::IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username) {

    // Create a vector named hashVec with the return of Hash(username, bloom).
    bloom->hashValues = Hash(username, bloom);

    // Loop bloom->hashes times.
    for (unsigned int i = 0; i < bloom->hashes; i++) {

        // Check if the value value of bloom->bitTable at the index whose value is
        // found in bloom->hashValues at index i is false. If it's ever false we can
        // return true as the username is definitely available.
        if (bloom->bitTable[bloom->hashValues[i]] == false) {
            return true;
        }
    }

    // If the for loop never returned true then the username may not be available so
    // return false.
    return false;
}

float Bloom::FalsePositiveChance(shared_ptr<bloom_filter> bloom) {

    // Declare int num as the product of bloom->hashes and bloom->elements
    int num = bloom->hashes * bloom->elements;

    // Declare double d as the negative of num divided by bloom->size converted to a float.
    double d = -num / (float) bloom->size;

    // Declare double e as the value of e^d.
    double e = exp(d);

    // Return (1-e)^bloom->hashes.
    return pow((1 - e), bloom->hashes);
}

void Bloom::Clear(shared_ptr<bloom_filter> bloom) {

    // Loop through all of bloom->bitTable setting all values to false.
    for (unsigned int i = 0; i < bloom->size; i++) {
        bloom->bitTable[i] = false;
    }

    // Create an empty vector<int> named vec then set ret->hashValues equal to vec.
    vector<int> vec;
    bloom->hashValues = vec;

    // Set bloom->elements equal to zero.
    bloom->elements = 0;
}

// Below are the 8 hashing functions.
int Bloom::Hash_1(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 1.
    ull hash = 1;

    // Loop through string str.
    for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash + 59 * str[i];

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
    return hash;
}

int Bloom::Hash_2(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 89.
    ull hash = 89;

    // Loop through string str.
    for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash + str[i] * pow(13, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
    return hash;
}

int Bloom::Hash_3(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 29.
    ull hash = 29;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 3 + str[i] * pow(17, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_4(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 11.
    ull hash = 11;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 5 + str[i] * pow(19, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}


int Bloom::Hash_5(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 5.
    ull hash = 5;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 3 + str[i] * pow(31, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_6(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 13.
    ull hash = 13;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 3 + str[i] * 59;

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_7(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 11.
    ull hash = 11;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 7 + str[i] * pow(13, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}

int Bloom::Hash_8(string str, shared_ptr<bloom_filter> bloom) {

    // Declare ull hash equal to 79.
    ull hash = 79;

    // Loop through string str.
	for (unsigned int i = 0; i < str.size(); i++) {

        // Set hash equal to the below value.
		hash += hash * 17 + str[i] * pow(5, i);

        // Set hash equal to hash % bloom->size.
		hash = hash % bloom->size;
	}
	return hash;
}