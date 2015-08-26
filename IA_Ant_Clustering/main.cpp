/* 
 * File:   main.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:31 PM
 */

#include <cstdlib>

#include "global.hpp"
#include "Board.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /* initialize random seed: */
    srand(time(NULL));
    
    Board *board = new Board(40, 520, 200, 5, 0.3, 0.2);
    board->printBoard();
    for (int i = 0; i < 100000; i++) {
        board->iterateBoard();
    }
    board->printBoard();
    
    cout << "drops was " << board->drop << " and pick " << board->pick << endl;
    return 0;
}

