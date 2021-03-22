#ifndef TETROMINO_H
#define TETROMINO_H

/* Is the size of the area in which we define each tetromino. */
#define SHAPE_SIZE 4

#include <string>
#include <tuple>
#include "render_object/game/game.h"
#include "render_object/draw_object/draw_object.h"

using namespace std;

/* Is the enum with the direction in which the tetromino can move. */
enum Direction { North, South, East, West };


class Game;

/* This is an abstract class providing the same methods for all the different tetrominoes. */
class Tetromino {
    public:
        /* Constructs an instance of this class. It requires the starting position of the tetromino. */
        Tetromino(int,int,string, Game *);
        /* Destructs an instance of this class. */
        virtual ~Tetromino() {};

        /* Draw this tetromino on screen. */
        void drawTetromino();
        /* Rotate the tetromino in a clockwise way. */
        void rotateClockwise();
        /* Rotate the tetromino in an anti-clockwise way. */
        void rotateAntiClockwise();

        /* Returns a string that should be printed on screen. */
        DrawObject toDrawObject();

        /* Changes the position of the Tetromino after a certain amount of time. 
        Returns true if the tetromino has reached the lower bottom and a new one has to be spawned.*/
        bool updatePosition(Direction Direction);

        /* Returns a tuple with the row and column of such a Tetromino on the grid. */
        tuple<int,int> getPosition() { return {row,col}; };
    protected:
        /* This is the shape of the tetromino. */
        bool shape[SHAPE_SIZE][SHAPE_SIZE];
        /* Indicates the position of the left higher position of the tetromino's shape on the 
        game's grid. */
        int row,col;
        /* This is the color of the tetromino. */
        string color;
        /* This is the game that the tetromino belongs to */
        Game * game;
        /* This computes the transpose of a matrix */
        void transpose(bool mat[SHAPE_SIZE][SHAPE_SIZE]);
        /* This reverts the rows of a matrix - useful for clockwise rotations */
        void reverse_rows(bool mat[SHAPE_SIZE][SHAPE_SIZE]);
        /* This reverts the columns of a matrix - useful for anti-clockwise rotations */
        void reverse_cols(bool mat[SHAPE_SIZE][SHAPE_SIZE]);
};

#endif