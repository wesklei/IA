/* 
 * File:   main.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on September 29, 2015, 8:45 PM
 */

#include "global.hpp"
#include "Cell.h"
#include "Board.hpp"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;
#define BOARD_SIZE 42
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
        fprintf(pipe, "set xrange [-1:42]\n"); // set the terminal
        fprintf(pipe, "set yrange [-1:42]\n"); // set the terminal

        fprintf(pipe, "set style line 1 lc rgb 'green' pt 5 ps 2 \n"); // plot type square
        fprintf(pipe, "set style line 2 lc rgb 'brown' pt 5 ps 2 \n"); // plot type circle
        fprintf(pipe, "set style line 3 lc rgb 'blue' pt 5 ps 2 \n"); // plot type triangle
        fprintf(pipe, "set style line 4 lc rgb 'orange' pt 5 ps 2 \n"); // plot type *
        fprintf(pipe, "set style line 5 lc rgb 'red' pt 5 ps 2 \n"); // plot type *

        ofstream color1("color_1_ordered.dataset");
        ofstream color2("color_2_ordered.dataset");
        ofstream color3("color_3_ordered.dataset");
        ofstream color4("color_4_ordered.dataset");
        ofstream color5("color_5_ordered.dataset");
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {

                int color = board->matrixPrint[i][j];
                switch (color) {
                    case SOLIDO:
                        color1 << j << " " << i << endl;
                        break;
                    case MONTANHOSO:
                        color2 << j << " " << i << endl;
                        break;
                    case PANTANO:
                        color3 << j << " " << i << endl;
                        break;
                    case FOGO:
                        color4 << j << " " << i << endl;
                        break;
                    case -1:
                        color5 << j << " " << i << endl;
                        break;
                        //fprintf(pipe, "%d %d\n", j, i); // data terminated with \n
                }
            }
        }
        color1.close();
        color2.close();
        color3.close();
        color4.close();
        color5.close();

        fprintf(pipe, "plot 'color_1_ordered.dataset' with points ls 1 notitle, 'color_2_ordered.dataset' with points ls 2 notitle, 'color_3_ordered.dataset' with points ls 3 notitle, 'color_4_ordered.dataset' with points ls 4 notitle, 'color_5_ordered.dataset' with points ls 5 notitle,\n");

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

/*
 * 
 */
int main(int argc, char** argv) {
    Board board;

    cout << endl << "board.deepFirstSearch(0,0,40,40) " << endl;
    board.deepFirstSearch(0, 0, 15, 40);
    gnuplot_write("deepFirstSearch", &board, false);


    cout << endl << "board.breadthFirstSearch(0,0,40,40) " << endl;
    board.breadthFirstSearch(0, 0, 15, 40);
    gnuplot_write("breadthFirstSearch", &board, false);

    cout << endl << "board.uniformWeightSearch(0,0,40,40) " << endl;
    board.uniformWeightSearch(0, 0, 15, 40);
    gnuplot_write("uniformWeightSearch", &board, false);


    return 0;
}

