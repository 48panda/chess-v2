// Define all the structs and stuffs
#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

using u64 = std::uint_fast64_t;
using u32 = std::uint_fast32_t;
using u16 = std::uint_fast16_t;
using u8 = std::uint_fast8_t;
using s64 = std::int_fast64_t;
using s32 = std::int_fast32_t;
using s16 = std::int_fast16_t;
using s8 = std::int_fast8_t;


// flags:
// 0x1: Slide orthogonally
// 0x2: Slide diagonally
// 0x4: Slide any direction
// 0x8: King
// 0x10: Knight
// 0x20: pawn
// 0x40: black
// 0x80: white

/* this means that: 

 0b10000101 is white rook
 0b10000110 is white bishop
 0b10000111 is white queen
 0b10001000 is white king
 0b10010000 is white knight
 0b10100000 is white pawn

 0b01000101 is black rook
 0b01000110 is black bishop
 0b01000111 is black queen
 0b01001000 is black king
 0b01010000 is black knight
 0b01100000 is black pawn

 0b00000000 is empty square

*/
class move;

class Game {
    public:
      u8 board[64];
      char tileNames[64][3];
      bool whiteToMove;
    //private:

      bool whiteCastleKingSide;
      bool whiteCastleQueenSide;
      bool blackCastleKingSide;
      bool blackCastleQueenSide;
      
      u8 whiteKingIndex;
      u8 blackKingIndex;

      u8 enPassant;
      u8 halfMoveClock;
      u16 fullMoveNumber;
      s8 pregen[16][64];
      void genPregenData();
    public:
      Game(u8 (&new_board)[64], bool whiteToMove, u8 castling, u8 new_enPassant, u8 new_halfMoveClock, u16 new_fullMoveNumber, u8 new_whiteKingIndex, u8 new_blackKingIndex);
      void printBoard();
      std::vector<move> genMoves();
      std::vector<move> getLegalMoves();
      void doMove(move &m);
      void undoMove(move &m);
      bool isInCheck(bool logging);

};

#include "pregen.hpp"
#include "moves.hpp"

#endif