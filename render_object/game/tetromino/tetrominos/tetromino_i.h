#ifndef TETROMINO_I_H
#define TETROMINO_I_H

#include "render_object/game/tetromino/tetromino.h"
#include "render_object/game/game.h"

using namespace std;


/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino_i: public Tetromino {
    public:
        /* Constructs an instance of this class.  It requires the starting position of the tetromino. */
        Tetromino_i(int,int,string,Game*);
        /* Destructs an instance of this class. */
        virtual ~Tetromino_i();
    private:
};

#endif