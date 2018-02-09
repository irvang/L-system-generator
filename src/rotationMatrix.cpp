#include "rotationMatrix.h"

//----------------------------------------------------------
rotationMatrix::rotationMatrix():
lookAtV {1.0,0.0,0.0},
headingV{0.0,1.0,0.0},
rightHandV {0.0,0.0,1.0},
theta {90},
stepSize  {1}
{
    
}
//----------------------------------------------------------
rotationMatrix::rotationMatrix(float thetaC, float stepSizeC):
lookAtV {1.0,0.0,0.0}, headingV {0.0,1.0,0.0}, rightHandV {0.0,0.0,1.0}, theta{thetaC}, stepSize {stepSizeC}
{
    
}
//----------------------------------------------------------
rotationMatrix::~rotationMatrix()
{
    
}
//----------------------------------------------------------
ofVec3f rotationMatrix::rotateMatrix(float & thetaInsideMatrix, ofVec3f & fixedV, ofVec3f & multipliedV)
{
    /* This function returns an ofVec3f which replaces the ofVec3fMultiplied. Two values are changed and one is kept the same. The one that is kept the same is the axis over which we rotate.
     For example:
     theta = (abs(theta));
     lookAtV = rotateMatrix(theta, headingV, lookAtV);
     rightHandV = lookAtV.getCrossed(headingV);
     //headingV remains the same
    
      -fixedV is the one that will remain the same
      -ofVec3fMultiplied is the vector that rotates
      -rightHandV vector rotates by "default," since it is a cross product of the other two vectors
    */
    
    //  theta is passed through the argument thetaInMatrix. That is how cosTheta and sinTheta are generated.
    float thetaRad = ofDegToRad(thetaInsideMatrix);//calculate once
    float cosTheta = cos(thetaRad);
    float sinTheta = sin(thetaRad);
    const float limits = 0.000000045;
    
    //  make cos & sin = 0 if they are less than... limits //This is to avoid 0 approximation error
    if ((cosTheta < limits) && (cosTheta > -limits)) cosTheta = 0.0;
    if((sinTheta < limits) && (sinTheta > -limits))sinTheta = 0.0;
    
    // now passed by reference 05/19/17
    float & xV = fixedV.x;
    float & yV = fixedV.y;
    float & zV = fixedV.z;
    
    ofMatrix4x4 rotateUHR;
    
    rotateUHR.set
    (
     //    roll left 'l' -theta, roll right '/' +theta // like rotate over x
     
     cosTheta + (xV * xV * (1 - (cosTheta))),//first row
     (xV * yV * (1-cosTheta)) - (zV * sinTheta),
     (xV * zV * (1-cosTheta)) + (yV * sinTheta),
     0.0,
     (yV * xV * (1-cosTheta)) + (zV * sinTheta), //second row
     cosTheta + (yV * yV * (1 - (cosTheta))),
     (yV * zV * (1-cosTheta)) - (xV * sinTheta),
     0.0,
     (zV * xV * (1-cosTheta)) - (yV * sinTheta), //third row
     (zV * yV * (1-cosTheta)) + (xV * sinTheta),
     cosTheta + (zV * zV * (1 - (cosTheta))),
     0.0,
     0.0, 0.0, 0.0, 1.0 // fourth row, it is discarded
     );
    
    //  in openFrameworks, for multiplication, the matrix values come after the vector, contrary to how it works in math, see documentation.
    
    //  returns the value of the new ofVec3f that is being altered.
    //  probably can be passed by reference
    return multipliedV * rotateUHR;
}
//----------------------------------------------------------
void rotationMatrix::move_f(const float & stepSize){
    // for forward, on invocation, use positive stepsize; for backward use negative
    curCoords += stepSize * lookAtV;
}

