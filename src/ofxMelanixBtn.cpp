#include "ofxMelanixBtn.h"

//--------------------------------------------------------------
void ofxMelanixBtn::setup(string _label, int _x, int _y, int _w, int _h){

    bw          = _w;
    bh          = _h;
    bx          = _x;
    by          = _y;
    label       = _label;
    padding     = 4;

    textCol     = 0x666666;
    textColActive = 0xff0000;
    borderCol   = 0x000000;
    bgCol       = 0x333333;

    hit         = true;
    active      = true;

    ofAddListener(ofEvents.mousePressed, this, &ofxMelanixBtn::_mousePressed);
    ofAddListener(ofEvents.mouseMoved, this, &ofxMelanixBtn::_mouseMoved);


}

//--------------------------------------------------------------
void ofxMelanixBtn::update(){



}

//--------------------------------------------------------------
void ofxMelanixBtn::draw(){

    ofSetHexColor(bgCol);
    ofFill();
    ofRect(bx+padding,by+padding,bw-(padding*2),bh-(padding*2));

    ofSetHexColor(borderCol);
    ofNoFill();
    ofRect(bx,by,bw,bh);

    if(!active) {
        ofSetHexColor(textCol);
    } else {
        ofSetHexColor(textColActive);
    }
    ofDrawBitmapString(label,bx+(padding*2),by+padding+(bh-12));

}
//----------------------------------------------------------------------------
void ofxMelanixBtn::setPos(int _x, int _y, int _w, int _h){
    bw          = _w;
    bh          = _h;
    bx          = _x;
    by          = _y;
}
//----------------------------------------------------------------------------
void ofxMelanixBtn::_mousePressed(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;

	if(hitTest(x, y)) ofNotifyEvent(newHitEvent,hit,this);

}
//----------------------------------------------------------------------------
void ofxMelanixBtn::_mouseMoved(ofMouseEventArgs &e) {

    if(hitTest(e.x, e.y)){
       //glutSetCursor(GLUT_CURSOR_NONE);
    } else {
        //glutSetCursor();
    }

}
//----------------------------------------------------------------------------
bool ofxMelanixBtn::hitTest(int tx, int ty) {

    bool hit = false;
    if(((tx > bx) && (tx < bx + bw) && (ty > by) && (ty < by + bh))){
       hit = true;

    }
    return hit;
}
//--------------------------------------------------------------
void ofxMelanixBtn::keyPressed(int key){

}

//--------------------------------------------------------------
void ofxMelanixBtn::keyReleased(int key){

}

//--------------------------------------------------------------
void ofxMelanixBtn::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofxMelanixBtn::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxMelanixBtn::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxMelanixBtn::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxMelanixBtn::windowResized(int w, int h){

}
ofxMelanixBtn::~ofxMelanixBtn(){
}

