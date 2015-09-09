/* 
 * File:   Item.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on September 02, 2015, 11:02 PM
 */

#ifndef ITEM_HPP
#define	ITEM_HPP


class Item {
    
public:
    float x_cord;
    float y_cord;
    char color;
    
    
    Item();
    Item(float x_cord, float y_cord, char color);
    Item(const Item& orig);
    virtual ~Item();
private:

};

#endif	/* ITEM_HPP */

