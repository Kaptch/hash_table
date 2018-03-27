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

#endif //HASH_TABLE_HASH_TABLE_UTILS_H
