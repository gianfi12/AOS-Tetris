#ifndef MENU_H
#define MENU_H
#include <string>
#include <map>

#include "render_object/render_object.h"
#include "render_object/game/game.h"
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
        bool updateState(char c);
    private:
        /* Is the map that associated an id to the draw object. */
        map<string,DrawObject> objectMap;
        /* This method creates a draw_object that describes the menu screen */
        void menu_draw_objects();
        /* It is true when the object has to finish its drawing work and pass the drawing to the next
        render object. */
        bool switchToNextRenderObject;
};

#endif