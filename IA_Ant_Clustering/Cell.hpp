/* 
 * File:   Ant.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 10:23 PM
 */

#ifndef CELL_HPP
#define	CELL_HPP


#include "Ant.hpp"
#include "global.hpp"


class Cell {
public:
    EnumBoard state;
    
    Cell();
    Cell(EnumBoard state);
    Cell(const Cell& orig);
    virtual ~Cell();

    char valueOfCell();


private:

};


#endif	/* ANT_HPP */

