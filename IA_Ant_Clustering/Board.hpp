/* 
 * File:   Board.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:41 PM
 */

#ifndef BOARD_HPP
#define	BOARD_HPP

#include "Cell.hpp"
#include "Ant.hpp"
#include "global.hpp"

class Board {
public:

    /*
     Main parameters
     */

    int drop = 0;
    int pick = 0;
    int SIZE;
    int ANTS_LIVE;
    int ANTS_DEAD;
    int VISION_RADIUS;
    float PROP_PICK;
    float PROP_DROP;

    int total_ants;
    int minBoardAcess;
    int maxBoardAcess;

    Cell **board;
    Ant *liveAntsInBoard;

    Board();
    Board(int size, int live_ants, int dead_ants, int radius, float prob_pick, float prob_drop);
    Board(const Board& orig);
    virtual ~Board();

    void printBoard();
    void printBoardWithTabLines();
    void iterateBoard();

private:

    void populateBoard();
    int random(int min, int max);
    int randomMove(int pos_now);
    int truncatePosition(int pos);
    int visionRadiusCount(Ant &ant);
    bool pickOrNot(Ant &ant);
    bool dropOrNot(Ant &ant);
    float RandomFloat(float a, float b);

};

#endif	/* BOARD_HPP */

