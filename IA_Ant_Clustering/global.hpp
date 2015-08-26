/* 
 * File:   global.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 9:56 PM
 */

#ifndef GLOBAL_HPP
#define	GLOBAL_HPP

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <vector>


using namespace std;

enum EnumBoard {
    FREE = ' ', ANT_DEAD = '*', ANT_CARRING='%', ANT_NONCARRING='¬', BARRIER='#'
};

#endif	/* GLOBAL_HPP */

