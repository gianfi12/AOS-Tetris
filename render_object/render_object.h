#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
#include <atomic>

#include "terminal/input_manager.h"
#include "terminal/terminal.h"
#include "miosix.h"

using namespace std;

/* This represent the abstraction of the object that is actually responsible
of drawing on the screen based on its internal state, that is changed based on the
char captured by the InputManager. */
class RenderObject{
    public:
        /* Constructs an instance of this object. */ 
        RenderObject(InputManager *,Terminal *);
        /* Virtual destructor of this object since the class is abstract. */
        virtual ~RenderObject() {};
        /* Render method of the screen through the Terminal. */
        virtual RenderObject * drawFrame() = 0;
        /* Update the state of the RenderObject based on the last read char. */
        virtual void updateState(char c) = 0;
        /* is the InputManger actually recording the inputs coming from the user. */
        InputManager * inputManager;
    protected:
        /* Is the terminal that provids primitive to print on screen. */
        Terminal * terminal;
        /* It reads the character that are actually stored in a queue
        by the InputManager. */
        Thread *t;
};

#endif