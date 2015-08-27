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

Board::Board(int size, int live_ants, int dead_ants, int radius) {

    this->size = size + 1;
    this->live_ants = live_ants;
    this->dead_ants = dead_ants;
    this->radius = radius;
    this->total_ants = this->live_ants + this->dead_ants;
    this->minBoardAcess = 1;
    this->maxBoardAcess = this->size - 1;

    this->liveAntsInBoard = new Ant[this->size];

    this->board = new Cell*[this->size];
    for (int i = 0; i <= this->size; i++) {
        this->board[i] = new Cell[this->size]();
    }

    //start with barriers
    for (int i = 0; i <= this->size; i++) {
        this->board[i][0].state = BARRIER;
        this->board[i][this->size].state = BARRIER;

        this->board[0][i].state = BARRIER;
        this->board[this->size][i].state = BARRIER;
    }

    populateBoard();
}

void Board::populateBoard() {

    int dead_ants = 0;
    int live_ants = 0;
    int x_pos, y_pos;
    while (dead_ants < this->dead_ants) {

        do {
            x_pos = random(minBoardAcess,maxBoardAcess);
            y_pos = random(minBoardAcess,maxBoardAcess);
        } while (!(this->board[x_pos][y_pos].state == FREE));

        this->board[x_pos][y_pos].state = ANT_DEAD;

        dead_ants++;
    }

    while (live_ants < this->live_ants) {

        do {
            x_pos = random(minBoardAcess,maxBoardAcess);
            y_pos = random(minBoardAcess,maxBoardAcess);
        } while (!(this->board[x_pos][y_pos].state == FREE));

        this->board[x_pos][y_pos].state = ANT_NONCARRING;

        this->liveAntsInBoard[live_ants] = Ant(x_pos, y_pos);
        std::cout << "[" << this->liveAntsInBoard[0].x_pos << "," << this->liveAntsInBoard[0].y_pos << "]" << std::endl;
        live_ants++;
    }

    //TODO bugfix
    this->board[this->size][this->size].state = BARRIER;


    for (int i = 0; i != this->live_ants; i++) {
        std::cout << "[" << this->liveAntsInBoard[i].x_pos << "," << this->liveAntsInBoard[i].y_pos << "] => " << this->board[this->liveAntsInBoard[i].x_pos][this->liveAntsInBoard[i].y_pos].valueOfCell() << std::endl;
    }
}

void Board::printBoard() {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            std::cout << this->board[i][j].valueOfCell();
        }
        std::cout << std::endl;

    }
}

void Board::iterateBoard() {

    vector<Ant>::iterator it;
    int x_pos, y_pos;

    // now start at from the beginning
    // and keep iterating over the element till you find
    // nth element...or reach the end of vector.
    for (int i = 0; i < this->live_ants; i++) {

        //walk ant
        EnumBoard stateInNewCell;
        do {
            x_pos =  randomMove(liveAntsInBoard[i].x_pos);
            y_pos = randomMove(liveAntsInBoard[i].y_pos);            
           

            stateInNewCell = this->board[x_pos][y_pos].state;
        } while (stateInNewCell != FREE && stateInNewCell != ANT_DEAD && stateInNewCell != BARRIER);


        //update old
        EnumBoard oldState = this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state;
        this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = FREE; //can put a dead ant

        std::cout << "[" << liveAntsInBoard[i].x_pos << "," << liveAntsInBoard[i].y_pos << "] => [" << x_pos << "," << y_pos << "]" << this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].valueOfCell() << std::endl;

        //update new
        liveAntsInBoard[i].x_pos = x_pos;
        liveAntsInBoard[i].y_pos = y_pos;
        this->board[liveAntsInBoard[i].x_pos][liveAntsInBoard[i].y_pos].state = oldState;
    }
}

int Board::random(int min, int max) {
	return min + (rand() % (int) (max - min + 1));
}

//walk one cell
int Board::randomMove(int pos_now) {
	int min = pos_now - 1;
	int max = pos_now + 1;
	return truncateMove(min + (rand() % (int) (max - min + 1)));
}

int Board::truncateMove(int pos){
	
	if(pos > this->maxBoardAcess){
		pos = this->maxBoardAcess;
	}else if(pos < this->minBoardAcess){
		pos = this->minBoardAcess;
	}
	
	return pos;
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








