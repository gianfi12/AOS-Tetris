#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h>
#include <sstream>
#include <random>
#include "game.h"

#include "render_object/game/tetromino/tetrominos/tetromino_i.h"
#include "render_object/game/tetromino/tetrominos/tetromino_j.h"
#include "render_object/game/tetromino/tetrominos/tetromino_l.h"
#include "render_object/game/tetromino/tetrominos/tetromino_o.h"
#include "render_object/game/tetromino/tetrominos/tetromino_s.h"
#include "render_object/game/tetromino/tetrominos/tetromino_t.h"
#include "render_object/game/tetromino/tetrominos/tetromino_z.h"


using namespace std;
using namespace miosix;
                                                                            
bool Game::updateState(char c){
    switch (c)
    {
    case (int)ROTATE_RIGHT:
        activeTetromino->rotateClockwise();
        this->drawFrame();
        break;
    case (int)ROTATE_LEFT:
        activeTetromino->rotateAntiClockwise();
        this->drawFrame();
        break;
    case (int)MOVE_DOWN:
        activeTetromino->updatePosition(South);
        this->drawFrame();
        break;
    case (int)MOVE_LEFT:
        activeTetromino->updatePosition(West);
        this->drawFrame();
        break;
    case (int)MOVE_RIGHT:
        activeTetromino->updatePosition(East);
        this->drawFrame();
        break;
    default:
        break;
    }
    
    //TODO update the state based on the received char c
    return true;
}


Tetromino * getRandomTetromino(Game* game){
    int random_tetromino = rand() % 7;
    int random_color = rand() % 6;
    string color;

    switch (random_color)
    {
    case 0:
        color = RED;
        break;
    case 1:
        color = GRN;
        break;
    case 2:
        color = YEL;
        break;
    case 3:
        color = BLU;
        break;
    case 4:
        color = MAG;
        break;
    case 5:
    default:
        color = CYN;
        break;
    }

    switch (random_tetromino)
    {
    case 0:
        return new Tetromino_i(0,COL_TETRIS/2,color,game);
    case 1:
        return new Tetromino_j(0,COL_TETRIS/2,color,game);
    case 2:
        return new Tetromino_l(0,COL_TETRIS/2,color,game);
    case 3:
        return new Tetromino_o(0,COL_TETRIS/2,color,game);
    case 4:
        return new Tetromino_s(0,COL_TETRIS/2,color,game);
    case 5:
        return new Tetromino_t(0,COL_TETRIS/2,color,game);
    case 6:
    default:
        return new Tetromino_z(0,COL_TETRIS/2,color,game);
    }
}

void updateTetrominos(void * argv){
    Game * game = (Game*)argv;
    bool continueRead = true;
    while(!isDone.load() && !game->getIsGameFinished()){
        game->m_activeTetromino.lock();
        if(game->nextTetromino==NULL){
            game->nextTetromino = getRandomTetromino(game);
        }
        if(game->activeTetromino==NULL){
            game->activeTetromino = game->nextTetromino;
            game->nextTetromino = getRandomTetromino(game);
            if(game->actualDrawnedTetromino!=NULL){
                delete game->actualDrawnedTetromino;
                game->actualDrawnedTetromino = NULL;
            }
        }
        if(game->activeTetromino->updatePosition(South)){ // If true, the tetromino has reached its final position.
            game->score += game->updateScoreAndGrid();
            delete game->activeTetromino;
            game->activeTetromino = game->nextTetromino;
            game->nextTetromino = getRandomTetromino(game);
        }
        game->m_activeTetromino.unlock();

        Thread::sleep(game->getTime());
    }
}

Game::Game(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal),timeSlidingDown(1000),isTheGridChanged(true){
    nextTetromino = NULL;
    actualDrawnedTetromino = NULL;
    activeTetromino = NULL;
    score = 0;
    for(int i=0 ; i<GRID_ROW ; i++)
        for(int j=0 ; j<GRID_COL ; j++)
            if(j==0 || i==GRID_ROW-1 || j==GRID_COL-1)
                grid[i][j] = WHT;
            else
                grid[i][j] = BLK;
    t = Thread::create(updateTetrominos,2048,1,(void*)this,Thread::JOINABLE);
};     

