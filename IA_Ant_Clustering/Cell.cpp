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


char Cell::valueOfCell(){
    return this->state;
}