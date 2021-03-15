#ifndef TETROMINO_L_H
#define TETROMINO_L_H

#include "render_object/game/tetromino/tetromino.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_l: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_l(int,int,string);
        /* Destructs an instance of this class. */
        ~Tetromino_l();
    private:
};

#endif