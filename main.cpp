#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "miosix.h"

#include <fcntl.h>
#include "terminal/terminal.h"
#include "terminal/utility.h"


using namespace std;
using namespace miosix;

// bool isDone=false;
// char lastReadCharacter = 'a';

// void readLine(char *str, int len)
// {
//     if(len==0) return;
//     for(int i=0;i<len;i++)
//     {
//         str[i]=getchar();
//         //in raw mode no conversion of \r to \n is performed!
//         if(str[i]!='\n' && str[i]!='\r' && i!=len-1) continue;
//         str[i]='\0';
//         return;
//     }
// }


// void threadfunc(void *argv){
//     while(!isDone){
//         lastReadCharacter = getchar();
//     }
// }

int main()
{
    int row = 0, col = 0;
    Terminal terminal;
    terminal.getPos(&row,&col);
    if(row<ROW_TETRIS || col<COL_TETRIS){
        printf("The terminal size is not enough, exiting.\n");
        return -1;
    }

    terminal.positionCursorForStartDrawing();
    
    // printf("(%d,%d)\n",col,row);
    //TODO: follow example in https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
    //TODO: use another thread to read the input from keyboard and not displaying it in some way and then add a queue in which puts the input, that is read in the other part by some class that is mainting a state used to draw the frame
    
    //TODO: use instead the main loop in order to draw frames
    //TODO: use external file to draw each object, and pass the content to this file at a function like drawObject() that move the cursor where to write on screen for represents this object and takes also the color of them and where to leave the cursor at the end
    //TODO: set the screen dimension fixed to a 50x50 and then center it in other cases?
    return 0;
}