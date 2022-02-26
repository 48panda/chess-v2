#include "searcher.hpp"
#include "lru.hpp"
#include <algorithm>

int negamax(Game &board, int depth, int alpha, int beta, lru_cache &cache, std::chrono::system_clock::time_point start, int maxTime, std::unordered_map<u64, move> &this_best, std::unordered_map<u64, move> &last_best) {
    if (depth == 0) {
        if (board.whiteToMove) {
            return  board.evaluateGameState();
        } else {
            return -board.evaluateGameState();
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    if (microseconds > maxTime) {
        return -0x7FFFFFFF;
    }
    int cacheres = cache.get_node(board.hash);
    if (cacheres != lru_cache::get_failed) { // If cache get did not fail, return cache get result
        return cacheres;
    }
    std::vector<move> childNodes = board.getLegalMoves();
    if (childNodes.size() == 0) {
        if (board.isInCheck(true)) {
            return -0x7FFFFFFE;
        } else {
            return 0;
        }
    }
    int best = -0x7FFFFFFE;
    move bestMove;
    if (depth != 1) {
        auto res = last_best.find(board.hash);
        if (res != last_best.end()){
            move m = res->second;
            board.doMove(m);
            int res = -negamax(board, depth - 1, -beta, -alpha, cache, start, maxTime, this_best, last_best);
            if (res == 0x7FFFFFFF) {
                return -res;
            }
            board.undoMove(m);
            bestMove = m;
            best = res;
            alpha = std::max(alpha, best);
        }
    }
    for (move m: childNodes) {
        board.doMove(m);
        int res = -negamax(board, depth - 1, -beta, -alpha, cache, start, maxTime, this_best, last_best);
        if (res == 0x7FFFFFFF) {
            return -res;
        }
        board.undoMove(m);
        if (res >= best) {
            bestMove = m;
            best = res;
        }
        alpha = std::max(alpha, best);
        if (alpha >= beta) {
            break;
        }
    }
    //this_best.insert({board.hash, bestMove});
    cache.add_node(board.hash, best); // Add to cache
    return best;

}

searchReturn search(Game &board, int depth, std::chrono::system_clock::time_point start, int maxTime, std::unordered_map<u64, move> &last_best) {
    std::unordered_map<u64, move> this_best;
    int alpha = -0x7FFFFFFF;
    int beta = 0x7FFFFFFF;
    int best = -0x7FFFFFFF;
    lru_cache cache(100000);
    move bestMove;
    for (move m: board.getLegalMoves()) {
        board.doMove(m);
        int res = -negamax(board, depth - 1, -beta, -alpha, cache, start, maxTime, this_best, last_best);
        if (res == 0x7FFFFFFF) {
            board.undoMove(m);
            return searchReturn{move{255, 255, 255, 0},this_best};
        }
        board.undoMove(m);
        if (res >= best) {
            bestMove = m;
            best = res;
        }
        alpha = std::max(alpha, best);
    }
    return searchReturn{bestMove, this_best};
}
