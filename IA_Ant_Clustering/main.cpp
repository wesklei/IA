/* 
 * File:   main.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:31 PM
 */

#include <cstdlib>

#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Board.hpp"
#include <string.h>
#include <time.h>


using namespace std;
#define BOARD_SIZE 32
#define GNUPLOT_NAME "gnuplot"
#define GIFF_NAME "convert"
#define SHOW_IN_WINDOW false

void gnuplot_write(string name, Board *board, bool showInWindow) {

    FILE *pipe = popen(GNUPLOT_NAME, "w");

    if (pipe != NULL) {

        if (showInWindow) {
            fprintf(pipe, "set term wx size 500,500\n"); // set the terminal
        } else {
            fprintf(pipe, "set term png size 500,500\n"); // set the terminal
            //  char output[80] = "set output '";
            //  strcat(output, name);
            // strcat(output, ".png'\n");
            string output("set output '" + name + ".png'\n");
            fprintf(pipe, output.c_str()); // set the terminal
        }
        fprintf(pipe, "set xrange [0:32]\n"); // set the terminal
        fprintf(pipe, "set yrange [0:32]\n"); // set the terminal

        fprintf(pipe, "plot '-' with points pointtype 3 pointsize 1 lc rgb 'black' notitle\n"); // plot type
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board->board[i][j].hasDeadAntInCell()) {
                    fprintf(pipe, "%d %d\n", j, i); // data terminated with \n
                }
            }
        }
        fprintf(pipe, "%s\n", "e"); // termination character
        fflush(pipe); // flush the pipe

        if (showInWindow) {
            // wait for key press
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }

        pclose(pipe);

    } else
        std::cout << "Could not open pipe" << std::endl;
}

void generate_giff() {

        system("convert -delay 10 -loop 0 `ls -v imgs/*.png` animation_ants.gif\n");
}

/*
 * 
 */
int main(int argc, char** argv) {

    srand(time(NULL));
    Board *board = new Board(BOARD_SIZE, 250, 350, 1, 0.3, 0.2);
    board->printBoard();
    //gnuplot_write("start", board, SHOW_IN_WINDOW);

    int times, timed;

    gnuplot_write("imgs/iterate_0", board, false);
    times = clock();
    for (int i = 0; i < 500000; i++) {
        board->iterateBoard();
        //if (i % 1000 == 0) {
          //  gnuplot_write("imgs/iterate_" + to_string(i), board, false);
           // board->printBoard();
        //}
    }
    timed = clock();
    //gnuplot_write("imgs/iterate_500000", board, false);
    generate_giff();

    board->printBoard();
    cout << "picks " << board->pick << " drops " << board->drop << endl;

    double diffticks = timed - times;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);

    cout << "Time run is " << diffms << " ms " << endl;

    //gnuplot_write("end_run", board, SHOW_IN_WINDOW);
    return 0;
}


