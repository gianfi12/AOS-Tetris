#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <string>
using namespace std;

class DrawObject{
    public:
        DrawObject(string object_string,string color):object_string(object_string),color(color){};
        string getObjectString() { return object_string; };
        string getObjectColor() { return color; };
    private:
        string object_string;
        string color;
};

#endif