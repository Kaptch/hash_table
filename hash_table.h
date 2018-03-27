//
// Created by kaptch on 3/27/18.
//

#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include <variant>
#include <functional>

template <class Key, class Hash = std::hash<Key>> class hash_table {
    struct _Hashtable_node {
        _Hashtable_node *_next;
        Key _key;
        _Hashtable_node(_Hashtable_node *_n, Key _k) : _next(_n), _key(_k) {}
    };

    Hash hash;
    using node = _Hashtable_node *;
    std::vector<node> _vec;
    unsigned int _size;
    unsigned int _max_size;

public:
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, Key> {
    public:
        using node = _Hashtable_node *;
        node ptr;
        const hash_table *ht;
        const_iterator(node x, const hash_table *y) : ptr(x), ht(y) {}
        const_iterator(const const_iterator &mit) : ptr(mit.ptr) {}
        const_iterator &operator++() {
            if (ptr->_next)
                ptr = ptr->_next;
            else {
                unsigned int index = ht->hash(ptr->_key) + 1;
                ptr = ht->_vec[index];
                while (index < 2000 && !ptr)
                    ptr = ht->_vec[++index];
            }
            return *this;
        }
        const_iterator &operator--() {
            unsigned int index = ht->hash(ptr->_key);
            if (ptr == ht->_vec[index])
                while (index > 0 && !ptr)
                    ptr = ht->_vec[--index];
            else {
                node temp = ht->_vec[index];
                while (temp->_next != ptr)
                    temp = temp->_next;
                ptr = temp;
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            operator++();
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }

        const Key &operator*() {
            node q = this->ptr;
            if (q)
                return q->_key;
        }
    };

    hash_table() : _size(0), _max_size(2000), _vec(2000, nullptr) {}
    unsigned int size() const {
        return _size;
    }
    bool empty() const {
        return _size == 0;
    }
    const_iterator find(const Key &k) const {
        return const_iterator(_vec[hash(k)], this);
    }
    void erase(const_iterator pos) {
        delete pos.ptr;
        --_size;
        return;
    }
    void erase(const Key &k) {
        const_iterator it = find(k);
        if (it != end())
            erase(it);
        else
            return;
    }
    const_iterator insert(const Key &k) {
        if (_size < _max_size) {
            _vec[hash(k)] = new _Hashtable_node(_vec[hash(k)], k);
            ++_size;
            return const_iterator(_vec[hash(k)], this);
        } else
            return end();
    }
    const_iterator begin() const {
        return const_iterator(*_vec.begin(), this);
    }
    const_iterator end() const {
        //TODO FIX
        return const_iterator(nullptr, this);
    }
};

#endif //HASH_TABLE_HASH_TABLE_H
