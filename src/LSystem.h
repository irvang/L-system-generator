#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "ofMain.h"

//  Prototype 1

class LSystem
{
    string startingString; //the axiom, will reset to this.
    string newGen;    //will store the development of the string.

public:

    LSystem();
    ~LSystem();

    string currentLString = startingString;

    void generate();//void. access to the string is by getting the variable. Seems more flexible
    void resetLSys();
};

#endif // LSYSTEM_H
