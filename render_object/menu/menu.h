#ifndef MENU_H
#define MENU_H
#include <string>
#include <map>

#include "render_object/render_object.h"
#include "miosix.h"
#include "render_object/draw_object/draw_object.h"

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
        /* Update the state of the Menu based on the last read char. */
        void updateState(char c);
    private:
        /* Is the file that contains a representation of the object to be printed on screen
        used by this class. */
        string objects_file_name="";
        /* Is the map that associated an id to the draw object. */
        map<string,DrawObject> objectMap;
};

#endif