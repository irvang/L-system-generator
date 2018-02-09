#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "ofMain.h"

//----------------------------------------------------------
class rotationMatrix : public ofMatrix4x4
{
public:
    rotationMatrix();
    rotationMatrix(float thetaC, float stepSizeC);
    ~rotationMatrix();

    ofVec3f rotateMatrix(float & thetaInsideMatrix, ofVec3f & fixedV, ofVec3f & multipliedV);
    void move_f(const float & stepSize);
    void rotateNegA();
    void rotatePosA();
    void rotateOnU();
    void rotateNegB();
    void rotatePosB();
    void rollPosC();
    void rollNegC();
    void pushMat();
    void popCoords();
    void popVectors();
    
    void printValues(const int & which);
    float theta = 0;
    float stepSize = 1;
    
    ofVec3f lookAtV,
            rightHandV,
            headingV,
            curCoords;//curCoords means 'current coordinates'
     
    // a vector of vectors of ofVec3f.
    // v2[n][m] = ofVec3f
    vector <vector <ofVec3f> > v2;
};

#endif // ROTATIONMATRIX_H
