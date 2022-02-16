#include "searcher.hpp"
#include "lru.hpp"
#include <algorithm>


int negamax(Game &board, int depth, int alpha, int beta, lru_cache &cache) {
    if (depth == 0) {
        return board.evaluateGameState();
    }
    int cacheres = cache.get_node(board.hash);
    if (cacheres != lru_cache::get_failed) { // If cache get did not fail, return cache get result
        return cacheres
    }
    std::vector<move> childNodes = board.getLegalMoves();
    if (childNodes.size() == 0) {
        if (board.isInCheck(true)) {
            std::cout << "Checkmate found!" << std::endl;
            return -0x7FFFFFFF;
        } else {
            return 0;
        }
    }
    int best = -0x7FFFFFFF;
    for (move m: childNodes) {
        board.doMove(m);
        int res = -negamax(board, depth - 1, -beta, -alpha);
        board.undoMove(m);
        if (res > best) {
            best = res;
        }
        alpha = std::max(alpha, best);
        if (alpha >= beta) {
            break;
        }
    }
    cache.add_node(board.hash, best); // Add to cache
    return best;

}

move search(Game &board, int depth) {
    int alpha = -0x7FFFFFFF;
    int beta = 0x7FFFFFFF;
    int best = -0x7FFFFFFF;
    lru_cache cache(1000);
    move bestMove;
    for (move m: board.getLegalMoves()) {
        board.doMove(m);
        int res = -negamax(board, depth - 1, -beta, -alpha, cache);
        board.undoMove(m);
        if (res > best) {
            bestMove = m;
            best = res;
        }
        alpha = std::max(alpha, best);
    }
    return bestMove;
}
