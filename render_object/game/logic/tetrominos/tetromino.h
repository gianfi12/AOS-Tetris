#ifndef TETROMINO_H
#define TETROMINO_H

#define M 4

#include <string>

using namespace std;
class Tetromino {
    // This is an abstract class providing the same methods for all the different tetrominos

    public:
        int * getShape();

        ~Tetromino();

    private:
        // This is the shape of the tetromino
        int shape[M][M];
        // This is the color of the tetromino
        string color;
}
#endif