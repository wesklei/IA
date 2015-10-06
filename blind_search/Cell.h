/* 
 * File:   Cell.h
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on September 29, 2015, 8:48 PM
 */

#ifndef CELL_H
#define	CELL_H

#include "global.hpp"
#include "Cell.h"


class Cell {
    
public:
    
    EnumBoard terrain;
    
    Cell();
    Cell(const Cell& orig);
    virtual ~Cell();
    
    int weightFromCell();
    
private:

};

#endif	/* CELL_H */

