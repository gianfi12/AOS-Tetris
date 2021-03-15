#include "render_object.h"

atomic<bool> isDone;

void readChars(void * argv){
    RenderObject * renderObject = (RenderObject*)argv;
    bool continueRead = true;
    while(!isDone.load() && continueRead){
        char lastChar = renderObject->inputManager->getLastChar();
        continueRead = renderObject->updateState(lastChar);
    }
}

RenderObject::RenderObject(InputManager* input, Terminal* terminal):inputManager(input),terminal(terminal){
    t = Thread::create(readChars ,2048,1,(void*)this,Thread::JOINABLE);
};
