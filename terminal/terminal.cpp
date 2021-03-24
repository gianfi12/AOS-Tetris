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
    positionCursorForStartDrawing(0,0);                             
}          

void Terminal::resetScreen(){
    printf("\x1b[0m");
    printf("\x1b[2J");
    fflush(stdout);
    return;
}

void Terminal::drawOnScreenMovingCursor(DrawObject drawObject, int writingRow, int writingCol, string substringToCheck){
    printf(drawObject.getObjectColor().c_str());
    positionCursorForStartDrawing(writingRow,writingCol);

    string drawString = drawObject.getObjectString();
    int startSub = 0; 
    int colIndex = 0;
    for(int i = 0; i<drawString.size();i++){
        if(drawString[i]=='\n'){
            writingRow++;
            colIndex=0;
        }else if(drawString[i]!=' '){
            bool found = true;
            for(int j=0; j<substringToCheck.size() && found; j++){
                if(drawString[i+j]!=substringToCheck[j])
                    found = false;
            }
            if(found){
                positionCursorForStartDrawing(writingRow,writingCol+colIndex);
                printf("%s",substringToCheck.c_str());
                colIndex++;
            }
        }else{
            colIndex++;
        }
    }
    fflush(stdout);   
    positionCursorForStartDrawing(0,0);
}

void Terminal::draw2DGridOfColorOnScreen(string * grid, int totalRow, int totalCol, int startingRow, int startingCol, string printingChar){
    string actualColor = "";
    for(int i=0; i<totalRow; i++)
        for(int j=0; j<totalCol; j++){
            if(grid[j+i*totalCol]!=BLK){
                if(actualColor==" " || actualColor!=grid[j+i*totalCol]){
                    actualColor = grid[j+i*totalCol];
                    printf(actualColor.c_str());
                }
                positionCursorForStartDrawing(startingRow+i,startingCol+j);
                printf(printingChar.c_str());
            }
        }
    fflush(stdout);
    positionCursorForStartDrawing(0,0);
}

void Terminal::revertDrawObject(DrawObject drawObject, int writingRow, int writingCol, string substringToCheck){
    printf("\x1b[0m");
    positionCursorForStartDrawing(writingRow,writingCol);

    string drawString = drawObject.getObjectString();
    int startSub = 0; 
    int colIndex = 0;
    for(int i = 0; i<drawString.size();i++){
        if(drawString[i]=='\n'){
            writingRow++;
            colIndex=0;
        }else if(drawString[i]!=' '){
            bool found = true;
            for(int j=0; j<substringToCheck.size() && found; j++){
                if(drawString[i+j]!=substringToCheck[j])
                    found = false;
            }
            if(found){
                positionCursorForStartDrawing(writingRow,writingCol+colIndex);
                printf("%s"," ");
                colIndex++;
            }
        }else{
            colIndex++;
        }
    }
    fflush(stdout);  
    positionCursorForStartDrawing(0,0);
}
