/* 
 * File:   Ant.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on August 23, 2015, 11:02 PM
 */

#include "Ant.hpp"

Ant::Ant() {
}

Ant::Ant(int x_poss, int y_poss) {
    this->x_pos = x_poss;
    this->y_pos = y_poss;
}

Ant::Ant(const Ant& orig) {
}

Ant::~Ant() {
}

