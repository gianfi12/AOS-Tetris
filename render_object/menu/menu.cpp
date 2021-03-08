#include <iostream>
#include <fstream>
#include "menu.h"
#include "../../rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;
using namespace miosix;
                                                                                
void Menu::updateState(char c){
    //TODO update the state based on the received char c
}

void readAndUpdateMenu(void *argv){
    Menu * menu = (Menu*)argv;
    InputManager * inputManager = menu->inputManager;
    while (!inputManager->isDone)
    {
        char incomingChar = inputManager->getLastChar();
        menu->updateState(incomingChar);
    }   
}


Menu::Menu(InputManager * inputManager,Terminal * terminal): RenderObject(inputManager,terminal){
    //TODO open and parse the file that is saved as objects_file_name
    // Following RapidXml guide and this example https://gist.github.com/JSchaenzle/2726944
    // Starts the updateState thread
    t = Thread::create(readAndUpdateMenu ,2048,1,(void*)this,Thread::JOINABLE);
    // xml_document<> doc;
    // xml_node<> * root_node;
    // // Reading the xml file into a vector
    ifstream file ("./rendering.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // // Parse the buffer using the library into doc
    // doc.parse<0>(&buffer[0]);
    // // Find root node
    // root_node = doc.first_node("root");
    // xml_node<> * node = root_node -> first_node("menu") -> first_node("ascii_art");
    // string color = root_node -> first_attribute("color") -> value();
    // string ascii_art = root_node -> value();
    // string title = root_node -> first_attribute("id") -> value();
    // DrawObject titleObject(ascii_art,color);
    // objectMap.insert( {title,titleObject} );
};     

Menu::~Menu(){
    //TODO check a better way to put the destructor on the parent class.
    //TODO this is not effective if the thread is still waiting from a character to be read.(do a write of the NULL_CHAR?) it is already done in the destructor of the input manager.
}
                                                                                
RenderObject * Menu::drawFrame() {     
    //TODO decide which elements to be selected for printing from the objects file.    
    terminal->drawOnScreen(objectMap.at("title"), 0, 0);
    
    //TODO return the new Render Object if a new one is needed, for example when passing from the menu to the game.
    return NULL;
}                                                                               
             