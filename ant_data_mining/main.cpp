/* 
 * File:   main.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:31 PM
 */

#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;
#define BOARD_SIZE 60
#define GNUPLOT_NAME "gnuplot"
#define GIFF_NAME "convert"
#define SHOW_IN_WINDOW false

void gnuplot_write(string name, Board *board, bool showInWindow) {

    FILE *pipe = popen(GNUPLOT_NAME, "w");

    if (pipe != NULL) {

        if (showInWindow) {
            fprintf(pipe, "set term wx\n"); // set the terminal
        } else {
            fprintf(pipe, "set term png\n"); // set the terminal
            //  char output[80] = "set output '";
            //  strcat(output, name);
            // strcat(output, ".png'\n");
            string output("set output '" + name + ".png'\n");
            fprintf(pipe, output.c_str()); // set the terminal
        }
        fprintf(pipe, "set xrange [0:60]\n"); // set the terminal
        fprintf(pipe, "set yrange [0:60]\n"); // set the terminal

        fprintf(pipe, "set style line 1 lc rgb 'black' pt 5 \n"); // plot type square
        fprintf(pipe, "set style line 2 lc rgb 'red' pt 7\n"); // plot type circle
        fprintf(pipe, "set style line 3 lc rgb 'blue' pt 9\n"); // plot type triangle
        fprintf(pipe, "set style line 4 lc rgb 'yellow' pt 3\n"); // plot type *

        ofstream color1("ants_color_1_ordered.dataset");
        ofstream color2("ants_color_2_ordered.dataset");
        ofstream color3("ants_color_3_ordered.dataset");
        ofstream color4("ants_color_4_ordered.dataset");
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {

                if (board->board[i][j].hasDeadAntInCell()) {

                    int color = board->board[i][j].item.color - '0';
                    switch (color) {
                        case 1:
                            color1 << j << " " << i << endl;
                            break;
                        case 2:
                            color2 << j << " " << i << endl;
                            break;
                        case 3:
                            color3 << j << " " << i << endl;
                            break;
                        case 4:
                            color4 << j << " " << i << endl;
                            break;
                            //fprintf(pipe, "%d %d\n", j, i); // data terminated with \n
                    }
                }
            }
        }
        color1.close();
        color2.close();
        color3.close();
        color4.close();

        fprintf(pipe, "plot 'ants_color_1_ordered.dataset' with points ls 1 notitle, 'ants_color_2_ordered.dataset' with points ls 2 notitle, 'ants_color_3_ordered.dataset' with points ls 3 notitle, 'ants_color_4_ordered.dataset' with points ls 4 notitle\n");

       // fprintf(pipe, "%s\n", "e"); // termination character
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
    Board *board = new Board(BOARD_SIZE, 150, 400, 2, 0.3, 0.2);
   // board->printBoard();
    //gnuplot_write("start", board, SHOW_IN_WINDOW);

    int times, timed;

    gnuplot_write("imgs/iterate_0", board, false);
    times = clock();
    for (int i = 0; i < 500000; i++) {
        board->iterateBoard();
        if (i % 1000 == 0) {
            gnuplot_write("imgs/iterate_" + to_string(i), board, false);
            //      board->printBoard();
        }
    }
    timed = clock();
    gnuplot_write("imgs/iterate_500000", board, false);
    generate_giff();

   // board->printBoard();
    cout << "picks " << board->pick << " drops " << board->drop << endl;

    double diffticks = timed - times;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);

    cout << "Time run is " << diffms << " ms " << endl;

    //gnuplot_write("end_run", board, SHOW_IN_WINDOW);
    return 0;
}


