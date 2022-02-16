#ifndef SEARCHER
#define SEARCHER

#include "main.hpp"
#include "lru.hpp"

int negamax(Game &board, int depth, int alpha, int beta, lru_cache cache);
move search(Game &board, int depth);

#endif
