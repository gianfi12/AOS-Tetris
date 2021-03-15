#include "tetromino.h"

Tetromino::Tetromino(int row, int col, string color, Game game):row(row),col(col),color(color),game(game){

};

void Tetromino::drawTetromino(){
    //TODO draw the tetromino on screen
}

void Tetromino::rotateClockwise(){
    bool temp [SHAPE_SIZE] [SHAPE_SIZE];
    memcpy(temp, shape, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool)); // Coping the matrix into a temporary element

    // Rotating the matrix clockwise
    transpose(temp);
    reverse_rows(temp);

    // Checking if the rotation is legal; if it is not, returns
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++)
            if(temp[i][j] == true && !game.is_legal(row + i, col + j))
                return;
    //Update the shape
    memcpy(shape, temp, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool));
}

void Tetromino::rotateAntiClockwise(){
    bool temp [SHAPE_SIZE] [SHAPE_SIZE];
    memcpy(temp, shape, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool)); // Coping the matrix into a temporary element

    // Rotating the matrix anticlockwise
    transpose(temp);
    reverse_cols(temp);

    // Checking if the rotation is legal; if it is not, returns
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++)
            if(!game.is_legal(row + i, col + i))
                return;

    //Update the shape
    memcpy(shape, temp, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool));
}

bool Tetromino::updatePosition(){
    // Made this method bool so we know when we have to spawn a new tetromino
    bool temp[SHAPE_SIZE][SHAPE_SIZE];
    memcpy(temp, shape, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool));

}

void Tetromino::transpose(bool mat[SHAPE_SIZE][SHAPE_SIZE]){
    for (int i = 0; i < SHAPE_SIZE; i++)
        for (int j = 0; j < SHAPE_SIZE; j++){
            swap(mat[i][j], mat[j][i]);
        }
}

void Tetromino::reverse_rows(bool mat[SHAPE_SIZE][SHAPE_SIZE]){
    int k;
    for (int i = 0; i < SHAPE_SIZE; i++){
        k = SHAPE_SIZE - 1;
        for (int j = 0; j < SHAPE_SIZE; j++){
            swap(mat[i][j], mat[i][k]);
            k--;
        }
        
    }
    
}

void Tetromino::reverse_cols(bool mat[SHAPE_SIZE][SHAPE_SIZE]){
    int k;
    for(int i = 0; i < SHAPE_SIZE; i++) {
        k = SHAPE_SIZE - 1;
        for(int j = 0; j < k; j++) {
            swap(mat[j][i], mat[k][i]);
        }
    }
}