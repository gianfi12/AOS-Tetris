#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "miosix.h"
#include <time.h>
#include <stdlib.h>  

#include <fcntl.h>
#include "terminal/terminal.h"
#include "render_object/menu/menu.h"
#include "terminal/input_manager.h"


using namespace std;
using namespace miosix;

int main()
{
    srand (time(NULL));

    int row = 0, col = 0;

    InputManager inputManager;
    Terminal terminal(&inputManager);
    terminal.getPos(&row,&col);
    if(row<ROW_TETRIS || col<COL_TETRIS){
        printf("The terminal size is not enough, exiting.\n");
        return -1;
    }

    RenderObject * actualRenderObject = new Menu(&inputManager, &terminal);
    while (!isDone)
    {
        terminal.resetScreen();
        //TODO check the condition if a signal handler can be used.
        RenderObject * returnedRenderObject = actualRenderObject->drawFrame();
        if(returnedRenderObject!=NULL){
            delete actualRenderObject;
            actualRenderObject = returnedRenderObject;
        }
        Thread::sleep(500);
    }
    


    
    // printf("(%d,%d)\n",col,row);
    //TODO: follow example in https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
    //TODO: use another thread to read the input from keyboard and not displaying it in some way and then add a queue in which puts the input, that is read in the other part by some class that is mainting a state used to draw the frame
    
    //TODO: use instead the main loop in order to draw frames
    //TODO: use external file to draw each object, and pass the content to this file at a function like drawObject() that move the cursor where to write on screen for represents this object and takes also the color of them and where to leave the cursor at the end
    //TODO: set the screen dimension fixed to a 50x50 and then center it in other cases?
    delete actualRenderObject;
    terminal.resetScreen();
    return 0;
}