#include "LSystem.h"

//----------------------------------------------------------
LSystem::LSystem() :
startingString {"a"},
newGen {""},
currentLString {startingString}
{
    /// \brief Initializes variables for L-System

}
//----------------------------------------------------------
LSystem::~LSystem(){

}
//----------------------------------------------------------
void LSystem::generate() {

    //    if (nextGen){

    //  sets "neXt" to " " (empty)
    //  next needs to be here so it starts anew (empty, reset, nil) when space bar is pressed
    newGen = "";

    for (unsigned int i = 0; i < currentLString.length(); ++i) {

        switch (currentLString[i]) {

        //  newGen = newGen + production
        //  adds whichever case is selected to the end of the string "newGen"


            case 'a':
            newGen += "b-f+cfc+f-edfue-f+ddcfc+f+b//" ;
                break;
            case 'b':
                newGen += "adfucfbufueuu-f-eu|fub|fcufua//";
                break;
            case 'c':
                newGen += "|eu|fub-f+cufuaddfadfuc+f+bufue//";
                break;
            case 'e':
                newGen += "|cfb-f+b|fadfuaddfb-f+b|fc//";
                break;

            // if no substitution is found, whatever is on "currentLString" at i is passed back to "newGen"
        default: newGen += currentLString[i];
            break;
        }
    }
    //    }

    currentLString = newGen;
    cout << "\n----------------------\n"
         << "length = " << currentLString.length() << '\n';
}
//----------------------------------------------------------
void LSystem::resetLSys() {
    currentLString = startingString;
    cout << "string reset, currentLString = " << currentLString << '\n';
}
