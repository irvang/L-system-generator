#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(40);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    myMesh.setMode(OF_PRIMITIVE_LINES);
    myMesh.enableColors();
    myMesh.enableIndices();//from ofBook example
    myMesh.addVertex(turtMa.curCoords);//first vertex.Program will break without because mesh.getNumVertices - 2 in 'f'
    myMesh.addColor(color);
    
    cam.setDistance(20);
    
    //====MATRIX SETTINGS
    theta = 90;
    stepSize = .5;
    turtMa.theta = theta;
    
    
    //    myMesh.setMode(OF_PRIMITIVE_LINE_STRIP_ADJACENCY);
    //    myMesh.addVertex(turtMa.curCoords);
    cout << "mesh.numVertices = "<<myMesh.getNumVertices() << endl;
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofBackground(20);
    myMesh.addColor(color);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    infoTextFunction(bInfoText);
    
    cam.begin();
    
    ofRotateX(ofRadToDeg(0.5));
    ofRotateY(ofRadToDeg(-0.5));
    
    myMesh.draw();
    
    cam.end();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    myParser(key, turtMa, myMesh);
    
    switch(key){
        case 's':
            for(int i=0;i < lsys.currentLString.length(); ++i)
                myParser(lsys.currentLString[i], turtMa, myMesh);
            break;
        case 32:
            lsys.generate();
            cout << "------------------\n";
            break;
//        case 'x':
//            lsys.resetLSys();
//            break;
        case 'c':
            myMesh.clear();
            myMesh.addVertex(turtMa.curCoords);
            myMesh.addColor(color);
            turtMa = rotationMatrix(theta,stepSize);
            break;
        case 'r':
            //reset lString
            lsys = LSystem();
            myMesh.clear();
            
            turtMa = rotationMatrix(theta,stepSize);
            myMesh.addVertex(turtMa.curCoords);
            myMesh.addColor(color);
            break;
        case 'i':
            bInfoText = !bInfoText;
            break;
    }
    ////         << lsys.currentLString << '\n'
    //         << "length is " << lsys.currentLString.length() << '\n';
}

//--------------------------------------------------------------
void ofApp::myParser(const int & inKeyPressed, rotationMatrix & turtleMatrix, ofMesh & meshInFunction)
{
    switch(inKeyPressed)
    {
        case 'f': case 'h':
            turtleMatrix.move_f(stepSize);
            addVertex_n_color(meshInFunction, turtleMatrix.curCoords, color);
            addIndices(meshInFunction);
            break;
        case 'g':
            turtleMatrix.move_f(-stepSize);
            addVertex_n_color(meshInFunction, turtleMatrix.curCoords, color);
            addIndices(meshInFunction);
            break;
        case 'F':
            turtleMatrix.move_f(stepSize);
            addVertex_n_color(meshInFunction, turtleMatrix.curCoords, color);
            break;
        case 'G':
            turtleMatrix.move_f(-stepSize);
            addVertex_n_color(meshInFunction, turtleMatrix.curCoords, color);
            break;
        case '|':
            turtleMatrix.rotateOnU();
            break;
        case '-':
            turtleMatrix.rotateNegA();//left
            break;
        case '+':
            turtleMatrix.rotatePosA();//right
            break;
        case 'u':
            turtleMatrix.rotatePosB();//up
            break;
        case 'd':
            turtleMatrix.rotateNegB();//down
            break;
        case 'l'://roll left
            turtleMatrix.rollNegC();
            break;
        case '/'://roll right
            turtleMatrix.rollPosC();
            break;
        case '[':
            turtleMatrix.pushMat();
            break;
        case ']':
            turtleMatrix.popCoords();
            addVertex_n_color(meshInFunction, turtleMatrix.curCoords, color);
            turtleMatrix.popVectors();
            break;
            
            //        case '1': {meshInFunction.setMode(OF_PRIMITIVE_LINE_LOOP);} break; // did not make much sense
        case '1': meshInFunction.setMode(OF_PRIMITIVE_LINE_STRIP); break;
        case '2': meshInFunction.setMode(OF_PRIMITIVE_LINE_STRIP_ADJACENCY); break;
        case '3': meshInFunction.setMode(OF_PRIMITIVE_LINES); break;
        case '4': meshInFunction.setMode(OF_PRIMITIVE_LINES_ADJACENCY); break;
            //       case '6': {meshInFunction.setMode(OF_PRIMITIVE_PATCHES);} break; // never did anything
        case '5': meshInFunction.setMode(OF_PRIMITIVE_POINTS); break;
        case '6': meshInFunction.setMode(OF_PRIMITIVE_TRIANGLE_FAN); break;
        case '7': meshInFunction.setMode(OF_PRIMITIVE_TRIANGLE_STRIP); break;
        case '8': meshInFunction.setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY); break;
        case '9': meshInFunction.setMode(OF_PRIMITIVE_TRIANGLES); break;
            //           case '0': meshInFunction.setMode(OF_PRIMITIVE_TRIANGLES_ADJACENCY); break;
            //    case '0': !dupVertexMesh; break;
    }
}

//--------------------------------------------------------------
void ofApp::addVertex_n_color(ofMesh & _mesh, const ofVec3f & _coords, ofColor & _color)
{
    _mesh.addVertex(_coords);
    _mesh.addColor(_color);
}

//--------------------------------------------------------------

void ofApp::addIndices(ofMesh & _mesh)
{
    _mesh.addIndex(_mesh.getNumVertices() -2);
    _mesh.addIndex(_mesh.getNumVertices() -1);
}

//--------------------------------------------------------------
void ofApp::infoTextFunction (bool infoText) {
    if(infoText){
//        gui.draw();  /*gui2.draw();*/
    
        ofSetColor(255);
        
        stringstream ss;
        
        ss << "-Press space bar (2-3 times) and then press 's'"<<endl;
        ss << "-Length of string: "<< lsys.currentLString.length() << '\n' <<endl;
        
        ss <<"(s): Start - draw shape"<<endl;
        ss <<"(c): Clear" << endl;
        ss <<"(r): Reset: clear and resset to starting axiom"<<endl;
        
        
        ss <<"(space bar): Next generation " <<endl;
        ss <<"(0-10 ): Drawing modes" <<endl;
        ss <<"(i): Show/hide info" << '\n' <<endl;
        
        ss <<"-Cam - rotate: click and drag" <<endl;
        ss <<"-Cam - zoom: control + click and drag up or \n   down, or mouse scrollwheel" <<endl;
        ss <<"-Cam - \"move shape\": alt + click and drag" <<'\n' << endl;
       

    
        ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
        
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }
}
//--------------------------------------------------------------
void ofApp::exit()
{
    
}
