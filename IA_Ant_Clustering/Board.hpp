/* 
 * File:   Board.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:41 PM
 */

#ifndef BOARD_HPP
#define	BOARD_HPP

#include "global.hpp"
#include "Cell.hpp"
#include "Ant.hpp"

class Board {   
public:
   
    Cell **board;
    Ant *liveAntsInBoard;
    int size;
    int live_ants;
    int dead_ants;
    int radius;
    int total_ants;
    int minBoardAcess;
    int maxBoardAcess;
    
    Board();
    Board(int size, int live_ants, int dead_ants, int radius);
    Board(const Board& orig);
    virtual ~Board();
    
    void printBoard();
    void iterateBoard();
    
private:
    
    void populateBoard();
    int random(int min, int max);
    int randomMove(int pos_now);
    int truncateMove(int pos);

};

#endif	/* BOARD_HPP */

