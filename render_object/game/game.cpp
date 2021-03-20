#include <iostream>
#include <fstream>
#include <stdlib.h> 
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
    //TODO update the state based on the received char c
    return true;
}


Tetromino * getRandomTetromino(Game* game){
        int random = rand() % 7;
        switch (random)
        {
        case 0:
            return new Tetromino_i(0,COL_TETRIS/2,RED,game);
        case 1:
            return new Tetromino_j(0,COL_TETRIS/2,RED,game);
        case 2:
            return new Tetromino_l(0,COL_TETRIS/2,RED,game);
        case 3:
            return new Tetromino_o(0,COL_TETRIS/2,RED,game);
        case 4:
            return new Tetromino_s(0,COL_TETRIS/2,RED,game);
        case 5:
            return new Tetromino_t(0,COL_TETRIS/2,RED,game);
        case 6:
        default:
            return new Tetromino_z(0,COL_TETRIS/2,RED,game);
        }
    }

void updateTetrominoes(void * argv){
    Game * game = (Game*)argv;
    bool continueRead = true;
    while(!isDone.load() && !game->getIsGameFinished()){
        if(game->nextTetromino==NULL){
            game->nextTetromino = getRandomTetromino(game);
        }
        if(game->activeTetromino==NULL){
            game->activeTetromino = game->nextTetromino;
            game->nextTetromino = getRandomTetromino(game);
        }
        game->activeTetromino->updatePosition(South);

        Thread::sleep(game->getTime());
    }
}

Game::Game(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal),time(1000){
    for(int i=0 ; i<ROW_TETRIS ; i++)
        for(int j=0 ; j<COL_TETRIS ; j++)
            grid[i][j] = BLK;
    t = Thread::create(updateTetrominoes ,2048,1,(void*)this,Thread::JOINABLE);
};     

bool Game::is_legal(int row, int col) {
    if ((row >= 0 && col >= 0) && (row < ROW_TETRIS && col < COL_TETRIS))
        if(grid[row][col] == BLK)
            return true;
    return false;
}

Game::~Game(){
    
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Game::drawFrame() {     
    //TODO decide which elements to be selected for printing from the objects file.    
    // terminal->drawOnScreen("", 0, 0);
    
    //TODO draw the tetromino.

    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL;
}                                                                               
             