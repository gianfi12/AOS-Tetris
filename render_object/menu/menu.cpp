#include <iostream>
#include <fstream>
#include <algorithm>
#include "menu.h"

using namespace std;
using namespace miosix;
                                                                                
bool Menu::updateState(char c){
    int charToInt = (int)c;
    //TODO update the state based on the received char c
    if(c==(char)ENTER){
        switchToNextRenderObject = true;
        return false;
    }
    return true;
}


Menu::Menu(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal),switchToNextRenderObject(false){
    menu_draw_objects();
};     

Menu::~Menu(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Menu::drawFrame() {    
    if(!switchToNextRenderObject){
        terminal->resetScreen();
        terminal->drawOnScreen(objectMap.at("title"), (COL_TETRIS-49)/2, 0);
        terminal->drawOnScreen(objectMap.at("playGame"), 20, 12);
        terminal->drawOnScreen(objectMap.at("exitGame"), 21, 14);
    }else{
        return new Game(inputManager,terminal);
    }
    return NULL;
}

void Menu::menu_draw_objects() {
    string title =  "######## ######## ######## ########  ####  ######\n"
                    "   ##    ##          ##    ##     ##  ##  ##    ##\n"
                    "   ##    ##          ##    ##     ##  ##  ##\n"
                    "   ##    ######      ##    ########   ##   ######\n"
                    "   ##    ##          ##    ##   ##    ##        ##\n"
                    "   ##    ##          ##    ##    ##   ##  ##    ##\n"
                    "   ##    ########    ##    ##     ## ####  ######\n";
    
    string titleConverted;
    for(int i=0;i<title.size();i++){
        if(title[i]=='#'){
            titleConverted = titleConverted.append(BLOCK_MENU); 
        }else{
            string s(1,title[i]);
            titleConverted = titleConverted.append(s); 
        }
    }   
    DrawObject obj = DrawObject(titleConverted, BLU);
    objectMap.insert( {"title",obj} );

    string playGame = "Press enter to play the game!\n";
    obj = DrawObject(playGame, RED);
    objectMap.insert( {"playGame",obj} );

    string exitGame = "Press q to exit the game!\n";
    obj = DrawObject(exitGame, RED);
    objectMap.insert( {"exitGame",obj} );
}
             