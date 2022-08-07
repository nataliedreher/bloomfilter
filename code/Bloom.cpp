#include "Bloom.h"





Bloom::Bloom() {
    h_table = shared_ptr<bloom_filter>(NULL);
}

Bloom::~Bloom() {

}

vector<bool> Bloom::Hash(string str) {
    
}

int Bloom::Hash_1(string str) {

}

int Bloom::Hash_2(string str) {

    ull hash = 5;

    for (int i = 0; i < str.size(); i++)
	{
		hash = hash + pow(23, i) * str[i];
		hash = hash % h_table->size;
	}
    return hash;
}

int Bloom::Hash_3(string str) {
    
}

int Bloom::Hash_4(string str) {
    
}

shared_ptr<bloom_filter> Bloom::InitTable(unsigned int cap) {

}

void Bloom::AddToBloom(shared_ptr<bloom_filter> bloom, string username) {

}

bool Bloom::IsUsernamePossiblyAvailable(shared_ptr<bloom_filter> bloom, string username) {

    int size = bloom->table.size();

    bool bit = { false };

    for (int i = 0; i < size; i++) {
        if (bloom->table[i] != bit) {

        }
    }
}

float Bloom::FalsePositiveChance(int bitsInArray, int numberOfHashF) {

}