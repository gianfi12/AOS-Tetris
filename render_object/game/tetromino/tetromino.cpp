#include "tetromino.h"

/* Returns a tuple of two ints from the given direction in which the first element 
represents the movement along the rows, while the second represents the movement along the columns. */
tuple<int,int> getVectorFromDirection(Direction direction){
    switch (direction)
    {
    case North:
        return {-1,0};
    case South:
        return {1,0};
    case East:
        return {0,1};
    case West:
        return {0,-1}; 
    default: 
        return {0,0};
    }
}


Tetromino::Tetromino(int row, int col, string color, Game * game):row(row),col(col),color(color),game(game),hasCompleted(false){

};

void Tetromino::drawTetromino(){
    //TODO draw the tetromino on screen
}

void Tetromino::rotateAntiClockwise(){
    bool mat [SHAPE_SIZE] [SHAPE_SIZE];
    memcpy(mat, shape, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool)); // Coping the matrix into a temporary element

    // Rotating the matrix clockwise
    for (int x = 0; x < SHAPE_SIZE / 2; x++) { 
        for (int y = x; y < SHAPE_SIZE - x - 1; y++) { 
            int temp = mat[x][y]; 
  
            mat[x][y] = mat[y][SHAPE_SIZE - 1 - x]; 
  
            mat[y][SHAPE_SIZE - 1 - x] 
                = mat[SHAPE_SIZE - 1 - x][SHAPE_SIZE - 1 - y]; 
  
            mat[SHAPE_SIZE - 1 - x][SHAPE_SIZE - 1 - y] 
                = mat[SHAPE_SIZE - 1 - y][x]; 
  
            mat[SHAPE_SIZE - 1 - y][x] = temp; 
        } 
    } 

    // Checking if the rotation is legal; if it is not, returns
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++)
            if(mat[i][j] == true && !game->is_legal(row + i, col + j))
                return;
    //Update the shape
    memcpy(shape, mat, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool));
}

void Tetromino::rotateClockwise(){
    bool a [SHAPE_SIZE] [SHAPE_SIZE];
    memcpy(a, shape, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool)); // Coping the matrix into a temporary element

    // Rotating the matrix anticlockwise
    for (int i = 0; i < SHAPE_SIZE / 2; i++) {
        for (int j = i; j < SHAPE_SIZE - i - 1; j++) {
 
            // Swap elements of each cycle
            // in clockwise direction
            int temp = a[i][j];
            a[i][j] = a[SHAPE_SIZE - 1 - j][i];
            a[SHAPE_SIZE - 1 - j][i] = a[SHAPE_SIZE - 1 - i][SHAPE_SIZE - 1 - j];
            a[SHAPE_SIZE - 1 - i][SHAPE_SIZE - 1 - j] = a[j][SHAPE_SIZE - 1 - i];
            a[j][SHAPE_SIZE - 1 - i] = temp;
        }
    }

    // Checking if the rotation is legal; if it is not, returns
    for(int i=0; i<SHAPE_SIZE ; i++)
        for(int j=0; j<SHAPE_SIZE ; j++)
            if(a[i][j] == true && !game->is_legal(row + i, col + j))
                return;

    //Update the shape
    memcpy(shape, a, SHAPE_SIZE*SHAPE_SIZE*sizeof(bool));
}

bool Tetromino::updatePosition(Direction direction){
    int addRow,addCol;
    tie(addRow,addCol) = getVectorFromDirection(direction);

    /* Checks that the movement is legal. If the movement is towards South and it is illegal, the game returns true (a new tetromino needs to be spawned).
    If it is not towards South, but still illegal, the method returns false without updating the row and col. */
    for(int i=0; i<SHAPE_SIZE; i++)
        for(int j=0; j < SHAPE_SIZE; j++)
            if(shape[i][j] == true && !game->is_legal(row + i + addRow, col + j + addCol)){
                if(direction == South) {

                    // If the direction is South, it means that I have to save the tetromino in the grid.
                    game->m_grid.lock();
                    hasCompleted = true;
                    for(int h = 0; h < SHAPE_SIZE; h++)
                        for(int k = 0; k <SHAPE_SIZE; k++)
                            if(shape[h][k])
                                game->addCellToGrid(row+h,col+k, color);
                    game->m_grid.unlock();
                    return true;
                }
                
                return false;
            }
    row+=addRow;
    col+=addCol;
    return false;
}

DrawObject Tetromino::toDrawObject(){
    string s;
    for(int i=0; i<SHAPE_SIZE; i++){
        for(int j=0; j<SHAPE_SIZE; j++)
            if(shape[i][j])
                s+=BLOCK;
            else
                s+=" ";
        s+="\n";
    }
    DrawObject drawObject(s,color);
    return drawObject;
}