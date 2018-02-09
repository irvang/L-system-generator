#pragma once

#include "ofMain.h"
#include "LSystem.h"
//#include "turtle.h"
#include "rotationMatrix.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void myParser(const int & inKeyPressed, rotationMatrix & turtleMatrix, ofMesh & meshInFunction );
    void addVertex_n_color(ofMesh & _mesh, const ofVec3f & _coords, ofColor & _color);

    void addIndices(ofMesh & _mesh);
    void infoTextFunction (bool infoText);
    
    //idea is to initialize all objects at creation. There is generally a constructor for that. I should perhaps do that with my classes.
    ofEasyCam   cam;
    LSystem     lsys;
    rotationMatrix turtMa;//turtleMatrix, My Matrix

    ofMesh      myMesh;   
    ofColor     color {100, 255, 100, 100};//init

    int counter {0};
    float theta{0}, stepSize{0};//init only
    bool bInfoText{true};
};
