#include <iostream>
#include <fstream>
#include "game.h"
#include "../../rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;
using namespace miosix;
                                                                                
void Game::updateState(char c){
    //TODO update the state based on the received char c
}

void readAndUpdate(void *argv){
    Game * game = (Game*)argv;
    InputManager * inputManager = game->inputManager;
    while (!inputManager->isDone)
    {
        char incomingChar = inputManager->getLastChar();
        game->updateState(incomingChar);
    }   
}

Game::Game(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal){
    //TODO open and parse the file that is saved as objects_file_name
    t = Thread::create(readAndUpdate ,2048,1,(void*)this,Thread::JOINABLE);
};     

Game::~Game(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Game::drawFrame() {     
    //TODO decide which elements to be selected for printing from the objects file.    
    terminal->drawOnScreen("", 0, 0);
    
    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL;
}                                                                               
             