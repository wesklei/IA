/* 
 * File:   main.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:31 PM
 */

#include <cstdlib>

#include "Board.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Board *board = new Board(10, 10, 5, 1);

    for (int i = 0; i < 10; i++) {
        board->printBoard();
       
        board->iterateBoard();
    }
    return 0;
}

