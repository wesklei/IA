/* 
 * File:   Ant.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on August 23, 2015, 10:23 PM
 */

#include "global.hpp"
#include "Cell.hpp"
#include "Board.hpp"

Cell::Cell() {
    this->state = FREE;
}

Cell::Cell(EnumBoard state) {
    this->state = state;
}

Cell::Cell(const Cell& orig) {
}

Cell::~Cell() {
}

char Cell::valueOfCell() {
    return this->state;
}

/**
 * where cell has a dead ant, return without live ants, only dead items
 * @return 
 */
char Cell::valueOfItemCell() {

    switch (this->state) {
        case ANT_NONCARRING:
            return FREE;//don't show
            break;
        case ANT_CARRYING:
        case ANT_DEAD_AND_NONCARRYING:
        case ANT_DEAD:
            return ANT_DEAD;
            break;
        default:
            return this->state;
    }
}


/**
 * where cell has a dead ant, return without live ants, only dead items
 * @return 
 */
bool Cell::hasDeadAntInCell() {

    bool retorno = false;
    switch (this->state) {
        case ANT_CARRYING:
        case ANT_DEAD_AND_NONCARRYING:
        case ANT_DEAD:
            retorno = true;
            break;            
    }
    
    return retorno;
}

int Cell::getCellState() {
    return this->state;
}