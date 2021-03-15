#include "tetromino_o.h"
#include "terminal/utility.h"
Tetromino_o::Tetromino_o(int row, int col, string color, Game game):Tetromino(row,col,color,game){
    shape[0][0] = false;
    shape[0][1] = false;
    shape[0][2] = false;
    shape[0][3] = false;

    shape[1][0] = false;
    shape[1][1] = true;
    shape[1][2] = true;
    shape[1][3] = false;

    shape[2][0] = false;
    shape[2][1] = true;
    shape[2][2] = true;
    shape[2][3] = false;

    shape[3][0] = false;
    shape[3][1] = false;
    shape[3][2] = false;
    shape[3][3] = false;

    color = YEL;
};