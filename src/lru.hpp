#ifndef LRU
#define LRU

#include "main.hpp"
#include <unordered_map>

class lru_cache {
    public:
        class node {
            public:
                node* prev;
                node* next;
                u64 key;
                int value;
                node(u64 new_key, int new_value);
        };
        node* head;
        node* tail;
        int max_size;
        int size = 0;
        std::unordered_map<u64, node*> map;
        lru_cache(int new_max_size);
        void add_node(u64 key, int value);
        int get_node(u64 key);
        int get_failed = 0x7FFFFFFF;
};

#endif