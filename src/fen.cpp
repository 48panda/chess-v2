#include "fen.hpp"
#include "main.hpp"
#include <exception>
#include <sstream>

Game decodeFen(fen fenString) {
    u8 board[64];
    int i = 0;
    int pos = -1;
    u8 whiteKingIndex = 65;
    u8 blackKingIndex = 65;
    while(i < 64) {
        pos++;
        if (i==64) {
            break;
        }
        char charofintrest = fenString.pieces[pos];
        if (charofintrest == '/') {
            continue;
        }
        if (charofintrest >= '1' && charofintrest <= '8') {
            int numberofspaces = charofintrest - '0';
            while (numberofspaces > 0) {
                board[i] = 0;
                i++;
                numberofspaces--;
            }
            continue;
        }
               if (charofintrest == 'R') {
            board[i] = 0b10000101;
        } else if (charofintrest == 'B') {
            board[i] = 0b10000110;
        } else if (charofintrest == 'Q') {
            board[i] = 0b10000111;
        } else if (charofintrest == 'K') {
            board[i] = 0b10001000;
            whiteKingIndex = i;
        } else if (charofintrest == 'N') {
            board[i] = 0b10010000;
        } else if (charofintrest == 'P') {
            board[i] = 0b10100000;
        } else if (charofintrest == 'r') {
            board[i] = 0b01000101;
        } else if (charofintrest == 'b') {
            board[i] = 0b01000110;
        } else if (charofintrest == 'q') {
            board[i] = 0b01000111;
        } else if (charofintrest == 'k') {
            board[i] = 0b01001000;
            blackKingIndex = i;
        } else if (charofintrest == 'n') {
            board[i] = 0b01010000;
        } else if (charofintrest == 'p') {
            board[i] = 0b01100000;
        } else if (charofintrest == ' ') {
            break;
        } else {
            std::stringstream ss;
            ss << "Invalid character in FEN: >" << charofintrest << "<" << pos;
            throw std::invalid_argument(ss.str());
        }
        i++;
    }
    bool whiteToMove;
    if (fenString.activeColor == "w") {
        whiteToMove = true;
    } else if (fenString.activeColor == "b") {
        whiteToMove = false;
    } else {
        throw std::invalid_argument("Invalid active color in FEN string: >" + fenString.activeColor + "<");
    }
    u8 castling = 0;
    if (fenString.castling == "-") {
        castling = 0;
    } else {
        if (fenString.castling.find("K") != std::string::npos) {
            castling |= 0x1;
        }
        if (fenString.castling.find("Q") != std::string::npos) {
            castling |= 0x2;
        }
        if (fenString.castling.find("k") != std::string::npos) {
            castling |= 0x4;
        }
        if (fenString.castling.find("q") != std::string::npos) {
            castling |= 0x8;
        }
    }

    u8 enPassant = 0;
    if (fenString.enPassant == "-") {
        enPassant = 0;
    } else {
        if (fenString.enPassant.length() != 2) {
            throw std::invalid_argument("Invalid en passant in FEN string: >" + fenString.enPassant + "<");
        }
        if (fenString.enPassant[0] >= 'a' && fenString.enPassant[0] <= 'h' && fenString.enPassant[1] >= '1' && fenString.enPassant[1] <= '8') {
            enPassant = ((fenString.enPassant[1] - '0') - 1) * 8 + (fenString.enPassant[0] - 'a');
        } else {
            throw std::invalid_argument("Invalid en passant in FEN string: >" + fenString.enPassant + "<");
        }
    }
    u8 halfMoveClock = std::stoi(fenString.halfMoveClock);
    u8 fullMoveNumber = std::stoi(fenString.fullMoveNumber);
    return Game(board, whiteToMove, castling, enPassant, halfMoveClock, fullMoveNumber, whiteKingIndex, blackKingIndex);
};