#ifndef SEARCHER
#define SEARCHER

#include "main.hpp"
#include "lru.hpp"

int negamax(Game &board, int depth, int alpha, int beta, lru_cache &cache, std::chrono::system_clock::time_point start, int maxTime);
move search(Game &board, int depth, std::chrono::system_clock::time_point start, int maxTime);

#endif
