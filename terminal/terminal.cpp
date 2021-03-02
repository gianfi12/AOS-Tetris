#include "terminal.h"
#include <string>
#include <fstream>                                                              

Terminal::Terminal():col(0),row(0){
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
            return -1;
        }
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

void Terminal::positionCursorForStartDrawing(){
    int startingRow = (row-ROW_TETRIS)/2+1;
    int startingCol = (col-COL_TETRIS)/2+1;
    printf("\x1b[0m");
    printf("\x1b[%d;%dH",startingRow,startingCol);
    fflush(stdout);
    // //Set text color
    // printf("%s",BLU);
    // //Set background color
    // printf("%s",BLUB);
    // fflush(stdout);
    // string str;
    // for(int i=0; i<ROW_TETRIS; i++){
    //     printf("\x1b[%d;%dH",startingRow+i,startingCol);
    //     fflush(stdout);    
    //     for(int j=0; j<COL_TETRIS; j++){
    //             printf("\x20");
    //             fflush(stdout);
    //     }
    // }
}

void Terminal::drawOnScreen(string printString, int writingRow, int writingCol){ 
    //TODO print only the content of printString starting from writingRow and writingCol.                                                            
    // printf("\x1b[0m");                                                          
    // string line;    
    // std::fstream file(file_name);                                               
    // while(std::getline(file, line)) {                                           
    //     printf("%s %d %d\n", line.c_str(), writingRow, writingCol);                   
    //     fflush(stdout);                                                         
    //     writingRow++;                                                           
    // }                                                                           
}          