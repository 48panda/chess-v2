#ifndef FEN_HPP
#define FEN_HPP

#include "main.hpp"

#include <string>

struct fen {
    std::string pieces;
    std::string activeColor;
    std::string castling;
    std::string enPassant;
    std::string halfMoveClock;
    std::string fullMoveNumber;
};

Game decodeFen(fen fenString);
#endif