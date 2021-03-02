#ifndef MENU_H
#define MENU_H
#include <string>

#include "render_object/render_object.h"

using namespace std;

/* This represents the Menu renderer, that based on the its internal state and the read
characters will print differently on the terminal.*/
class Menu: public RenderObject{
    public:
        /* Constructs an instance of this Menu. */
        Menu(InputManager *,Terminal *);
        /* Destroy an instace of the menu. */
        ~Menu();
        /* Draw the actual frame based on the actual state, bu using the primitive
        provided by Terminal. If the returned RenderObject is != null than we the actual one has finished its work
        and the returned one has to draw the next frame. */
        RenderObject * drawFrame();
    private:
        /* Is the file that contains a representation of the object to be printed on screen
        used by this class. */
        string objects_file_name="";
};

#endif