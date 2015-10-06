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
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <functional>
#include <cmath>
#include <string.h>
#include <time.h>
#include <errno.h>
 #include <fstream>

using namespace std;

enum EnumBoard {
    SOLIDO = 0, MONTANHOSO = 1, PANTANO = 2, FOGO = 3
};

enum EnumBoardWeight {
    WEIGHT_SOLIDO = 1, WEIGHT_MONTANHOSO = 5, WEIGHT_PANTANO = 10, WEIGHT_FOGO = 15
};



#endif	/* GLOBAL_HPP */

