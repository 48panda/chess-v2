#ifndef SEARCHER
#define SEARCHER

#include "main.hpp"

int negamax(Game &board, int depth, int alpha, int beta);
move search(Game &board, int depth);

#endif