#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <string>
#include <map>

#include "render_object/render_object.h"
#include "render_object/menu/menu.h"

using namespace std;


/* This class represents the render object that is responsible for drawing frame during the game. */
class Gameover: public RenderObject{
    public:
        /* Constructs an instance of this Game. The integer is the score done by the user */
        Gameover(InputManager *,Terminal *,int);
        /* Destroy an instace of the Game. */
        ~Gameover();
        /* Draw the actual frame based on the actual state, bu using the primitive
        provided by Terminal. If the returned RenderObject is != null than we the actual one has finished its work
        and the returned one has to draw the next frame. */
        RenderObject * drawFrame();
        /* Update the state of the Menu based on the last read char. */
        bool updateState(char c);
    private:
        /* Is the score done by the user. */
        int score;
        /* Is the map that associated an id to the draw object. */
        map<string,DrawObject> objectMap;
        /* This method creates a draw_object that describes the menu screen */
        void gameover_draw_objects();
        /* It is true when the object has to finish its drawing work and pass the drawing to the next
        render object. */
        bool switchToNextRenderObject;
};

#endif