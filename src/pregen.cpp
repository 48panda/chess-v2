#include "main.hpp"
#include <algorithm>
#include <random>

void Game::genPregenData() {
    std::random_device rd;

    std::mt19937_64 e2(rd());

    std::uniform_int_distribution<long long int> dist(std::llround(0), std::llround(std::pow(2,63)));
    for(s8 x = 0; x < 8; x++) {
        for (s8 y = 0; y < 8; y++) {
            int index = x * 8 + y;
            s8 seven = 7;
            pregen[0][index] = seven - y;
            pregen[1][index] = y;
            pregen[2][index] = seven - x;
            pregen[3][index] = x;
            pregen[4][index] = std::min((s8)(seven - x), (s8)(seven - y));
            pregen[5][index] = std::min(x, y);
            pregen[6][index] = std::min((s8)(seven - x), y);
            pregen[7][index] = std::min(x, (s8)(seven - y));
            if ( y < 6 && x < 7) {
                pregen[8][index] = 1;
            } else {
                pregen[8][index] = 0;
            }
            if ( y > 1 && x > 0) {
                pregen[9][index] = 1;
            } else {
                pregen[9][index] = 0;
            }
            if ( y > 1 && x < 7) {
                pregen[10][index] = 1;
            } else {
                pregen[10][index] = 0;
            }
            if ( y < 6 && x > 0) {
                pregen[11][index] = 1;
            } else {
                pregen[11][index] = 0;
            }
            if (y < 7 && x < 6) {
                pregen[12][index] = 1;
            } else {
                pregen[12][index] = 0;
            }
            if (y > 0 && x > 1) {
                pregen[13][index] = 1;
            } else {
                pregen[13][index] = 0;
            }
            if (y > 0 && x < 6) {
                pregen[14][index] = 1;
            } else {
                pregen[14][index] = 0;
            }
            if (y < 7 && x > 1) {
                pregen[15][index] = 1;
            } else {
                pregen[15][index] = 0;
            }
            tileNames[index][0] = 'a' + y;
            tileNames[index][1] = '8' - x;
            tileNames[index][2] = '\0';
            for (s8 i = 0; i < 16; i++) {
                u64 toStore = dist(e2);
                hashTable[index][i] = toStore;
            }
        }
    }
}