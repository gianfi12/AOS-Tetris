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


Tetromino::Tetromino(int row, int col, string color, Game * game):row(row),col(col),color(color),game(game){

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
    int N = SHAPE_SIZE;
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
 
            // Swap elements of each cycle
            // in clockwise direction
            int temp = a[i][j];
            a[i][j] = a[N - 1 - j][i];
            a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
            a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
            a[j][N - 1 - i] = temp;
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
    // Made this method bool so we know when we have to spawn a new tetromino, update score and eventually remove some rows.
    int addRow,addCol;
    tie(addRow,addCol) = getVectorFromDirection(direction);

    /* Checks that the movement is legal. If the movement is towards South and it is illegal, the game returns true (a new tetromino needs to be spawned).
    If it is not towards South, but still illegal, the method returns false without updating the row and col. */
    for(int i=0; i<SHAPE_SIZE; i++)
        for(int j=0; j < SHAPE_SIZE; j++)
            if(shape[i][j] == true && !game->is_legal(row + i + addRow, col + j + addCol))
                if(direction == South)
                    return true;
                else return false;
    row+=addRow;
    col+=addCol;
    return false;
}

void Tetromino::transpose(bool mat[SHAPE_SIZE][SHAPE_SIZE]){
    for (int i = 0; i < SHAPE_SIZE; i++)
        for (int j = 0; j < SHAPE_SIZE; j++){
            swap(mat[i][j], mat[j][i]);
        }
}

void Tetromino::reverse_rows(bool mat[SHAPE_SIZE][SHAPE_SIZE]){
    int k;
    for (int i = 0; i < SHAPE_SIZE/2; i++){
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