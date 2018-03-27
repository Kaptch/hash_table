#include <iostream>
#include <functional>
#include <variant>

#include "hash_table.h"
#include "hash_table_utils.h"

using namespace std;

int main() {
    hash_table<int, hash1> testHT = hash_table<int, hash1>();
    testHT.insert(5);
    testHT.insert(2004);
    for_each(testHT.begin(), testHT.end(),
             [](int i) {cout << i;});
    return 0;
}