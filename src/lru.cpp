#include "lru.hpp"

lru_cache::lru_cache(int new_max_size) {
    max_size = new_max_size;
};
lru_cache::node::node(u64 new_key, int new_value) {
    key = new_key;
    value = new_value;
    prev = nullptr;
    next = nullptr;
};
void lru_cache::add_node(u64 key, int value) {
    node* new_node = new node(key, value);
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
    map.insert({key, new_node});
    if (size == 0) {
        tail = new_node;
    }
    size++;
    while (size > max_size) {
        map.erase(tail->key);
        tail = tail->prev;
        tail->next = nullptr;
        size--;
    }
}
int lru_cache::get_node(u64 key) {
    auto findResult = map.find(key);
    if (findResult == map.end()) {
        return get_failed;
    }
    node* found_node = findResult->second;
    if (found_node == head) {
        return found_node->value;
    }
    if (found_node == tail) {
        tail = found_node->prev;
        tail->next = nullptr;
        found_node->prev = nullptr;
        found_node->next = head;
        head->prev = found_node;
        head = found_node;
        return found_node->value;
    }
    // put the node at the front of the list
    found_node->prev->next = found_node->next;
    found_node->next->prev = found_node->prev;
    found_node->prev = nullptr;
    found_node->next = head;
    head->prev = found_node;
    head = found_node;
    return found_node->value;
}