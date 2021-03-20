#ifndef TETROMINO_T_H
#define TETROMINO_T_H

#include "render_object/game/tetromino/tetromino.h"
#include "render_object/game/game.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_t: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_t(int,int,string,Game*);
        /* Destructs an instance of this class. */
        ~Tetromino_t();
    private:
};

#endif