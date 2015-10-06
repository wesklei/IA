/* 
 * File:   Board.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on September 29, 2015, 9:13 PM
 */

#include "Board.hpp"

Board::Board() {

    process_file_data();
}

Board::Board(const Board& orig) {
}

Board::~Board() {
}

void Board::process_file_data() {


    std::ifstream infile("Robo_ambiente.txt");

    int i, j;
    environment = new Cell*[SIZE];
    for (i = 0; i <= SIZE; i++) {
        environment[i] = new Cell[SIZE]();
    }

    int terrain;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            infile >> terrain;

            environment[i][j].terrain = static_cast<EnumBoard> (terrain);
            cout << environment[i][j].terrain << " ";
        }
        cout << endl;
    }
}

void Board::breadthFirstSearch(int x, int y, int finalX, int finalY) {

    vector<Node*> searchNodes;
    int weigth;
    Node *root = new Node(x, y, environment[x][y].weightFromCell(), NULL);
    searchNodes.push_back(root);
    int nodesCount = 1;
    int i = 0;

    int environmentVisited[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            environmentVisited[i][j] = 0;
        }
    }
    environmentVisited[x][y] = 1; // go to it!

    i = 0;

    while (true) {
        root = searchNodes[i];

        int xNode = root->x;
        int yNode = root->y;

        nodesCount++;
        if (xNode == finalX && yNode == finalY) {
            break;
        }
        if (yNode - 1 >= 0 && environmentVisited[xNode][yNode - 1] == 0) { // north
            weigth = root->weight + environment[xNode][yNode - 1].weightFromCell();
            searchNodes.push_back(new Node(xNode, yNode - 1, weigth, root));
            environmentVisited[xNode][yNode - 1] = 1;
        }
        if (xNode + 1 < SIZE && environmentVisited[xNode + 1][yNode] == 0) { // east
            weigth = root->weight + environment[xNode + 1][yNode].weightFromCell();
            searchNodes.push_back(new Node(xNode + 1, yNode, weigth, root));
            environmentVisited[xNode + 1][yNode] = 1;
        }
        if (yNode + 1 < SIZE && environmentVisited[xNode][yNode + 1] == 0) { // south
            weigth = root->weight + environment[xNode][yNode + 1].weightFromCell();
            searchNodes.push_back(new Node(xNode, yNode + 1, weigth, root));
            environmentVisited[xNode][yNode + 1] = 1;
        }
        if (xNode - 1 >= 0 && environmentVisited[xNode - 1][yNode] == 0) { // west
            weigth = root->weight + environment[xNode - 1][yNode].weightFromCell();
            searchNodes.push_back(new Node(xNode - 1, yNode, weigth, root));
            environmentVisited[xNode - 1][yNode] = 1;
        }
        i++;
    }

    printSearchResult(root, nodesCount);

}

void Board::deepFirstSearch(int x, int y, int finalX, int finalY) {

    vector<Node*> searchNodes;
    int weigth;
    Node *root = new Node(x, y, environment[x][y].weightFromCell(), NULL);
    int xNode = root->x;
    int yNode = root->y;
    searchNodes.push_back(root);
    int nodesCount = 1;
    int i = 0;

    int environmentVisited[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            environmentVisited[i][j] = 0;
        }
    }
    environmentVisited[x][y] = 1; // go to it!

    i = 0;
    while (true) {
        root = searchNodes[i];

        xNode = root->x;
        yNode = root->y;

        nodesCount++;

        environmentVisited[xNode][yNode] = 1;

        if (xNode == finalX && yNode == finalY) {
            break;
        }
        if (xNode - 1 >= 0 && environmentVisited[xNode - 1][yNode] == 0) { // weast
            weigth = root->weight + environment[xNode - 1][yNode].weightFromCell();
            searchNodes.insert(searchNodes.begin()+(i + 1), new Node(xNode - 1, yNode, weigth, root));
        }
        if (yNode + 1 < SIZE && environmentVisited[xNode][yNode + 1] == 0) { // south
            weigth = root->weight + environment[xNode][yNode + 1].weightFromCell();
            searchNodes.insert(searchNodes.begin()+(i + 1), new Node(xNode, yNode + 1, weigth, root));
        }
        if (xNode + 1 < SIZE && environmentVisited[xNode + 1][yNode] == 0) { // east
            weigth = root->weight + environment[xNode + 1][yNode].weightFromCell();
            searchNodes.insert(searchNodes.begin()+(i + 1), new Node(xNode + 1, yNode, weigth, root));
        }
        if (yNode - 1 >= 0 && environmentVisited[xNode][yNode - 1] == 0) { // north
            weigth = root->weight + environment[xNode][yNode - 1].weightFromCell();
            searchNodes.insert(searchNodes.begin()+(i + 1), new Node(xNode, yNode - 1, weigth, root));
        }

        i++;
    }

    printSearchResult(root, nodesCount);
}

