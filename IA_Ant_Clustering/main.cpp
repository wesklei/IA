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

    srand(time(NULL));
    Board *board = new Board(20,50, 20, 3, 0.3, 0.2);
    board->printBoard();
    for (int i = 0; i < 100000000; i++) {
        board->iterateBoard();
        
        if (i % 100000 == 0) {
          //  gnuplot_write("imgs/iterate_" + to_string(i), board, false);
            board->printBoard();
      }
    }
    board->printBoard();
    cout << "picks " << board->pick << " drops " << board->drop << endl;
    return 0;
}

