/* 
 * File:   Board.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on August 23, 2015, 9:41 PM
 */

#include "Board.hpp"
#include <errno.h>
#include <string.h>

Board::Board(const Board& orig) {
}

Board::~Board() {
}

Board::Board(int size, int live_ants, int dead_ants, int radius, float prob_pick, float prob_drop) {

    this->SIZE = size;
    this->ANTS_LIVE = live_ants;
    this->ANTS_DEAD = dead_ants;
    this->VISION_RADIUS = radius;
    this->PROP_PICK = prob_pick;
    this->PROP_DROP = prob_drop;
    this->total_ants = this->ANTS_LIVE + this->ANTS_DEAD;
    this->minBoardAcess = 0;
    this->maxBoardAcess = this->SIZE - 1;

    this->liveAntsInBoard = new Ant[this->ANTS_LIVE];

    this->board = new Cell*[this->SIZE];
    for (int i = 0; i <= this->SIZE; i++) {
        this->board[i] = new Cell[this->SIZE]();
    }

    //start with barriers
    for (int i = 0; i <= this->SIZE; i++) {
        this->board[i][0].state = BARRIER;
        this->board[i][this->SIZE].state = BARRIER;

        this->board[0][i].state = BARRIER;
        this->board[this->SIZE][i].state = BARRIER;
    }

    populateBoard();
}

void Board::process_file_data(Board *board) {
    std::ifstream infile("Square1_DataSet_400itens.txt");

    float x, y;
    int color;

    while (infile >> x >> y >> color) {
        Item item(x, y, color);

    }
}

void Board::populateBoard() {

    int dead_ants = 0;
    int live_ants = 0;
    int x_pos, y_pos;
    float x_data, y_data;
    char color_data;
    int limit = 0;
    Item* items = new Item[this->ANTS_DEAD];
    std::ifstream infile("Square1_DataSet_400itens.txt");

    if (infile) // Verify that the file was open successfully
    {

        while (infile >> x_data >> y_data >> color_data && limit < this->ANTS_DEAD) {
            limit++;
            items[dead_ants] = Item(x_data, y_data, color_data);
            dead_ants++;
        }

        double dist;
        double max_dist = -1;
        this->NORM_DIST = 1;
        for (int i = 0; i < ANTS_DEAD; i++) {
            for (int j = i + 1; j < ANTS_DEAD; j++) {
                dist = euclidianDistance(items[i].x_cord, items[i].y_cord, items[j].x_cord, items[j].y_cord);

                if (dist > max_dist) {
                    max_dist = dist;
                }
            }
        }
        this->NORM_DIST = max_dist;

        dead_ants = 0;
        while (dead_ants < this->ANTS_DEAD) {

            do {
                x_pos = random(minBoardAcess, maxBoardAcess);
                y_pos = random(minBoardAcess, maxBoardAcess);
            } while (!(this->board[x_pos][y_pos].state == FREE));

            this->board[x_pos][y_pos].state = ANT_DEAD;
            this->board[x_pos][y_pos].item = items[dead_ants];

            dead_ants++;
        }

        while (live_ants < this->ANTS_LIVE) {

            do {
                x_pos = random(minBoardAcess, maxBoardAcess);
                y_pos = random(minBoardAcess, maxBoardAcess);
            } while (!(this->board[x_pos][y_pos].state == FREE));

            this->board[x_pos][y_pos].state = ANT_NONCARRING;

            this->liveAntsInBoard[live_ants] = Ant(x_pos, y_pos);
            live_ants++;
        }
    } else {
        cerr << "File could not be opened!\n"; // Report error
        cerr << "Error code: " << strerror(errno); // Get some info as to why
    }
}

void Board::printBoardWithTabLines() {
    std::cout << "\t";
    for (int j = 0; j <= SIZE; j++) {
        std::cout << j << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i <= SIZE; i++) {
        std::cout << i << "\t";
        for (int j = 0; j <= SIZE; j++) {
            std::cout << this->board[i][j].valueOfItemCell() << "\t";
        }
        std::cout << "\t" << std::endl;

    }
}

void Board::printBoard() {
    for (int i = 0; i <= SIZE; i++) {
        for (int j = 0; j <= SIZE; j++) {
            std::cout << this->board[i][j].valueOfCell();
        }
        std::cout << std::endl;
    }
}

