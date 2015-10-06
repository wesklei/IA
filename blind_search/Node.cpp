/* 
 * File:   Node.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on October 5, 2015, 7:48 PM
 */

#include "Node.hpp"

Node::Node() {
}

Node::Node(int x, int y, int weight) {
    this->x = x;
    this->y = y;
    this->weight = weight;
}

Node::Node(int x, int y, int weight, Node* root) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->root = root;
}

Node::Node(int x, int y, int weight, int level, Node* root) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->level = level;
    this->root = root;
}

Node::Node(const Node& orig) {
}

Node::~Node() {
}

