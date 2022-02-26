#ifndef SEARCHER
#define SEARCHER

#include "main.hpp"
#include "lru.hpp"

struct searchReturn {
    move m;
    std::unordered_map<u64, move> last_iter;
};

searchReturn search(Game &board, int depth, std::chrono::system_clock::time_point start, int maxTime, std::unordered_map<u64, move> &last_best);

#endif
