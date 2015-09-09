/* 
 * File:   Item.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on September 02, 2015, 11:02 PM
 */

#include "Item.hpp"

Item::Item() {
}

Item::Item(float x_cord, float y_cord, char color) {
    this->x_cord = x_cord;
    this->y_cord = y_cord;
    this->color = color;
}

Item::Item(const Item& orig) {
}

Item::~Item() {
    x_cord = -1;
    y_cord = -1;
    color = '0';
}