void Board::uniformWeightSearch(int x, int y, int finalX, int finalY) {
    vector<Node*> searchNodes;
    int weigth;
    Node *root = new Node(x, y, environment[x][y].weightFromCell(), NULL);
    int xNode = root->x;
    int yNode = root->y;
    searchNodes.push_back(root);
    int nodesCount = 1;
    int i = 0, j;

    int environmentVisited[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            environmentVisited[i][j] = 0;
        }
    }
    environmentVisited[x][y] = 1; // go to it!

    i = 0;
    while (true) {
        root = searchNodes[i];
        int xNode = root->x;
        int yNode = root->y;
        
        nodesCount++;
        environmentVisited[xNode][yNode] = 1;
        if (xNode == finalX && yNode == finalY) {
            break;
        }
        if (yNode - 1 >= 0 && environmentVisited[xNode][yNode - 1] == 0) { // north
            weigth = root->weight + environment[xNode][yNode - 1].weightFromCell();
            for (j = searchNodes.size() - 1; true; j--) {
                if (searchNodes[j]->level == root->level) {
                    searchNodes.insert(searchNodes.begin() + j + 1, new Node(xNode, yNode - 1, weigth, root->level + 1, root));
                    break;
                }
                if (searchNodes[j]->weight > weigth) {
                    searchNodes.insert(searchNodes.begin() + j, new Node(xNode, yNode - 1, weigth, root->level + 1, root));
                    break;
                }
            }
            environmentVisited[xNode][yNode - 1] = 1;
        }
        if (xNode + 1 < SIZE && environmentVisited[xNode + 1][yNode] == 0) { // weast
            weigth = root->weight + environment[xNode + 1][yNode].weightFromCell();
            for (j = searchNodes.size() - 1; true; j--) {
                if (searchNodes[j]->level == root->level) {
                    searchNodes.insert(searchNodes.begin() + j + 1, new Node(xNode + 1, yNode, weigth, root->level + 1, root));
                    break;
                }
                if (searchNodes[j]->weight > weigth) {
                    searchNodes.insert(searchNodes.begin() + j, new Node(xNode + 1, yNode, weigth, root->level + 1, root));
                    break;
                }
            }
            environmentVisited[xNode + 1][yNode] = 1;
        }
        if (yNode + 1 < SIZE && environmentVisited[xNode][yNode + 1] == 0) { // south
            weigth = root->weight + environment[xNode][yNode + 1].weightFromCell();
            for (j = searchNodes.size() - 1; true; j--) {
                if (searchNodes[j]->level == root->level) {
                    searchNodes.insert(searchNodes.begin() + j + 1, new Node(xNode, yNode + 1, weigth, root->level + 1, root));
                    break;
                }
                if (searchNodes[j]->weight > weigth) {
                    searchNodes.insert(searchNodes.begin() + j, new Node(xNode, yNode + 1, weigth, root->level + 1, root));
                    break;
                }
            }
            environmentVisited[xNode][yNode + 1] = 1;
        }
        if (xNode - 1 >= 0 && environmentVisited[xNode - 1][yNode] == 0) { // east
            weigth = root->weight + environment[xNode - 1][yNode].weightFromCell();
            for (j = searchNodes.size() - 1; true; j--) {
                if (searchNodes[j]->level == root->level) {
                    searchNodes.insert(searchNodes.begin() + j + 1, new Node(xNode - 1, yNode, weigth, root->level + 1, root));
                    break;
                }
                if (searchNodes[j]->weight > weigth) {
                    searchNodes.insert(searchNodes.begin() + j, new Node(xNode - 1, yNode, weigth, root->level + 1, root));
                    break;
                }
            }
            environmentVisited[xNode - 1][yNode] = 1;
        }
        i++;
    }
    
    printSearchResult(root, nodesCount);
}

void Board::printSearchResult(Node *root, int nodesCount) {
    Node *aux = root;
    int i;
    cout << "Final cost => " << aux->weight << endl;
    cout << "Visited=> " << nodesCount << endl;

    for (i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrixPrint[i][j] = environment[i][j].terrain;
        }
    }

    while (aux != NULL) {
        matrixPrint[aux->x][aux->y] = -1;
        aux = aux->root;
    }

    cout << "Final path => " << endl;
    for (i = 0; i < SIZE; i++) {
        cout << endl;
        for (int j = 0; j < SIZE; j++) {

            if (matrixPrint[i][j] == -1) {
                cout << "*" << " ";
            } else {
                cout << matrixPrint[i][j] << " ";
            }
        }
    }
}

