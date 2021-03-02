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

using namespace std;

class Terminal{
    public:
        /* Construct and build the terminal management */
        Terminal();
        /* At each frame update this method to change the value of col and row */
        int refreshColAndRow();
        /* Set the terminal screen sizes */
        void getPos(int *row, int *col);
        /* Set the position of the cursor to the left higher corner of the drawing area */
        void positionCursorForStartDrawing();
        /* Draw a portion of the screen based on the content of printString
        starting from the position on screen (writingRow, writingCol). */
        void drawOnScreen(string printString, int writingRow, int writingCol);
    private:
        /* Set the terminal mode used to display character to the end user */
        void setTerminalMode();
        /* Interger value of col and row of the terminal size */
        int col, row;
};

#endif