//
// Created by kaptch on 3/27/18.
//

#ifndef HASH_TABLE_HASH_TABLE_UTILS_H
#define HASH_TABLE_HASH_TABLE_UTILS_H

#include <iostream>
#include "hash_table.h"

struct hash1 {
    int operator()(const int i) const {
        return i % 1999;
    }
};

template<class Val, class Hash = std::hash<Val>>
void printHT(const hash_table<Val, Hash> &ht, std::ostream &os) {
    Hash hash;
    std::for_each(ht.begin(), ht.end(), [&os, hash](Val i) {
        os << "value: " << i << " hash: " << hash(i) << " index: " << hash(i) % 1999 << std::endl;
    });
    return;
};

#endif //HASH_TABLE_HASH_TABLE_UTILS_H
