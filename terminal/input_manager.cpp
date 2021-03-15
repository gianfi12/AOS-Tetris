#include "input_manager.h"

void readStdin(void * argv){
    InputManager * inputManager = (InputManager*)argv;
    while (!isDone)
    {
        char incomingChar = getchar();
        inputManager->managerIncomingChars(incomingChar);
    }
}

void InputManager::managerIncomingChars(char c){
    if(awaitSequenceForTerminal){
        if(c==charStartSequenceTerminal){
            readsForTerminal=true;
        }

        if(readsForTerminal){
            Lock<Mutex> lock(mutexTerminal);
            lastCharsForTerminal.push(c);
            condTerminal.signal();
        }else{
            putChar(c);
            if(c==ESCAPE || c==CTRLC){
                isDone.store(true); //Stop the main thread
            }
        }

        if(c==charFinishSequenceTerminal && readsForTerminal){
            readsForTerminal = false;   
            awaitSequenceForTerminal.store(false);  
        }
    }else{
        putChar(c);
        if(c==(char)ESCAPE || c==(char)CTRLC){
            isDone.store(true); //Stop the main thread
        }
    }
}

InputManager::InputManager():awaitSequenceForTerminal(false){
    t = Thread::create(readStdin ,2048,1,(void*)this,Thread::JOINABLE);
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

char InputManager::getLastCharForTerminal(){
    Lock<Mutex> lock(mutexTerminal);
    while(lastCharsForTerminal.size()==0) condTerminal.wait(lock);
    char returnedChar = lastCharsForTerminal.front();
    lastCharsForTerminal.pop();
    return returnedChar;
}


void InputManager::putChar(char c){
    Lock<Mutex> lock(mutex);
    lastChars.push(c);
    cond.signal();
}

void InputManager::startTerminalSequence(char startSequence, char endSequence){
    awaitSequenceForTerminal.store(true);
    charStartSequenceTerminal = startSequence;
    charFinishSequenceTerminal = endSequence;
}