#include <iostream>
#include <fstream>
#include <algorithm>
#include "menu.h"
#include "../../rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;
using namespace miosix;
                                                                                
void Menu::updateState(char c){
    int charToInt = (int)c;
    //TODO update the state based on the received char c
    if(c==10){
        printf("prova");
    }
}


Menu::Menu(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal){
    menu_draw_objects();
};     

Menu::~Menu(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Menu::drawFrame() {     
    //TODO decide which elements to be selected for printing from the objects file.    
    terminal->drawOnScreen(objectMap.at("title"), 0, 0);

    terminal->drawOnScreen(objectMap.at("playGame"), 20, 12);
    
    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
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
            titleConverted = titleConverted.append(BLOCK); 
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
}
             