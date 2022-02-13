#include "searcher.hpp"

#include <algorithm>


int negamax(Game &board, int depth, int alpha, int beta) {
    if (depth == 0) {
        return board.evaluateGameState();
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
    return best;

}

move search(Game &board, int depth) {
    int alpha = -0x7FFFFFFF;
    int beta = 0x7FFFFFFF;
    int best = -0x7FFFFFFF;
    move bestMove;
    for (move m: board.getLegalMoves()) {
        board.doMove(m);
        int res = -negamax(board, depth - 1, -beta, -alpha);
        board.undoMove(m);
        if (res > best) {
            bestMove = m;
            best = res;
        }
        alpha = std::max(alpha, best);
    }
    return bestMove;
}