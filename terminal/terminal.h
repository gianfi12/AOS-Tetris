#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib> 
#include <termios.h>
#include <string>

#include "utility.h"
#include "render_object/draw_object/draw_object.h"
#include "miosix.h"
#include "terminal/input_manager.h"

using namespace std;
using namespace miosix;

class Terminal{
    public:
        /* Construct and build the terminal management */
        Terminal(InputManager *);
        /* When needed use this method to update the value of col and row */
        int refreshColAndRow();
        /* Get the terminal number of rows and cols */
        void getPos(int *row, int *col);
        /* Set the position of the cursor to the left higher corner of the drawing area, relative
        to the given row and col. */
        void positionCursorForStartDrawing(int posRow, int posCol);
        /* Draw a portion of the screen based on DrawObject
        starting from the position on screen (writingRow, writingCol). */
        void drawOnScreen(DrawObject drawObject, int writingRow, int writingCol);
        /* Resets the content of the screen to be black, and also the color to the default one. 
        It also sets the position of the screen to be in the position set by postionCursorForStartDrawing. */
        void resetScreen();
        /* Draw on screen the DrawObject by moving the cursor only where the string has the substringToCheck. */
        void drawOnScreenMovingCursor(DrawObject drawObject, int writingRow, int writingCol, string substringToCheck);
        /* Draw the given 2D grid of colors on screen. */
        void draw2DGridOfColorOnScreen(string * grid, int totalRow, int totalCol, int startingRow, int startingCol, string printingChar);
        /* Invert the effects on the screen of drawOnScreenMovingCursor by printing the same char but black.
        NOTE: use the BLOCK char if you want to remove all the content in the cell. */
        void revertDrawObject(DrawObject drawObject, int writingRow, int writingCol, string substringToCheck);
    private:
        /* Set the terminal mode used to display character to the end user */
        void setTerminalMode();
        /* Interger value of col and row of the terminal size */
        int col, row;
        /* The instance of the input manager from which take the input that is coming. */
        InputManager * inputManager;
};

#endif