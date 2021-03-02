#include "render_object.h"

void readChars(void * argv){
    RenderObject * renderObject = (RenderObject*)argv;
    while(!renderObject->isDone.load()){
            char lastChar = renderObject->inputManager->getLastChar();
    renderObject->updateState(lastChar);
    }
}

RenderObject::RenderObject(InputManager* input, Terminal* terminal):inputManager(input),isDone(false),terminal(terminal){
    t = Thread::create(readChars ,2048,1,(void*)this,Thread::JOINABLE);

};