//----------------------------------------------------------
void rotationMatrix::rotateNegA()//left
{
    //first add and then do the calculations
    
    // take the absolute of theta and make it negative, in case theta is already negative
    theta = -(abs(theta));
    
    // headingV remains the same, and the output is the new lookAtV. the unchanged one is in the middle. the changed one is at both ends
    lookAtV = rotateMatrix(theta, headingV, lookAtV);
    
    lookAtV.normalize();
    headingV.normalize();
    
    // cross product of lookAtV and new headingV:  u x h
    rightHandV = lookAtV.getCrossed(headingV);
    // headingV remains the same
}
//----------------------------------------------------------
void rotationMatrix::rotatePosA()//right
{
    
    theta = (abs(theta));
    lookAtV = rotateMatrix(theta, headingV, lookAtV);
    
    lookAtV.normalize();
    headingV.normalize();
    
    rightHandV = lookAtV.getCrossed(headingV);
    // headingV remains the same
}
//----------------------------------------------------------
void rotationMatrix::rotateOnU()// rotates 180º around Ru (- +)
{
    float thetaRestore = theta; // store theta in thetaStore
    theta = 180;// theta becomes 180 to run the matrix
    //            theta = (abs(theta));
    
    lookAtV= rotateMatrix(theta, headingV, lookAtV);
    
    lookAtV.normalize();
    headingV.normalize();
    
    rightHandV = lookAtV.getCrossed(headingV);
    theta = thetaRestore; // restores theta to initial angle
}
//----------------------------------------------------------
void rotationMatrix::rotatePosB()   //  up
{
    theta = (abs(theta));
    lookAtV = rotateMatrix(theta, rightHandV, lookAtV);
    headingV = rotateMatrix(theta, rightHandV, headingV);
    
    lookAtV.normalize();
    headingV.normalize();
    // rightHandV remains unchanged
}
//----------------------------------------------------------
void rotationMatrix::rotateNegB()//down
{
    theta = -(abs(theta));
    lookAtV = rotateMatrix(theta, rightHandV, lookAtV);
    headingV = rotateMatrix(theta, rightHandV, headingV);
    
    lookAtV.normalize();
    headingV.normalize();
    // rightHandV remains unchanged
}
//----------------------------------------------------------
void rotationMatrix::rollNegC()//roll left
{
    theta = -(abs(theta));
    headingV = rotateMatrix(theta, lookAtV, headingV);
    
    lookAtV.normalize();
    headingV.normalize();
    
    rightHandV = lookAtV.getCrossed(headingV);
    // lookAtV remains the same
}
//----------------------------------------------------------
void rotationMatrix::rollPosC()//roll right
{
    theta = (abs(theta)); // take the absolute of theta, in case theta may be negative
    headingV = rotateMatrix(theta, lookAtV, headingV);
    
    lookAtV.normalize();
    headingV.normalize();
    
    rightHandV = lookAtV.getCrossed(headingV);
    // lookAtV remains the same
}
//----------------------------------------------------------

//----------------------------------------------------------
void rotationMatrix::pushMat()
{
    
    v2.push_back(vector <ofVec3f> {curCoords, lookAtV, headingV, rightHandV} );
    /* same as:
    const vector <ofVec3f> toStore = {curCoords, lookAtV, headingV, rightHandV};
    v2.push_back(toStore);
    */
}
//----------------------------------------------------------
void rotationMatrix::popCoords()
{
    if(v2.size())   // if(v2.size() != 0)
    {
        //first use the last one, then move by calling popVectors()
        curCoords = v2.back()[0];//curCoords = v2[N-1][0]
    }
}
//----------------------------------------------------------
void rotationMatrix::popVectors()
{
    if(v2.size())//if(v2.size() != 0)
    {
        lookAtV = v2.back()[1];     //same as v2[lastNumber][lookAt]
        headingV = v2.back()[2];    //heading
        rightHandV = v2.back()[3];  //rightHand
        v2.pop_back();
    }
}
//----------------------------------------------------------

void rotationMatrix::printValues(const int & which)
{
    cout << "\nprint #" << which << " curCoords = " << curCoords
    << ", lookAtV = " << lookAtV
    << ", headingV = " << headingV
    << ", rigtHandV = " << rightHandV;
}
