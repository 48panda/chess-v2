#include "main.hpp"
#include "fen.hpp"
#include "pregen.hpp"

Game::Game(u8 (&new_board)[64], bool new_whiteToMove, u8 castling, u8 new_enPassant, u8 new_halfMoveClock, u16 new_fullMoveNumber, u8 new_whiteKingIndex, u8 new_blackKingIndex) {
    for (int i = 0; i < 64; i++) {
        board[i] = new_board[i];
    }
    whiteToMove = new_whiteToMove;
    if (castling & 0x1) { whiteCastleKingSide = true;} else { whiteCastleKingSide = false;}
    if (castling & 0x2) {whiteCastleQueenSide = true;} else {whiteCastleQueenSide = false;}
    if (castling & 0x4) { blackCastleKingSide = true;} else { blackCastleKingSide = false;}
    if (castling & 0x8) {blackCastleQueenSide = true;} else {blackCastleQueenSide = false;}
    enPassant = new_enPassant;
    halfMoveClock = new_halfMoveClock;
    fullMoveNumber = new_fullMoveNumber;
    whiteKingIndex = new_whiteKingIndex;
    blackKingIndex = new_blackKingIndex;
    genPregenData();
}

char getPieceFromValue(u8 value) {
    switch (value) {
        case 0b10000101:
            return 'R';
        case 0b10000110:
            return 'B';
        case 0b10000111:
            return 'Q';
        case 0b10001000:
            return 'K';
        case 0b10010000:
            return 'N';
        case 0b10100000:
            return 'P';
        case 0b01000101:
            return 'r';
        case 0b01000110:
            return 'b';
        case 0b01000111:
            return 'q';
        case 0b01001000:
            return 'k';
        case 0b01010000:
            return 'n';
        case 0b01100000:
            return 'p';
        default:
            return '.';

    }
}

void Game::printBoard() {
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << getPieceFromValue(board[i]) << " ";
    }
    std::cout << std::endl;
}
int countBoards(Game &board, int depth, bool first) {
    int count = 0;
    if (depth == 1 && !first) {
        return board.getLegalMoves().size();
    }
    for (move m: board.getLegalMoves()) {
        Game oldBoard(board);
        board.doMove(m);
        /*if (m.from == 7 && m.to == 39) {
            board.printBoard();
        }*/
        int res = countBoards(board, depth - 1, false);
        if (first) {
            m.printMove(board);
            std::cout << ": " << res << std::endl;
        }
        count += res;
        board.undoMove(m);
        bool hasBroken = false;
        for (int i = 0; i < 64; i++) {
            if (board.board[i] != oldBoard.board[i]) {
                board.printBoard();
                oldBoard.printBoard();
                hasBroken = true;
                break;
            }
        }
        if (hasBroken) {
            continue;
        }
        if (board.enPassant != oldBoard.enPassant) {
            board.printBoard();
            oldBoard.printBoard();
            hasBroken = true;
            continue;
        }
        if (board.blackCastleKingSide != oldBoard.blackCastleKingSide || board.blackCastleQueenSide != oldBoard.blackCastleQueenSide || board.whiteCastleKingSide != oldBoard.whiteCastleKingSide || board.whiteCastleQueenSide != oldBoard.whiteCastleQueenSide) {
            board.printBoard();
            oldBoard.printBoard();
            std::cout << board.blackCastleKingSide << " " << board.blackCastleQueenSide << " " << board.whiteCastleKingSide << " " << board.whiteCastleQueenSide << std::endl;
            std::cout << oldBoard.blackCastleKingSide << " " << oldBoard.blackCastleQueenSide << " " << oldBoard.whiteCastleKingSide << " " << oldBoard.whiteCastleQueenSide << std::endl;
            hasBroken = true;
            continue;
        }

    }
    return count;
}

bool Game::isInCheck(bool switchPlayer = false) {
    if (switchPlayer) {
        whiteToMove = !whiteToMove;
    }
    if (whiteToMove) {
        for (move m: genMoves()) {
            if (m.to == blackKingIndex) {
                if (switchPlayer) {
                    whiteToMove = !whiteToMove;
                }
                return true;
            }
        }
    } else {
        for (move m: genMoves()) {
            if (m.to == whiteKingIndex) {
                if (switchPlayer) {
                    whiteToMove = !whiteToMove;
                }
                return true;
            }
        }
    }
    if (switchPlayer) {
        whiteToMove = !whiteToMove;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cout << "Usage: " << argv[0] << " <fen string>" << std::endl;
        return 1;
    }
    std::cout << "Converting FEN string..." << std::endl;

    Game board = decodeFen(fen{argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]});
    
    std::cout << "Beginning search..." << std::endl;

    //std::cout << countBoards(board, 1, false) << std::endl;
    //std::cout << "Search depth 1 complete." << std::endl;
    std::cout << countBoards(board, 2, true) << std::endl;
    std::cout << "Search depth 2 complete." << std::endl;
    std::cout << countBoards(board, 3, true) << std::endl;
    std::cout << "Search depth 3 complete." << std::endl;
    std::cout << countBoards(board, 4, true) << std::endl;
    std::cout << "Search depth 4 complete." << std::endl;
    std::cout << countBoards(board, 5, true) << std::endl;
    std::cout << "Search depth 5 complete." << std::endl;
    std::cout << countBoards(board, 6, true) << std::endl;
    std::cout << "Search depth 6 complete." << std::endl;
    


    return 0;
}