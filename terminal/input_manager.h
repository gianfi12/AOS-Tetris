#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <atomic>
#include <queue>

#include "miosix.h"
#include "utility.h"

using namespace std;
using namespace miosix;

/* Is responsible of managing the input received from the usage, to store the received
char inside a queue that will be later on read by the actual ActiveRenderer that 
based on this will change its state. */
class InputManager{
    public:
        /* Constructs an instance of the InputManager. */
        InputManager();
        /* Returns an instance of the last char received from the user.
        NOTE: it is a blocking call. */
        char getLastChar();
        /* Put the provided char in the list with the last received char not already elaborated. */
        void putChar(char c);
        /* It destructs the instance of the InputManager. */
        ~InputManager();
        /* It says if the InputManager's thread has to be stopped. */ 
        atomic<bool> isDone;
    private:
        /* Is the thread on which the InputManager awaits the inputs of the user. */
        Thread *t;
        /* Is the queue(FIFO access) that contains the chars received from the user and not yet processed. */
        queue<char> lastChars;
        /* Is the mutex used to manage the access to the queue with the last chars. */
        Mutex mutex;
        /* Is the condition variable used to manage the access to the last chars queue. */
        ConditionVariable cond;
};


#endif