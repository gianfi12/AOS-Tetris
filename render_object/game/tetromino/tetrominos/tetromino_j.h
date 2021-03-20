#ifndef TETROMINO_J_H
#define TETROMINO_J_H

#include "render_object/game/tetromino/tetromino.h"
#include "render_object/game/game.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_j: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_j(int,int,string,Game*);
        /* Destructs an instance of this class. */
        ~Tetromino_j();
    private:
};

#endif