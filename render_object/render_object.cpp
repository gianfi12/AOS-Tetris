#include "render_object.h"

atomic<bool> isDone;

void readChars(void * argv){
    RenderObject * renderObject = (RenderObject*)argv;
    while(!isDone.load()){
        char lastChar = renderObject->inputManager->getLastChar();
        renderObject->updateState(lastChar);
    }
}

RenderObject::RenderObject(InputManager* input, Terminal* terminal):inputManager(input),terminal(terminal){
    t = Thread::create(readChars ,2048,1,(void*)this,Thread::JOINABLE);
};
