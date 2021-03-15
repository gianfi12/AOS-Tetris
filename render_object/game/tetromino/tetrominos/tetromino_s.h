#ifndef TETROMINO_S_H
#define TETROMINO_S_H

#include "render_object/game/tetromino/tetromino.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_s: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_s(int,int,string);
        /* Destructs an instance of this class. */
        ~Tetromino_s();
    private:
};

#endif