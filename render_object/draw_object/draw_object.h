#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <string>
using namespace std;

/* Is an abstraction that is used in order to have the directive to know what should be printed on screen */
class DrawObject{
    public:
        /* Is the constructor of this object */
        DrawObject(string object_string,string color):object_string(object_string),color(color){};
        /* Returns the string associated to this object that should be printed */
        string getObjectString() { return object_string; };
        /* Is the color of the string that has to be printed */
        string getObjectColor() { return color; };
    private:
        /* Is the string associate to this DrawObject */
        string object_string;
        /* Is the color associate to this DrawObject */
        string color;
};

#endif