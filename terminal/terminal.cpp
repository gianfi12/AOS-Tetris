#include "terminal.h"
#include <string>
#include <fstream>                                                              

Terminal::Terminal(InputManager * inputManager):col(0),row(0),inputManager(inputManager){
    setTerminalMode();
    refreshColAndRow();
}

void Terminal::setTerminalMode(){
    //NOTE: follow this link https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html to understand the various mode with termios.h
    struct termios t;
    
    tcgetattr(STDIN_FILENO,&t);
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &t);
    
    return;
}
int Terminal::refreshColAndRow(){
    //NOTE: code provided from https://stackoverflow.com/questions/50884685/how-to-get-cursor-position-in-c-using-ansi-code
    //NOTE: look on wikipedia at https://en.wikipedia.org/wiki/ANSI_escape_code
    char buf[30]={0};
    int ret,i,pow;
    char ch;
    
    //Reset screen
    printf("\e[1;1H\e[2J\n");
    // //Save actual cursos pointer
    // printf("\x1b%d",7);
    //Set position to the bottom right of the screen
    printf("\x1b[999;999H\n");
    inputManager->startTerminalSequence((char)ESC,'R');
    //Print the actual position fo the cursor on the screen
    printf("\x1b[6n\n");
    fflush(stdout);
    // Read from stdin the output of the previous character
    for( i = 0, ch = 0; ch != 'R'; i++ )
    {
        ch = inputManager->getLastCharForTerminal();
        buf[i] = ch;
    }
    //Compute the value of x and y from the characters inside buf
    for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        col = col + ( buf[i] - '0' ) * pow;

    for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
        row = row + ( buf[i] - '0' ) * pow;
    //Reset the screen content
    printf("\e[1;1H\e[2J");
    //Move the cursor back to the starting position
    write(1,"\x1b[0;0H",6);
    //Move the cursor back to the postion where you have saved it with 7
    // printf("\x1b%d",8);
    return 0;
}

void Terminal::getPos(int *row, int *col){
    *row = this->row;
    *col = this->col;
}

void Terminal::positionCursorForStartDrawing(int posRow, int posCol){
    int startingRow = (row-ROW_TETRIS)/2+1;
    int startingCol = (col-COL_TETRIS)/2+1;
    printf("\x1b[%d;%dH",startingRow+posRow,startingCol+posCol);
    fflush(stdout);
}

void Terminal::drawOnScreen(DrawObject drawObject, int writingRow, int writingCol){ 
    printf(drawObject.getObjectColor().c_str());
    positionCursorForStartDrawing(writingRow,writingCol);

    string drawString = drawObject.getObjectString();
    int startSub = 0; 
    for(int i = 0; i<drawString.size();i++){
        if(drawString[i]=='\n'){
            printf("%s",drawString.substr(startSub,i+1-startSub).c_str());
            fflush(stdout);
            startSub=i+1;
            writingRow = writingRow+1;
            positionCursorForStartDrawing(writingRow,writingCol);
        }
    }
    fflush(stdout);                                                                         
}          

void Terminal::resetScreen(){
    printf("\x1b[0m");
    printf("\x1b[2J");
    fflush(stdout);
    return;
}
