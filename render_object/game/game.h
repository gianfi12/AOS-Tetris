#ifndef GAME_H
#define GAME_H

#include "render_object/render_object.h"

using namespace std;

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
    private:
        /* Is the file that contains a representation of the object to be printed on screen
        used by this class. */
        string objects_file_name="";
        /* Is the grid that contains all the elements of the grid occupied by a tetromino, as a string that higlight the color of this point in the grid. */
        string grid [ROW_TETRIS] [COL_TETRIS];
};

#endif