#ifndef MOVES_HPP
#define MOVES_HPP

#include "main.hpp"
#include <vector>

struct move {
    u8 from;
    u8 to;
    u8 captured;
    int flags;
    u64 hash = 0;
    void printMove();
    bool whiteCastleKingSide = false;
    bool whiteCastleQueenSide = false;
    bool blackCastleKingSide = false;
    bool blackCastleQueenSide = false;
    u8 enPassant = 0;
    u8 whiteKingIndex = 65;
    u8 blackKingIndex = 65;
    
};

// move flags: 0x80: en passant
// last 6 bits will be the location of the captured piece if this flag is set
//             0x40: promotion
// last 6 bits will be the piece to promote to if this flag is set (color is the same as the piece that moved)
//             0x20: castling
//             0x10: set en passant
#endif