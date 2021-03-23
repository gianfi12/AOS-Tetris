#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h>
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
    case (int)ROTATE_LEFT:
        activeTetromino->rotateClockwise();
        terminal->resetScreen();
        this->drawFrame();
        break;
    case (int)ROTATE_RIGHT:
        activeTetromino->rotateAntiClockwise();
        terminal->resetScreen();
        this->drawFrame();
        break;
    case (int)MOVE_DOWN:
        activeTetromino->updatePosition(South);
        terminal->resetScreen();
        this->drawFrame();
        break;
    case (int)MOVE_LEFT:
        activeTetromino->updatePosition(West);
        terminal->resetScreen();
        this->drawFrame();
        break;
    case (int)MOVE_RIGHT:
        activeTetromino->updatePosition(East);
        terminal->resetScreen();
        this->drawFrame();
        break;
    default:
        break;
    }
    
    //TODO update the state based on the received char c
    return true;
}


Tetromino * getRandomTetromino(Game* game){
        srand (time(NULL));
        int random = rand() % 7;
        srand(time(NULL));
        int random_color = rand() % 7;
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
            color = CYN;
            break;
        case 6:
        default:
            color = WHT;
            break;
        }

        switch (random)
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
        }
        if(game->activeTetromino->updatePosition(South)){ // If true, the tetromino has reached its final position.
            game->score += game->updateScoreAndGrid();
            game->activeTetromino = game->nextTetromino;
            game->nextTetromino = getRandomTetromino(game);
        }
        game->m_activeTetromino.unlock();

        Thread::sleep(game->getTime());
    }
}

Game::Game(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal),timeSlidingDown(1000){
    nextTetromino = NULL;
    activeTetromino = NULL;
    for(int i=0 ; i<ROW_TETRIS ; i++)
        for(int j=0 ; j<COL_TETRIS ; j++)
            grid[i][j] = BLK;
    t = Thread::create(updateTetrominos,2048,1,(void*)this,Thread::JOINABLE);
};     

bool Game::is_legal(int row, int col) {
    if ((row >= 0 && col >= 0) && (row < ROW_TETRIS && col < COL_TETRIS))
        if(grid[row][col] == BLK)
            return true;
    return false;
}

int Game::updateScoreAndGrid() {

    int streak;     // This is how many row at one time the player canceled.
    bool allRow;    // This controls that every cell of the row is filled.
    int flagRow;    // This flags the starting row of the streak.
    flagRow = -1;

    //TODO maybe we can use only the row that are occupied by the shape of the actualTetromino
    // This part computes how many rows the player filled, and flags the startingRow.
    for(int i = 0, streak = 0; i < ROW_TETRIS; i++){
        for(int j = 0, allRow = true; j < COL_TETRIS; j++) {
            if(grid[i][j] == BLK)
                allRow = false;
        }
        if(allRow){
            if(flagRow == -1)
                flagRow = i;
            streak++;
        }
    }

    // This part recomputes the grid.
    if(flagRow != -1) {
        for(int i = 0; i < streak; i++)
            for(int j = 0; j < COL_TETRIS; j++){
                grid[i][j] = grid[i + streak][j];
                grid[i + streak][j] = BLK;
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
}


Game::~Game(){
    
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}

DrawObject gridToDrawObject(string grid[ROW_TETRIS][COL_TETRIS]){
    // TODO How to deal with different colors?
    string drawString;
    for(int i = 0; i < ROW_TETRIS; i++){
        for(int j = 0; j < COL_TETRIS; j++)
            if(grid[i][j] == BLK)
                drawString += ' ';
            else drawString += BLOCK;
        drawString += '\n';
    }
    return DrawObject(drawString, WHT);
}

                                                                                
RenderObject * Game::drawFrame() {   
    Lock<Mutex> lock(m);  
    //TODO decide which elements to be selected for printing from the objects file.    
    // terminal->drawOnScreen("", 0, 0);
    
    //TODO draw the tetromino and the grid altogether.
    m_activeTetromino.lock();
    int rowT, colT;
    tie(rowT,colT) = activeTetromino->getPosition();
    // terminal->drawOnScreen(activeTetromino->toDrawObject(), rowT + GRID_OFFSET, colT);
    terminal->drawOnScreenMovingCursor(activeTetromino->toDrawObject(), rowT + GRID_OFFSET, colT,BLOCK);
    m_activeTetromino.unlock();


    //TODO print a bar to indicate the end of the grid
    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL; 
}                                                                               
             