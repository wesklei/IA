/* 
 * File:   Ant.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on August 23, 2015, 11:02 PM
 */

#ifndef ANT_HPP
#define	ANT_HPP


class Ant {
    
public:
    int x_pos;
    int y_pos;
    
    
    Ant();
    Ant(int x_poss, int y_poss);
    Ant(const Ant& orig);
    virtual ~Ant();
private:

};

#endif	/* ANT_HPP */

