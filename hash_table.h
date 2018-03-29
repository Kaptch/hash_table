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

    Hash hash5;
    int hash (Key i) const {
        return hash5(i) % 2000;
    }
    using node = _Hashtable_node *;
    std::vector<node> _vec;
    size_t _size;
    size_t _max_size;
    typename std::vector<node>::const_iterator _first;

public:
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, Key> {
    public:
        using node = _Hashtable_node *;
        typename std::vector<node>::const_iterator iter;
        node ptr;
        const hash_table *ht;

        const_iterator(typename std::vector<node>::const_iterator i, node x, const hash_table *y) : iter(i), ptr(x),
                                                                                                    ht(y) {}

        const_iterator(const const_iterator &mit) : iter(mit.iter), ptr(mit.ptr), ht(mit.ht) {}
        const_iterator &operator++() {
            if (ptr->_next)
                ptr = ptr->_next;
            else {
                ++iter;
                if (iter == ht->_vec.end()) {
                    ptr = nullptr;
                    return *this;
                }
                while (*iter == nullptr)
                    if (iter == ht->_vec.end()) {
                        ptr = nullptr;
                        return *this;
                    } else
                        ++iter;
                ptr = *iter;
            }
            return *this;
        }
        const_iterator &operator--() {
            if (ptr == *iter) {
                --iter;
                while (*iter == nullptr)
                    --iter;
                ptr = *iter;
                while (ptr->_next)
                    ptr = ptr->_next;
            }
            else {
                node temp = *iter;
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

        bool operator!=(const const_iterator &rhs) const { return !this->operator==(rhs); }

        const Key &operator*() {
            node q = this->ptr;
            if (q)
                return q->_key;
        }
    };

    explicit hash_table(size_t ms = 2000) : _size(0), _max_size(ms), _vec(ms, nullptr), _first(_vec.end()) {}

    size_t size() const {
        return _size;
    }
    bool empty() const {
        return _size == 0;
    }
    const_iterator find(const Key &k) const {
        return const_iterator(_vec.begin() + hash(k), _vec[hash(k)], this);
    }

    const_iterator erase(const_iterator pos) {
        node tmp = *(pos.iter);
        if (pos.iter == _first)
            while (*_first == nullptr)
                ++_first;
        if (tmp == pos.ptr) {
            _vec[pos.ht->hash(tmp->_key)] = pos.ptr->_next;
            delete pos.ptr;
            --_size;
            return const_iterator(pos.iter, *pos.iter, this);
        } else {
            while (tmp->_next != pos.ptr)
                tmp = tmp->_next;
            tmp->_next = pos.ptr->_next;
            delete pos.ptr;
            --_size;
            return const_iterator(pos.iter, *pos.iter, this);
        }
    }

    size_t erase(const Key &k) {
        const_iterator it = find(k);
        if (it != end()) {
            erase(it);
            return 1;
        }
        else
            return 0;
    }
    const_iterator insert(const Key &k) {
        if (_size < _max_size) {
            _vec[hash(k)] = new _Hashtable_node(_vec[hash(k)], k);
            ++_size;
            if (_vec.begin() + hash(k) < _first)
                _first = _vec.begin() + hash(k);
            return const_iterator(_vec.begin() + hash(k), _vec[hash(k)], this);
        } else
            return end();
    }
    const_iterator begin() const {
        return const_iterator(_first, *_first, this);
    }
    const_iterator end() const {
        return const_iterator(_vec.end(), nullptr, this);
    }
};

#endif //HASH_TABLE_HASH_TABLE_H
