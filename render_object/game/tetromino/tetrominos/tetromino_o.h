#ifndef TETROMINO_O_H
#define TETROMINO_O_H

#include "render_object/game/tetromino/tetromino.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_o: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_o(int,int,string);
        /* Destructs an instance of this class. */
        ~Tetromino_o();
    private:
};

#endif