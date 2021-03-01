#include "input_manager.h"
#include <functional>

void threadfunc(void *argv)
{
}

void InputManager::readStdout(void * argv){

}

InputManager::InputManager():isDone(false){
    t = Thread::create(readStdout),2048,1,nullptr,Thread::JOINABLE);
};