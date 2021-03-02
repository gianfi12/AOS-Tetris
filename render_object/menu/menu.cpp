#include "menu.h"                                                               
                                                                                
void updateState(void * argv){
    InputManager * inputManager = (InputManager*)argv;
    while (!inputManager->isDone)
    {
        inputManager->putChar(getchar());
    }
}

Menu::Menu(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal){
    //TODO open and parse the file that is saved as objects_file_name
};     

Menu::~Menu(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?)_
    isDone.store(true);
}
                                                                                
RenderObject * Menu::drawFrame() {     
    //TODO decide which elements to be selected for printing from the objects file.    
    terminal->drawOnScreen("", 0, 0);
    
    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL;
}                                                                               
             