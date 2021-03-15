#ifndef TETROMINO_Z_H
#define TETROMINO_Z_H

#include "render_object/game/tetromino/tetromino.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_z: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_z(int,int,string);
        /* Destructs an instance of this class. */
        ~Tetromino_z();
    private:
};

#endif