void Board::iterateBoard() {

    int x_pos, y_pos;

    // now start at from the beginning
    // and keep iterating over the element till you find
    // nth element...or reach the end of vector.
    for (int i = 0; i < this->ANTS_LIVE; i++) {

        EnumBoard stateAnt = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state;
        bool isHoldItem = stateAnt == ANT_CARRYING ? true : false;

        Item holdItem;
        if (stateAnt == ANT_CARRYING) {

            if (dropOrNot(liveAntsInBoard[i])) {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = ANT_DEAD;
                stateAnt = ANT_NONCARRING; //now is not carrying
                isHoldItem = false;
            } else {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;

                holdItem = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].item;
                isHoldItem = true;
            }


        } else {

            bool isPick = pickOrNot(liveAntsInBoard[i]);
            if (stateAnt == ANT_DEAD_AND_NONCARRYING && isPick) {

                isHoldItem = true;
                holdItem = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].item;

                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;
                stateAnt = ANT_CARRYING; //now is carrying
            } else if (stateAnt == ANT_DEAD_AND_NONCARRYING && !isPick) {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = ANT_DEAD;
                isHoldItem = false;
            } else {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;
                isHoldItem = false;
            }
        }

        //walk ant

        //find new position to go
        EnumBoard stateInNewCell;

        if (stateAnt == ANT_CARRYING) {// || stateAnt == ANT_DEAD_AND_NONCARRYING) {
            do {
                x_pos = randomMove(liveAntsInBoard[i].x_pos);
                y_pos = randomMove(liveAntsInBoard[i].y_pos);

                stateInNewCell = this->board[x_pos][y_pos].state;
            } while (stateInNewCell != FREE);
        } else {

            do {
                x_pos = randomMove(liveAntsInBoard[i].x_pos);
                y_pos = randomMove(liveAntsInBoard[i].y_pos);

                stateInNewCell = this->board[x_pos][y_pos].state;
            } while (stateInNewCell != FREE
                    && stateInNewCell != ANT_DEAD);
        }

        //walk to new   
        liveAntsInBoard[i].x_pos = x_pos;
        liveAntsInBoard[i].y_pos = y_pos;

        //update new
        if (isHoldItem) {
            this->board[x_pos][y_pos].state = ANT_CARRYING;
            this->board[x_pos][y_pos].item = holdItem;
        } else {

            if (stateInNewCell == ANT_DEAD) {
                this->board[x_pos][y_pos].state = ANT_DEAD_AND_NONCARRYING;
            } else {
                this->board[x_pos][y_pos].state = ANT_NONCARRING;
            }
        }
    }
}

int Board::random(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

//walk one cell

int Board::randomMove(int pos_now) {
    int min = pos_now - 1;
    int max = pos_now + 1;
    return truncatePosition(min + (rand() % (int) (max - min + 1)));
}

int Board::truncatePosition(int pos) {

    // toroide.
    if (pos < this->minBoardAcess) {
        pos = this->maxBoardAcess;
    }

    if (pos > this->maxBoardAcess) {
        pos = this->minBoardAcess;
    }

    return pos;
}

int Board::truncateVision(int pos) {
    // toroide.
    if (pos < this->minBoardAcess) {
        pos = this->maxBoardAcess + pos;
    }

    if (pos >= this->maxBoardAcess) {
        pos = pos % this->maxBoardAcess;
    }

    return pos;
}

/**
 * Count the actual dead ants nearby
 * @param ant
 * @return 
 */
float Board::visionRadiusCountItem(Ant & ant) {

    int count_dead_ants = 0;
    int x_pos_start = ant.x_pos - this->VISION_RADIUS;
    int x_pos_end = ant.x_pos + this->VISION_RADIUS;

    int y_pos_start = ant.y_pos - this->VISION_RADIUS;
    int y_pos_end = ant.y_pos + this->VISION_RADIUS;

    float sum_func = 0;
    float dist, norm;

    int i_truncate, j_truncate;
    for (int i = x_pos_start; i <= x_pos_end; i++) {
        for (int j = y_pos_start; j <= y_pos_end; j++) {

            i_truncate = truncateVision(i);
            j_truncate = truncateVision(j);
            if (this->board[i_truncate][j_truncate].state == ANT_DEAD && i_truncate != ant.x_pos && j_truncate != ant.y_pos) {
                count_dead_ants++;
                dist = euclidianDistance(this->board[ant.x_pos][ant.y_pos].item.x_cord, this->board[ant.x_pos][ant.y_pos].item.y_cord, this->board[i_truncate][j_truncate].item.x_cord, this->board[i_truncate][j_truncate].item.y_cord);

                norm = (1.0 - (dist / 0.3));
                sum_func += norm;
            }
        }
    }

    if (count_dead_ants == 0) {
        return 0;
    }
    sum_func = sum_func / count_dead_ants; //((float) 8 * 8);

    if (sum_func > 0) {
        return sum_func;
    } else {
        return 0;
    }
}

/*
 * calculating distance by euclidean formula
 */
float Board::euclidianDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / this->NORM_DIST; //360.624458405;
}

/* 
 *  Stochastic behaviors to pick or not a dead ant
 */
bool Board::pickOrNot(Ant & ant) {

    float deadAntsInVision = visionRadiusCountItem(ant);
    float propPickOrNot = (PROP_PICK / (PROP_PICK + deadAntsInVision));
    propPickOrNot = pow(propPickOrNot, 2); //^2

    if (propPickOrNot > PROP_PICK) {
        EnumBoard state = this->board[ant.x_pos][ant.y_pos].state;
        if (state == ANT_DEAD_AND_NONCARRYING) {
            pick++;
        }

        return true;
    }

    return false;
}

/* 
 *  Stochastic behaviors to drop or not a dead ant
 */
bool Board::dropOrNot(Ant & ant) {
    float deadAntsInVision = visionRadiusCountItem(ant);

    float propDropOrNot = (deadAntsInVision / (PROP_DROP + deadAntsInVision));
    propDropOrNot = pow(propDropOrNot, 2); //*100; //^2

    if (propDropOrNot > PROP_DROP) {

        EnumBoard state = this->board[ant.x_pos][ant.y_pos].state;
        if (state == ANT_CARRYING) {
            drop++;
        }

        return true;
    }

    return false;
}

float Board::RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}






