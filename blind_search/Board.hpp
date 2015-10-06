/* 
 * File:   Board.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on September 29, 2015, 9:13 PM
 */

#ifndef BOARD_HPP
#define	BOARD_HPP

#include "global.hpp"
#include "Cell.h"
#include "Node.hpp"

class Board {
public:

    static const int SIZE = 42;
    Cell **environment;
    int matrixPrint[SIZE][SIZE];

    Board();
    Board(const Board& orig);
    virtual ~Board();

    void breadthFirstSearch(int x, int y, int finalX, int finalY);
    void deepFirstSearch(int x, int y, int finalX, int finalY);
    void uniformWeightSearch(int x, int y, int finalX, int finalY);


private:

    void printSearchResult(Node *root, int nodesCount);
    void process_file_data();

};

#endif	/* BOARD_HPP */

