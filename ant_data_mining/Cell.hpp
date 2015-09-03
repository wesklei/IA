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
#include "Item.hpp"

class Cell {
  
  
public:
    EnumBoard state;
    Item item;
    
    Cell();
    Cell(EnumBoard state, Item item);
    Cell(const Cell& orig);
    virtual ~Cell();

    char valueOfCell();
    char valueOfItemCell();
    int getCellState();
    bool hasDeadAntInCell();
    
private:

};


#endif	/* ANT_HPP */

