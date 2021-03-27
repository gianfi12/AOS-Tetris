#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "gameover.h"
#include "miosix.h"

using namespace std;
using namespace miosix;
                                                                                
bool Gameover::updateState(char c){
    int charToInt = (int)c;
    //TODO update the state based on the received char c
    if(c==(char)ENTER){
        switchToNextRenderObject = true;
        return false;
    }
    return true;
}


Gameover::Gameover(InputManager * inputManager,Terminal * terminal, int score): RenderObject(inputManager,terminal),switchToNextRenderObject(false),score(score){
    gameover_draw_objects();
};     

Gameover::~Gameover(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Gameover::drawFrame() {    
    if(!switchToNextRenderObject){
        terminal->resetScreen();
        terminal->drawOnScreen(objectMap.at("title"), 0, (COL_TETRIS-38)/2);
        terminal->drawOnScreen(objectMap.at("scoreWriting"), 30, 17);
        terminal->drawOnScreen(objectMap.at("playGame"), 35, 13);
        terminal->drawOnScreen(objectMap.at("exitGame"), 37, 18);
    }else{
        return new Menu(inputManager,terminal);
    }
    return NULL;
}

void Gameover::gameover_draw_objects() {
    string title =  " ######      ###    ##     ## ########\n"   
                    "##    ##    ## ##   ###   ### ##\n"        
                    "##         ##   ##  #### #### ##\n"        
                    "##   #### ##     ## ## ### ## ######\n"     
                    "##    ##  ######### ##     ## ##\n"         
                    "##    ##  ##     ## ##     ## ##\n"         
                    " ######   ##     ## ##     ## ########\n"
                    "\n"
                    " #######  ##     ## ######## ########\n" 
                    "##     ## ##     ## ##       ##     ##\n"
                    "##     ## ##     ## ##       ##     ##\n"
                    "##     ## ##     ## ######   ########\n" 
                    "##     ##  ##   ##  ##       ##   ##\n"  
                    "##     ##   ## ##   ##       ##    ##\n" 
                    " #######     ###    ######## ##     ##\n";
    
    string titleConverted;
    for(int i=0;i<title.size();i++){
        if(title[i]=='#'){
            titleConverted = titleConverted.append(BLOCK_MENU); 
        }else{
            string s(1,title[i]);
            titleConverted = titleConverted.append(s); 
        }
    }   
    DrawObject obj = DrawObject(titleConverted, GRN);
    objectMap.insert( {"title",obj} );

    string scoreWriting = "You have reached a SCORE of:";
    ostringstream ss;
    ss<<score;
    scoreWriting += ss.str();
    scoreWriting+="!\n";
    obj = DrawObject(scoreWriting, BLU);
    objectMap.insert( {"scoreWriting",obj} );

    string playGame = "Press enter to return to the main menu!\n";
    obj = DrawObject(playGame, RED);
    objectMap.insert( {"playGame",obj} );

    string exitGame = "Press q to exit the game!\n";
    obj = DrawObject(exitGame, RED);
    objectMap.insert( {"exitGame",obj} );
}
             