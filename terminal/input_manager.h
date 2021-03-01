#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <atomic>
#include <queue>

#include "miosix.h"

using namespace std;
using namespace miosix;

class InputManager{
    public:
        InputManager();
        char getLastChar();
    private:
        Thread *t;
        queue<char> lastChars;
        atomic<bool> isDone;
        void readStdout(void * argv);
};


#endif