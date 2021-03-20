#include "tetromino_s.h"
#include "terminal/utility.h"
Tetromino_s::Tetromino_s(int row, int col, string color, Game *game):Tetromino(row,col,color,game){
    shape[0][0] = false;
    shape[0][1] = false;
    shape[0][2] = false;
    shape[0][3] = false;

    shape[1][0] = false;
    shape[1][1] = true;
    shape[1][2] = true;
    shape[1][3] = false;

    shape[2][0] = true;
    shape[2][1] = true;
    shape[2][2] = false;
    shape[2][3] = false;

    shape[3][0] = false;
    shape[3][1] = false;
    shape[3][2] = false;
    shape[3][3] = false;

    color = GRN;
};

Tetromino_s::~Tetromino_s(){
    
}