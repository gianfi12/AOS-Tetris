#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "miosix.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_LEFT 68
#define ARROW_RIGHT 67

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

/* Set the terminal mode used to display character to the end user */
void setTerminalMode();

/* Set the terminal screen sizes */
int getPos(int *x, int *y);

int main()
{
    int row = 0, col = 0;
    setTerminalMode();
    getPos(&row,&col);
    // printf("(%d,%d)\n",col,row);
    //TODO: follow example in https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
    //TODO: use another thread to read the input from keyboard and not displaying it in some way and then add a queue in which puts the input, that is read in the other part by some class that is mainting a state used to draw the frame
    
    //TODO: use instead the main loop in order to draw frames
    //TODO: use external file to draw each object, and pass the content to this file at a function like drawObject() that move the cursor where to write on screen for represents this object and takes also the color of them and where to leave the cursor at the end
    //TODO: set the screen dimension fixed to a 50x50 and then center it in other cases?
    return 0;
}

void setTerminalMode(){
    //NOTE: follow this link https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html to understand the various mode with termios.h
    struct termios t;
    
    tcgetattr(STDIN_FILENO,&t);
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &t);
    
    return;
}

int getPos(int *x, int *y){
    //NOTE: code provided from https://stackoverflow.com/questions/50884685/how-to-get-cursor-position-in-c-using-ansi-code
    //NOTE: look on wikipedia at https://en.wikipedia.org/wiki/ANSI_escape_code
    char buf[30]={0};
    int ret,i,pow;
    char ch;
    
    //Reset screen
    printf("\e[1;1H\e[2J");
    //Save actual cursos pointer
    printf("\x1b%d",7);
    printf("\n");
    //Set position to the bottom right of the screen
    printf("\x1b[999;999H\n");
    //Print the actual position fo the cursor on the screen
    printf("\x1b[6n\n");
    //Read from stdin the output of the previous character
    for( i = 0, ch = 0; ch != 'R'; i++ )
    {
        ret = read(0, &ch, 1);
        if ( !ret )     {
            fprintf(stderr, "getpos: error reading response!\n");
            return 1;
        }
        buf[i] = ch;
    }
    //Compute the value of x and y from the characters inside buf
    for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        *x = *x + ( buf[i] - '0' ) * pow;

    for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
        *y = *y + ( buf[i] - '0' ) * pow;
    //Reset the screen content
    printf("\e[1;1H\e[2J");
    //Move the cursor back to the starting position
    write(1,"\x1b[0;0H",6);
    //Move the cursor back to the postion where you have saved it with 7
    // printf("\x1b%d",8);
    return 0;
}