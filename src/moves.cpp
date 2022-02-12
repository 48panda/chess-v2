#include "moves.hpp"

void move::printMove(Game &board) {
    std::cout << board.tileNames[from] << "=>" << board.tileNames[to];
}

std::vector<move> Game::genMoves() {
    std::vector<move> moves;
    for(u8 i = 0; i < 64; i++) {
        u8 piece = board[i];
        if (piece == 0) {
            continue;
        }
        u8 isWhite = piece & 0x80;
        if ((bool)(isWhite) != whiteToMove) {
            continue;
        }
        u8 myPieceCheck = isWhite ? 0x80 : 0x40;
        if (piece & 0x4) { // sliding pieces
            s8 directionOffsets[8] = {1,-1, 8, -8, 9, -9, 7, -7};
            u8 startIndex = piece & 0x1 ? 0 : 4;
            u8 endIndex = piece & 0x2 ? 8 : 4;
            for (u8 dir = startIndex; dir < endIndex; dir++) {
                s8 directionOffset = directionOffsets[dir];
                s8 distanceFromEdge = pregen[dir][i];
                s8 pos = i + directionOffset;
                for (u8 d = 0; d < distanceFromEdge; d++) {
                    if (board[pos] & myPieceCheck) {
                        break;
                    } else if (board[pos] == 0) {
                        moves.push_back(move{i, (u8)(pos), 0, 0});
                    } else {
                        moves.push_back(move{i, (u8)(pos), board[pos], 0});
                        break;
                    }
                    pos += directionOffset;
                }
            }
        } else if (piece & 0x18) { // King or Knight
            s8 directionOffsets[16] = {1,-1, 8, -8, 9, -9, 7, -7, 10, -10, 6, -6, 17, -17, 15, -15};
            u8 startIndex = piece & 0x8 ? 0 : 8;
            u8 endIndex = piece & 0x10 ? 16 : 8;
            for (u8 dir = startIndex; dir < endIndex; dir++) {
                s8 pos = i + directionOffsets[dir];
                if (pregen[dir][i]) {
                    if (!(board[pos] & myPieceCheck)) {
                        moves.push_back(move{i, (u8)(pos), board[pos], 0});
                    }
                }
            }
            if (piece & 0x8) {
                if (i == 4 && blackCastleQueenSide && board[0] == 0x45) {
                    if (board[3] == 0 && board[2] == 0 && board[1] == 0) {
                        moves.push_back(move{4, 2, 0, 0x20});
                    }
                }
                if (i == 4 && blackCastleKingSide && board[7] == 0x45) {
                    if (board[5] == 0 && board[6] == 0) {
                        moves.push_back(move{4, 6, 0, 0x20});
                    }
                }
                if (i == 60 && whiteCastleQueenSide && board[56] == 0b10000101) {
                    if (board[59] == 0 && board[58] == 0 && board[57] == 0) {
                        moves.push_back(move{60, 58, 0, 0x20});
                    }
                }
                if (i == 60 && whiteCastleKingSide && board[63] == 0b10000101) {
                    if (board[61] == 0 && board[62] == 0) {
                        moves.push_back(move{60, 62, 0, 0x20});
                    }
                }
            }
        } else if (piece & 0x20) {
            if (!isWhite) {
                if (pregen[2][i] > 1) {
                    if (board[i + 8] == 0) {
                        moves.push_back(move{i, (u8)(i + 8), 0, 0});
                        if (pregen[3][i] == 1) {
                            if (board[i + 16] == 0) {
                                moves.push_back(move{i, (u8)(i + 16), 0, 0x10});
                            }
                        }
                    }
                    if (pregen[0][i] && board[i + 9] & 0x80) {
                        moves.push_back(move{i, (u8)(i + 9), board[i + 9], 0});
                    }
                    if (pregen[0][i] && i + 9 == enPassant) {
                        moves.push_back(move{i, (u8)(i + 9), board[i + 1], 0x80 | (i + 1)});
                    }
                    if (pregen[1][i] && board[i + 7] & 0x80) {
                        moves.push_back(move{i, (u8)(i + 7), board[i + 7], 0});
                    }
                    if (pregen[1][i] && i + 7 == enPassant) {
                        moves.push_back(move{i, (u8)(i + 7), board[i - 1], 0x80 | (i - 1)});
                    }
                } else {
                    if (board[i + 8] == 0) {
                        moves.push_back(move{i, (u8)(i + 8), 0, 0x45});
                        moves.push_back(move{i, (u8)(i + 8), 0, 0x46});
                        moves.push_back(move{i, (u8)(i + 8), 0, 0x47});
                        moves.push_back(move{i, (u8)(i + 8), 0, 0x50});
                    }
                    if (pregen[0][i] && board[i + 9] & 0x80) {
                        moves.push_back(move{i, (u8)(i + 9), board[i + 9], 0x45});
                        moves.push_back(move{i, (u8)(i + 9), board[i + 9], 0x46});
                        moves.push_back(move{i, (u8)(i + 9), board[i + 9], 0x47});
                        moves.push_back(move{i, (u8)(i + 9), board[i + 9], 0x50});
                    }
                    if (pregen[1][i] && board[i + 7] & 0x80) {
                        moves.push_back(move{i, (u8)(i + 7), board[i + 7], 0x45});
                        moves.push_back(move{i, (u8)(i + 7), board[i + 7], 0x46});
                        moves.push_back(move{i, (u8)(i + 7), board[i + 7], 0x47});
                        moves.push_back(move{i, (u8)(i + 7), board[i + 7], 0x50});
                    }
                }
            } else {
                if (pregen[3][i] > 1) {
                    if (board[i - 8] == 0) {
                        moves.push_back(move{i, (u8)(i - 8), 0, 0});
                        if (pregen[2][i] == 1) {
                            if (board[i - 16] == 0) {
                                moves.push_back(move{i, (u8)(i - 16), 0, 0x10});
                            }
                        }
                    }
                    if (pregen[0][i] && board[i - 7] & 0x40) {
                        moves.push_back(move{i, (u8)(i - 7), board[i - 7], 0});
                    }
                    if (pregen[0][i] && i - 7 == enPassant) {
                        moves.push_back(move{i, (u8)(i - 7), board[i + 1], 0x80 | (i + 1)});
                    }
                    if (pregen[1][i] && board[i - 9] & 0x40) {
                        moves.push_back(move{i, (u8)(i - 9), board[i - 9], 0});
                    }
                    if (pregen[1][i] && i - 9 == enPassant) {
                        moves.push_back(move{i, (u8)(i - 9), board[i - 1], 0x80 | (i - 1)});
                    }
                } else {
                    if(board[i - 8] == 0) {
                        moves.push_back(move{i, (u8)(i - 8), 0, 0x45});
                        moves.push_back(move{i, (u8)(i - 8), 0, 0x46});
                        moves.push_back(move{i, (u8)(i - 8), 0, 0x47});
                        moves.push_back(move{i, (u8)(i - 8), 0, 0x50});
                    }
                    if (pregen[1][i] && board[i - 9] & 0x40) {
                        moves.push_back(move{i, (u8)(i - 9), board[i - 9], 0x45});
                        moves.push_back(move{i, (u8)(i - 9), board[i - 9], 0x46});
                        moves.push_back(move{i, (u8)(i - 9), board[i - 9], 0x47});
                        moves.push_back(move{i, (u8)(i - 9), board[i - 9], 0x50});
                    }
                    if (pregen[0][i] && board[i - 7] & 0x40) {
                        moves.push_back(move{i, (u8)(i - 7), board[i - 7], 0x45});
                        moves.push_back(move{i, (u8)(i - 7), board[i - 7], 0x46});
                        moves.push_back(move{i, (u8)(i - 7), board[i - 7], 0x47});
                        moves.push_back(move{i, (u8)(i - 7), board[i - 7], 0x50});
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<move> Game::getLegalMoves() {
    std::vector<move> moves = genMoves();
    std::vector<move> legalMoves;
    for (move m : moves) {
        if (m.flags == 0x20 && isInCheck(true)) {
            continue;
        }
        doMove(m);
        if (!isInCheck(false)) {
            if (m.flags == 0x20) {
                for (move m2: legalMoves) {
                    if (m2.from == m.from && m2.to == (m.to + m.from) / 2) {
                        legalMoves.push_back(m);
                        break;
                    }
                }

            } else{
                legalMoves.push_back(m);
            }
        }
        undoMove(m);
    }
    return legalMoves;
}
char getPieceIndex(u8 value) {
    switch (value) {
        case 0b10000101:
            return 0;
        case 0b10000110:
            return 1;
        case 0b10000111:
            return 2;
        case 0b10001000:
            return 3;
        case 0b10010000:
            return 4;
        case 0b10100000:
            return 5;
        case 0b01000101:
            return 6;
        case 0b01000110:
            return 7;
        case 0b01000111:
            return 8;
        case 0b01001000:
            return 9;
        case 0b01010000:
            return 10;
        case 0b01100000:
            return 11;
        default:
            return 12;

    }
}
void Game::doMove(move &m) {
    m.hash = hash;
    m.blackCastleKingSide = blackCastleKingSide;
    m.blackCastleQueenSide = blackCastleQueenSide;
    m.whiteCastleKingSide = whiteCastleKingSide;
    m.whiteCastleQueenSide = whiteCastleQueenSide;
    m.enPassant = enPassant;
    m.whiteKingIndex = whiteKingIndex;
    m.blackKingIndex = blackKingIndex;
    enPassant = 65;
    whiteToMove = !whiteToMove;
    board[m.to] = board[m.from];
    board[m.from] = 0;    
    if (m.flags & 0x80) {
        board[m.flags & 0x7F] = 0;
    }
    else if (m.flags & 0x40) {
        board[m.to] = (board[m.to] & 0xC0) | (m.flags & 0x3F);
    }
    else if (m.flags & 0x20) {
        if (m.to == 2) {
            board[3] = board[0];
            board[0] = 0;
        } else if (m.to == 6) {
            board[5] = board[7];
            board[7] = 0;
        } else if (m.to == 58) {
            board[59] = board[56];
            board[56] = 0;
        } else if (m.to == 62) {
            board[61] = board[63];
            board[63] = 0;
        }
    }
    else if (m.flags & 0x10) {
        if (m.to < 32) {
            enPassant = m.from + 8;
        } else {
            enPassant = m.from - 8;
        }
    }
    if (board[m.to] & 0x8) {
        if (board[m.to] & 0x80) {
            whiteCastleKingSide = false;
            whiteCastleQueenSide = false;
            whiteKingIndex = m.to;
        } else {
            blackCastleKingSide = false;
            blackCastleQueenSide = false;
            blackKingIndex = m.to;
        }
    }
    if (board[m.to] & 0x3 == 1) {
        if (m.from == 0) {
            blackCastleQueenSide = false;
        }
        if (m.from == 7) {
            blackCastleKingSide = false;
        }
        if (m.from == 56) {
            whiteCastleQueenSide = false;
        }
        if (m.from == 63) {
            whiteCastleKingSide = false;
        }
    }
    if (m.captured & 0x3 == 1) {
        if (m.to == 0) {
            blackCastleQueenSide = false;
        }
        if (m.to == 7) {
            blackCastleKingSide = false;
        }
        if (m.to == 56) {
            whiteCastleQueenSide = false;
        }
        if (m.to == 63) {
            whiteCastleKingSide = false;
        }
    }
    // Zobrist hashing
    hash ^= hashTable[m.from][getPieceIndex(board[m.to])];
    hash ^= hashTable[m.from][12];
    hash ^= hashTable[m.to][getPieceIndex(board[m.to])];
    if (m.flags & 0x80) {
        hash ^= hashTable[m.flags & 0x7F][getPieceIndex(m.captured)];
    } else {
        hash ^= hashTable[m.to][getPieceIndex(m.captured)];
    }
    if (whiteCastleKingSide != m.whiteCastleKingSide) {
        hash ^= hashTable[56][13];
    }
    if (whiteCastleQueenSide != m.whiteCastleQueenSide) {
        hash ^= hashTable[56][14];
    }
    if (blackCastleKingSide != m.blackCastleKingSide) {
        hash ^= hashTable[0][13];
    }
    if (blackCastleQueenSide != m.blackCastleQueenSide) {
        hash ^= hashTable[0][14];
    }
    if (enPassant != m.enPassant) {
        if (m.enPassant != 65) {
            hash ^= hashTable[m.enPassant][15];
        }
        if (enPassant != 65) {
            hash ^= hashTable[enPassant][15];
        }
    }
}

void Game::undoMove(move &m) {
    hash = m.hash;
    blackCastleQueenSide = m.blackCastleQueenSide;
    blackCastleKingSide = m.blackCastleKingSide;
    whiteCastleQueenSide = m.whiteCastleQueenSide;
    whiteCastleKingSide = m.whiteCastleKingSide;
    enPassant = m.enPassant;
    whiteKingIndex = m.whiteKingIndex;
    blackKingIndex = m.blackKingIndex;
    whiteToMove = !whiteToMove;
    board[m.from] = board[m.to];
    if (m.flags & 0x80) {
        board[m.flags & 0x7F] = m.captured;
        board[m.to] = 0;
    } else {
        board[m.to] = m.captured;
        if (m.flags & 0x40) {
            board[m.from] = (board[m.from] & 0b11000000) | 0x20;
        } else if ( m.flags & 0x20) {
            if (m.to == 2) {
                board[0] = board[3];
                board[3] = 0;
            } else if (m.to == 6) {
                board[7] = board[5];
                board[5] = 0;
            } else if (m.to == 58) {
                board[56] = board[59];
                board[59] = 0;
            } else if (m.to == 62) {
                board[63] = board[61];
                board[61] = 0;
            }
        }
    }
}