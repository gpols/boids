#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //GUI
    gui.setup();
    //Toggles declared in ofApp.h
    //setup(sliderName, sliderValue, sliderMinimum, sliderMaximum, sliderWidth, sliderHeight)
    //sliderValue: start value
    
    // separation slider: Initial separation value set to 0.07, within the range [0, 1]
    gui.add(slider_separation.setup("separation", 0.07, 0, 1, 200, 20));

    // speedlimit slider: Initial speed limit set to 5, within the range [1, 20]
    gui.add(slider_speedlimit.setup("Speed Limit", 5, 1, 20, 200, 20));

    // cohesion slider: Initial cohesion value set to 0.3, within the range [0.5, 1]
    gui.add(slider_cohesion.setup("Cohesion", 0.3, 0.5, 1, 200, 20));

    // alignment slider: Initial alignment value set to 0.1, within the range [0, 1]
    gui.add(slider_alignment.setup("Alignment", 0.1, 0, 1, 200, 20));

    // checkdist slider: Initial check distance set to 35, within the range [10, 60]
    gui.add(slider_checkdist.setup("Check Distance", 35, 10, 60, 200, 20));

    // radius slider: Initial radius value set to 275, in the middle of the range [50, 500]
    gui.add(slider_radius.setup("Radius", 275, 50, 500, 200, 20));

    // bounce slider: Initial bounce value set to 0.5, within the range [0.1, 100]
    gui.add(slider_bounce.setup("Bounce", 0.5, 0.1, 100, 200, 20));

    
    // set 3d inviroment
    ofSetBackgroundColor(0);
    ofEnableNormalizedTexCoords();
    light.setPointLight();
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    light.setAmbientColor(ofFloatColor(0.3, 0.3, 0.3));
    light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,500);
    
    for(int i = 0; i < 100; i++){
           vec3 pos = vec3(ofRandom(-100,100), ofRandom(-100,100), ofRandom(-100,100));
           Boid b{pos,ofColor(0,0,255)};
           flock.push_back(b);
       }
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i = 0; i < flock.size(); i++){
           //Boid update prototype, play with these values to see what happens
       // void update(vector<Boid> _flock, float speedlimit, float separationFactor, float cohesionFactor, float alignmentFactor, float checkdist, float boundradius, float bouncespeed)
        
        // update to use gui
        flock[i].update(flock,slider_speedlimit,slider_separation,slider_cohesion,slider_alignment,slider_checkdist,slider_radius,slider_bounce);
       }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();// this wrap inside 3d
    cam.begin();

    ofEnableLighting();
    light.enable();

    //Do 3D drawing in here
    for(int i = 0; i < flock.size(); i++){
         flock[i].draw();
     }

    light.disable();
    ofDisableLighting();
    cam.end();
    ofDisableDepthTest(); // this wrap inside 3d
    
    // from here we can draw 2d
    // gui draw
    ofSetColor(255);
    gui.draw();
    
    
    // draw frame rate to screen
    ofSetColor(255);
    ofDrawBitmapString(to_string(ofGetFrameRate()), ofGetWidth()/2, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
