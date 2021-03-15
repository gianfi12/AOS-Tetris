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
        /* It destructs the instance of the InputManager. */
        ~InputManager();

        /* Returns an instance of the last char received from the user.
        NOTE: it is a blocking call. */
        char getLastChar();

        /* Manage incoming chars received from the thread. */
        void managerIncomingChars(char);

        /* Sets the InputManager in a way in which the char in between the provided two are inserted in a special queue that is used by the terminal. 
        NOTE: Call this method before printing on the stdin. */
        void startTerminalSequence(char startSequence, char endSequence);
        /* Returns an instance of the last char received for the terminal.
        NOTE: it is a blocking call. */
        char getLastCharForTerminal();
    private:
        /* Is the thread on which the InputManager awaits the inputs of the user. */
        Thread *t;
        /* Is the queue(FIFO access) that contains the chars received from the user and not yet processed. */
        queue<char> lastChars;
        /* Is the mutex used to manage the access to the queue with the last chars. */
        Mutex mutex;
        /* Is the condition variable used to manage the access to the last chars queue. */
        ConditionVariable cond;
        /* Put the provided char in the list with the last received char not already elaborated. */
        void putChar(char c);
        
        /* Is the queue(FIFO access) that contains the chars received after interrogating the terminal with the ANSII escape sequences. */
        queue<char> lastCharsForTerminal;
        /* Indicates if we are going to await a sequence of chars that starts with charStartSequenceTerminal and finish with charFinishSequenceTerminal
        that are needed by the Terminal class. */
        atomic<bool> awaitSequenceForTerminal;
        /* Is true if we have actually received the first char we have to read of the terminal sequence and so all the next characters before the end of sequence will 
        go to the terminal reading. */
        bool readsForTerminal;
        /* Are the chars that starts the sequence of chars on which the terminal is waiting. */
        char charStartSequenceTerminal, charFinishSequenceTerminal;
        /* Is the mutex used to manage the access to the queue with the last chars. */
        Mutex mutexTerminal;
        /* Is the condition variable used to manage the access to the last chars queue. */
        ConditionVariable condTerminal;
    
};


#endif