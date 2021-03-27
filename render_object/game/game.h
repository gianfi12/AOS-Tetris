#ifndef GAME_H
#define GAME_H

// #define GRID_ROW (ROW_TETRIS-GRID_OFFSET)
#define GRID_ROW 20
#define GRID_COL 25

#include "render_object/render_object.h"
#include "render_object/gameover/gameover.h"

using namespace std;

class Tetromino;
class Gameover;

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
        int getTime(){ return timeSlidingDown; };
        /* This is the score of the match. */
        int score=0;
        /* Computes the score of the turn, and cancels the rows completely filled. */
        int updateScoreAndGrid();
        /* This method lets add a cell to the grid. */
        void addCellToGrid(int row, int col, string color);

        /* Used to get the lock on the drawFrame method. */
        Mutex m,m_activeTetromino, m_grid;


        /* Is the reference to the previous drawned tetromino. */
        DrawObject * actualDrawnedTetromino;
        /* Save also the row and the col where you have drawned the previous tetromino. */
        int prevCol, prevRow;
        /* Returns true if the game is finished */
        bool checkGameFinished();
    private:
        /* Is the file that contains a representation of the object to be printed on screen
        used by this class. */
        string objects_file_name="";
        /* Is the grid that contains all the elements of the grid occupied by a tetromino, as a string that higlight the color of this point in the grid. */
        string grid [GRID_ROW] [GRID_COL];
        /* Updated time(in milliseconds). */
        int timeSlidingDown;
        /* Is the thread responsible for the sliding down of the Tetorminoes. */
        Thread * t;
        /* Tells if the game is finished. */
        bool isGameFinished;
        /* This method returns the DrawObject of the score. */
        DrawObject scoreDrawObject();
        /* Tells whether the previous grid is changed. */
        bool isTheGridChanged;

        /* Is the reference to the next gameover screen */
        Gameover * gameover;
        /* Mutex used to access the gameover saved instance */
        Mutex m_gameover;
};

#endif