bool Game::is_legal(int row, int col) {
    if ((row >= 0 && col >= -1) && (row < GRID_ROW && col <=GRID_COL))
        if(grid[row][col] == BLK)
            return true;
    return false;
}

int Game::updateScoreAndGrid() {

    int streak, temp;     // This is how many row at one time the player canceled.
    bool allRow=false;    // This controls that every cell of the row is filled.
    int flagRows[SHAPE_SIZE] = {-1, -1, -1, -1};    // This flags the rows of the streak.
    streak = 0;

    if(actualDrawnedTetromino!=NULL){
        delete actualDrawnedTetromino;
        actualDrawnedTetromino = NULL;
    }

    // This part computes how many rows the player filled, and flags the startingRow.
    temp = get<0>(activeTetromino->getPosition());      // In this way I get the row of the tetromino.
    for(int i = 0; i < SHAPE_SIZE && (i + temp) < GRID_ROW-1; i++){
        allRow = true;
        for(int j = 0; j < GRID_COL && allRow; j++) {
            if(grid[i + temp][j] == BLK)
                allRow = false;
        }
        if(allRow){
            flagRows[i] = i + temp;
            streak++;
        }
    }

    // This part recomputes the grid.
    for(int i = 0; i <SHAPE_SIZE; i++)
        if(flagRows[i] !=-1){
            bool allBlack = false;
            int r = flagRows[i];
            for(;r>0 && !allBlack;r--){
                allBlack=true;
                for(int c=1;c<COL_TETRIS-1;c++){
                    if(grid[r-1][c]!=BLK)
                        allBlack = false;
                    grid[r][c] = grid[r-1][c];
                }
            }
        }

    switch (streak)
    {
    case 0:
        return 0;
    case 1:
        return 40;
    case 2:
        return 100;
    case 3:
        return 300;
    case 4:
        return 1200;
    
    default:
        return 0;
    }
}

void Game::addCellToGrid(int row, int col, string color){
    grid[row][col] = color;
    isTheGridChanged = true;
}


Game::~Game(){
    
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}

DrawObject Game::scoreDrawObject() {
    string scoreString = "SCORE:\n";
    ostringstream ss;
    ss<<score;
    scoreString += ss.str();
    scoreString+="\n";
    return DrawObject(scoreString, WHT);
}

                                                                                
RenderObject * Game::drawFrame() {   
    Lock<Mutex> lock(m);  
    m_grid.lock();
    if(isTheGridChanged){ //comment this if you want to reset the screen at each frame
        terminal->resetScreen();
        terminal->drawOnScreen(nextTetromino->toDrawObject(),0,2);
        terminal->drawOnScreen(scoreDrawObject(),0,COL_TETRIS/2);
        terminal->draw2DGridOfColorOnScreen(*grid,GRID_ROW,GRID_COL,GRID_OFFSET,0,BLOCK);
        isTheGridChanged = false;
    }
    m_grid.unlock();
    if(actualDrawnedTetromino!=NULL && !activeTetromino->isCompleted()){ //comment this to avoid revert the previous tetromino print if you reset the screen at each frame
        terminal->revertDrawObject(*actualDrawnedTetromino, prevRow + GRID_OFFSET, prevCol,BLOCK);
        delete actualDrawnedTetromino;
    }
    m_activeTetromino.lock();
    int rowT, colT;
    tie(rowT,colT) = activeTetromino->getPosition();
    DrawObject temp = activeTetromino->toDrawObject();
    actualDrawnedTetromino = new DrawObject(temp.getObjectString(),temp.getObjectColor());
    prevCol = colT;
    prevRow = rowT;
    terminal->drawOnScreenMovingCursor(temp, rowT + GRID_OFFSET, colT,BLOCK);
    m_activeTetromino.unlock();


    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL; 
}                                                                               
             