#ifndef GAME_H
#define GAME_H

#include "render_object/render_object.h"

using namespace std;

class Tetromino;

/* This class represents the render object that is responsible for drawing frame during the game. */
class Game: public RenderObject{
    public:
        /* Constructs an instance of this Game. */
        Game(InputManager *,Terminal *);
        /* Destroy an instace of the Game. */
        ~Game();
        /* Draw the actual frame based on the actual state, bu using the primitive
        provided by Terminal. If the returned RenderObject is != null than we the actual one has finished its work
        and the returned one has to draw the next frame. */
        RenderObject * drawFrame();
        /* Update the state of the Game based on the last read char. */
        bool updateState(char c);
        /* Gives a feedback about a certain element of the grid. */
        bool is_legal(int row, int col);
        /* Returns true if the game is finished. */
        bool getIsGameFinished(){ return isGameFinished; };
        /* Is the tetromino that is actually sliding down. */
        Tetromino * activeTetromino;
        /* Is the next spawned tetromino. */
        Tetromino * nextTetromino;
        /* Returns the actual refresh time del terminal. */
        int getTime(){ return time; };
        /* This is the score of the match. */
        int score=0;
        /* Computes the score of the turn, and cancels the rows completely filled. */
        int updateScoreAndGrid();
    private:
        /* Is the file that contains a representation of the object to be printed on screen
        used by this class. */
        string objects_file_name="";
        /* Is the grid that contains all the elements of the grid occupied by a tetromino, as a string that higlight the color of this point in the grid. */
        string grid [ROW_TETRIS] [COL_TETRIS];
        /* Updated time(in milliseconds). */
        int time;
        /* Is the thread responsible for the sliding down of the Tetorminoes. */
        Thread * t;
        /* Tells if the game is finished. */
        bool isGameFinished;
};

#endif