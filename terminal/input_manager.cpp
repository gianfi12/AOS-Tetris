#include "input_manager.h"

void readStdout(void * argv){
    InputManager * inputManager = (InputManager*)argv;
    while (!inputManager->isDone)
    {
        inputManager->putChar(getchar());
    }
}

InputManager::InputManager():isDone(false){
    t = Thread::create(readStdout ,2048,1,(void*)this,Thread::JOINABLE);
}

InputManager::~InputManager(){
    t->join();
    write(0,NULL_CHAR,1);
    isDone.store(true);

}


char InputManager::getLastChar(){
    Lock<Mutex> lock(mutex);
    while(lastChars.size()==0) cond.wait(lock);
    char returnedChar = lastChars.front();
    lastChars.pop();
    return returnedChar;
}

void InputManager::putChar(char c){
    Lock<Mutex> lock(mutex);
    lastChars.push(c);
    cond.signal();
}