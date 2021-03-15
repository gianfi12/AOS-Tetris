#include "tetromino.h"

Tetromino::Tetromino(int row, int col, string color):row(row),col(col),color(color){

};

void Tetromino::drawTetromino(){
    //TODO draw the tetromino on screen
}

void Tetromino::rotateClockwise(){
    //TODO we must check if the object can be rotate, for example if it is near the border it cannot go out(?) use the grid in order to do so
    bool temp [SHAPE_SIZE] [SHAPE_SIZE];
    // Compute the new shape
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            temp[i][j] = shape[j][SHAPE_SIZE-1-i];
        } 
    // Clear the old shape
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            shape[i][j] = false;
        } 
    //Update the shape
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            shape[i][j] = temp[i][j];
        } 
}

void Tetromino::rotateAntiClockwise(){
    //TODO we must check if the object can be rotate, for example if it is near the border it cannot go out(?) use the grid in order to do so
    bool temp [SHAPE_SIZE] [SHAPE_SIZE];
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            temp[i][j] = shape[SHAPE_SIZE-1-j][SHAPE_SIZE-1-i]; //TODO this inversion
        } 
    // Clear the old shape
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            shape[i][j] = false;
        } 
    //Update the shape
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++){
            shape[i][j] = temp[i][j];
        } 
}

void Tetromino::updatePosition(){
    //TODO update position, maybe the game class with a thread that every tot seconds update the position(?)
    //NOTE: remember to check that the tetromino doesn't go outside the draw area
}