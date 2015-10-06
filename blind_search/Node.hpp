/* 
 * File:   Node.hpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 *
 * Created on October 5, 2015, 7:48 PM
 */

#ifndef NODE_HPP
#define	NODE_HPP

class Node {
    
public:
    
    int x,y,weight,level;
    Node *root;
    
    Node();
    Node(int x, int y, int weight);
    Node(int x, int y, int weight, Node *root);
    Node(int x, int y, int weight, int level, Node *root);
    Node(const Node& orig);
    virtual ~Node();
private:

};

#endif	/* NODE_HPP */

