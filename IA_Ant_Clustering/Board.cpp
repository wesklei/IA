/* 
 * File:   Board.cpp
 * Author: Wesklei Migliorini <wesklei.m at gmail dt com>
 * 
 * Created on August 23, 2015, 9:41 PM
 */

#include "Board.hpp"

Board::Board(const Board& orig) {
}

Board::~Board() {
}

Board::Board(int size, int live_ants, int dead_ants, int radius, float prob_pick, float prob_drop) {

    this->SIZE = size + 1;
    this->ANTS_LIVE = live_ants;
    this->ANTS_DEAD = dead_ants;
    this->VISION_RADIUS = radius;
    this->PROP_PICK = prob_pick;
    this->PROP_DROP = prob_drop;
    this->total_ants = this->ANTS_LIVE + this->ANTS_DEAD;
    this->minBoardAcess = 1;
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

void Board::populateBoard() {

    int dead_ants = 0;
    int live_ants = 0;
    int x_pos, y_pos;
    while (dead_ants < this->ANTS_DEAD) {

        do {
            x_pos = random(minBoardAcess, maxBoardAcess);
            y_pos = random(minBoardAcess, maxBoardAcess);
        } while (!(this->board[x_pos][y_pos].state == FREE));

        this->board[x_pos][y_pos].state = ANT_DEAD;

        // this->board[x_pos][y_pos].state = ANT_CARRYING;
        // this->liveAntsInBoard[live_ants] = Ant(x_pos, y_pos);

        // live_ants++;
        dead_ants++;
    }

    while (live_ants < this->ANTS_LIVE) {

        do {
            x_pos = random(minBoardAcess, maxBoardAcess);
            y_pos = random(minBoardAcess, maxBoardAcess);
        } while (!(this->board[x_pos][y_pos].state == FREE));

        this->board[x_pos][y_pos].state = ANT_NONCARRING;

        this->liveAntsInBoard[live_ants] = Ant(x_pos, y_pos);
        std::cout << "[" << this->liveAntsInBoard[live_ants].x_pos << "," << this->liveAntsInBoard[live_ants].y_pos << "]" << std::endl;
        live_ants++;
    }

    //TODO bugfix
    // this->board[this->SIZE][this->SIZE].state = BARRIER;


    //  for (int i = 0; i != this->ANTS_LIVE; i++) {
    //      std::cout << "[" << this->liveAntsInBoard[i].x_pos << "," << this->liveAntsInBoard[i].y_pos << "] => " << this->board[this->liveAntsInBoard[i].x_pos][this->liveAntsInBoard[i].y_pos].valueOfCell() << std::endl;
    //  }
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
            std::cout << this->board[i][j].valueOfItemCell();
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

        // cout << "in for " << i << endl;
        // printBoard();

        EnumBoard stateAnt = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state;
        bool holdItem = stateAnt == ANT_CARRYING ? true : false;


        if (stateAnt == ANT_CARRYING) {

            if (dropOrNot(liveAntsInBoard[i])) {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = ANT_DEAD;
                stateAnt = ANT_NONCARRING; //now is not carrying
                holdItem = false;
            } else {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;
                holdItem = true;
            }

        } else {

            bool isPick = pickOrNot(liveAntsInBoard[i]);
            if (stateAnt == ANT_DEAD_AND_NONCARRYING && isPick) {
                holdItem = true;
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;
                stateAnt = ANT_CARRYING; //now is carrying
            } else if (stateAnt == ANT_DEAD_AND_NONCARRYING && !isPick) {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = ANT_DEAD;
                holdItem = false;
            } else {
                this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE;
                holdItem = false;
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
        if (holdItem) {
            this->board[x_pos][y_pos].state = ANT_CARRYING;
        } else {

            if (stateInNewCell == ANT_DEAD) {
                this->board[x_pos][y_pos].state = ANT_DEAD_AND_NONCARRYING;
            } else {
                this->board[x_pos][y_pos].state = ANT_NONCARRING;
            }
        }



        /*
                EnumBoard oldState = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state;
                int old_x_pos = liveAntsInBoard[i].x_pos;
                int old_y_pos = liveAntsInBoard[i].y_pos;
                switch (stateInNewCell) {
                    case FREE: //new state is free
                        if (oldState == ANT_CARRYING) {
                            if (dropOrNot(liveAntsInBoard[i])) {
                                drop++;
                                //new
                                this->board[x_pos][y_pos].state = ANT_DEAD_AND_NONCARRYING; //drop and stay above

                                //old
                                this->board[old_x_pos][old_y_pos].state = FREE; //free the old state

                            } else {
                                this->board[x_pos][y_pos].state = ANT_CARRYING; //stay carrying

                                //old
                                this->board[old_x_pos][old_y_pos].state = FREE; //free the old state
                            }
                        } else if (oldState == ANT_NONCARRING) {
                            this->board[x_pos][y_pos].state = ANT_NONCARRING; //stay noncarrying

                            //old
                            this->board[old_x_pos][old_y_pos].state = FREE; //free the old state
                        }

                        break;
                    case ANT_DEAD: //new state has ant dead
                        if (oldState != ANT_CARRYING) {
                            if (pickOrNot(liveAntsInBoard[i])) {
                                pick++;
                                this->board[x_pos][y_pos].state = ANT_CARRYING; //drop and stay above

                                //old
                                this->board[old_x_pos][old_y_pos].state = FREE; //free the old state
                            } else {
                                this->board[x_pos][y_pos].state = ANT_DEAD_AND_NONCARRYING; //stay carrying

                                //old
                                this->board[old_x_pos][old_y_pos].state = FREE; //free the old state
                            }
                        }
                        break;
                }


                //walk to new   
                liveAntsInBoard[i].x_pos = x_pos;
                liveAntsInBoard[i].y_pos = y_pos;
         */
        //  std::cout << "[" << liveAntsInBoard[i].x_pos << "," << liveAntsInBoard[i].y_pos << "] => [" << x_pos << "," << y_pos << "]" << this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].valueOfCell() << std::endl;
    }
    //cout << "ended! " << endl;
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

    if (pos > this->maxBoardAcess) {
        pos = this->maxBoardAcess;
    } else if (pos < this->minBoardAcess) {
        pos = this->minBoardAcess;
    }

    return pos;
}

/**
 * Count the actual dead ants nearby
 * @param ant
 * @return 
 */
int Board::visionRadiusCount(Ant &ant) {

    int count_dead_ants = 0;
    int x_pos_start = truncatePosition(ant.x_pos - this->VISION_RADIUS);
    int x_pos_end = truncatePosition(ant.x_pos + this->VISION_RADIUS);

    int y_pos_start = truncatePosition(ant.y_pos - this->VISION_RADIUS);
    int y_pos_end = truncatePosition(ant.y_pos + this->VISION_RADIUS);

    for (int i = x_pos_start; i <= x_pos_end; i++) {
        for (int j = y_pos_start; j <= y_pos_end; j++) {
            if (this->board[i][j].state == ANT_DEAD) {
                count_dead_ants++;
            }
        }
        return count_dead_ants;
    }
}

/* 
 *  Stochastic behaviors to pick or not a dead ant
 */
bool Board::pickOrNot(Ant &ant) {

    int deadAntsInVision = visionRadiusCount(ant);

    float propPickOrNot = (PROP_PICK / (PROP_PICK + deadAntsInVision));
    propPickOrNot *= propPickOrNot; //^2

    if (propPickOrNot > PROP_PICK) {
        pick++;
        return true;
    }

    return false;
}

/* 
 *  Stochastic behaviors to drop or not a dead ant
 */
bool Board::dropOrNot(Ant &ant) {
    if (this->board[ant.x_pos][ant.y_pos].state == ANT_NONCARRING
            || this->board[ant.x_pos][ant.y_pos].state == ANT_DEAD_AND_NONCARRYING) return false; //is not carrying 

    int deadAntsInVision = visionRadiusCount(ant);

    float propDropOrNot = (deadAntsInVision / (PROP_DROP + deadAntsInVision));
    propDropOrNot *= propDropOrNot; //^2

    if (propDropOrNot > PROP_DROP) {
        drop++;
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

/* Introducao
 * 	Contextualização do problema, justificativa, objetivos, estrutura do relatorio
 * Problematica
 * 	Detalhamento do problema, PEAS e caracteristicas
 * Modelo implementado
 * 	Estratégias utilizadas, definições, definições de implementação, linguagem
 * Experimentos e resultados
 * 	Detalhamento de como os experimentos foram conduzidos (variações do raio, def do numero de itens e tamanho da matriz, quatidade de agentes)
 * 	Mostrar e analisar os resultados
 * Conclusao
 * 	Consideracoes sober o trabalho e sober os resultados obetidos
 * 
 * Referencias
 */
//http://www.eecs.harvard.edu/~rad/courses/cs266/papers/collective.pdf para os Ks
//







