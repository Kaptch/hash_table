#include <iostream>
#include <functional>
#include <variant>
#include <random>
#include <chrono>
#include <unordered_set>
#include <set>
#include <string>

#include "hash_table.h"
#include "hash_table_utils.h"

using namespace std;

string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

int main() {
    hash_table<string> testHT = hash_table<string>();
    std::unordered_set<string> testUS = unordered_set<string>();
    std::set<string> testST = set<string>();

    vector<string> ranStrs;
    for (int i = 0; i < 1000; ++i)
        ranStrs.push_back(random_string(6));
    for (auto i = ranStrs.begin(); i != ranStrs.end(); ++i) {
        testHT.insert(*i);
        testUS.insert(*i);
        testST.insert(*i);
    }

    printHT(testHT, cout);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000);

    std::vector<string> vec;
    for (int i = 0; i < 100000; ++i)
        vec.push_back(random_string(6));
    std::vector<string> ranI;
    for (int i = 0; i < 50; ++i)
        ranI.push_back(random_string(6));

    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testHT.insert(vec[i * j % 10000]);
        //for (int j = 0; j < 50; ++j)
            //testHT.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testHT.erase(vec[i * j % 10000]);
    }
    auto end1 = std::chrono::steady_clock::now();

    auto it2 = testHT.begin();

    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testUS.insert(vec[i * j % 10000]);
        //for (int j = 0; j < 50; ++j)
            //testUS.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testUS.erase(vec[i * j % 10000]);
    }
    auto end2 = std::chrono::steady_clock::now();

    auto start3 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testST.insert(vec[i * j % 10000]);
        //for (int j = 0; j < 50; ++j)
            //testST.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testST.erase(vec[i * j % 10000]);
    }
    auto end3 = std::chrono::steady_clock::now();

    std::cout << "hash_table: " << std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1).count()
              << std::endl;
    std::cout << "unordered_set: " << std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2).count()
              << std::endl;
    std::cout << "set: " << std::chrono::duration_cast<std::chrono::duration<double>>(end3 - start3).count()
              << std::endl;

    /*
    hash_table<int, hash1> testHT = hash_table<int, hash1>();
    std::unordered_set<int> testUS = std::unordered_set<int>();
    std::set<int> testST = std::set<int>();

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000);
    std::vector<int> initVals;
    for (int i = 0; i < 1000; ++i)
        initVals.push_back(dist(rng));
    for (int i = 0; i < 1000; ++i) {
        testHT.insert(initVals[i]);
        testUS.insert(initVals[i]);
        testST.insert(initVals[i]);
    }

    printHT(testHT, std::cout);

    auto it1 = testHT.begin();

    std::vector<int> vec;
    for (int i = 0; i < 100000; ++i)
        vec.push_back(dist(rng));
    std::vector<int> ranI;
    for (int i = 0; i < 50; ++i)
        ranI.push_back(dist(rng) % 2000);

    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testHT.insert(vec[i * j % 10000]);
        for (int j = 0; j < 50; ++j)
            testHT.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testHT.erase(vec[i * j % 10000]);
    }
    auto end1 = std::chrono::steady_clock::now();

    auto it2 = testHT.begin();

    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testUS.insert(vec[i * j % 10000]);
        for (int j = 0; j < 50; ++j)
            testUS.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testUS.erase(vec[i * j % 10000]);
    }
    auto end2 = std::chrono::steady_clock::now();

    auto start3 = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            testST.insert(vec[i * j % 10000]);
        for (int j = 0; j < 50; ++j)
            testST.find(ranI[j]);
        for (int j = 0; j < 100; ++j)
            testST.erase(vec[i * j % 10000]);
    }
    auto end3 = std::chrono::steady_clock::now();

    std::cout << "hash_table: " << std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1).count()
              << std::endl;
    std::cout << "unordered_set: " << std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2).count()
              << std::endl;
    std::cout << "set: " << std::chrono::duration_cast<std::chrono::duration<double>>(end3 - start3).count()
              << std::endl;
              */
}