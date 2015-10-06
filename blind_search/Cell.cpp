/* 
 * File:   Cell.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on September 29, 2015, 8:48 PM
 */

#include "Cell.h"

Cell::Cell() {
}

Cell::Cell(const Cell& orig) {
}

Cell::~Cell() {
}

int Cell::weightFromCell() {
    switch (terrain) {
        case SOLIDO:
            return WEIGHT_SOLIDO;
        case MONTANHOSO:
            return WEIGHT_MONTANHOSO;
        case PANTANO:
            return WEIGHT_PANTANO;
        case FOGO:
            return WEIGHT_FOGO;
        default:
            return -10000;
    }
}

