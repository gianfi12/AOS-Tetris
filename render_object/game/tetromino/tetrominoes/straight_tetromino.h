#ifndef STRAIGHTTETROMINO_H
#define STRAIGHTTETROMINO_H

#include "render_object/game/tetromino/tetromino.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class StraightTetromino: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        StraightTetromino(int,int,string);
        /* Destructs an instance of this class. */
        ~StraightTetromino();
    private:
};

#endif