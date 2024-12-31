#include "ofxMelanixLimbControlBtn.h"

//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::setup(string _label, int _x, int _y, int _w, int _h){

    bw          = _w;
    bh          = _h;
    bx          = _x;
    by          = _y;
    label       = _label;
    padding     = 4;

    textCol             = 0x666666;
    textColActive       = 0xff0000;
    borderCol           = 0x000000;
    bgCol               = 0x333333;

    active              = false;

    upperLimbActive     = true;
    jointActive         = false;
    lowerLimbActive     = false;
    limbAverageActive   = false;
    lowerJointActive    = false;

    btn1x       = bx+padding+10;
    btn1y       = by+10;
    btn2x       = bx+padding+40;
    btn2y       = by+10;
    btn3x       = bx+padding+70;
    btn3y       = by+10;
    btn4x       = bx+padding+100;
    btn4y       = by+10;
    btn5x       = bx+padding+130;
    btn5y       = by+10;



    //-----------------------------------------------------------------------------------

    upperLimbBtn.setup("",btn1x,btn1y,18,18);
    ofAddListener(upperLimbBtn.newHitEvent,this,&ofxMelanixLimbControlBtn::setUpperLimbActive);

    jointBtn.setup("",btn2x,btn2y,18,18);
    ofAddListener(jointBtn.newHitEvent,this,&ofxMelanixLimbControlBtn::setJointActive);

    lowerLimbBtn.setup("",btn3x,btn3y,18,18);
    ofAddListener(lowerLimbBtn.newHitEvent,this,&ofxMelanixLimbControlBtn::setLowerLimbActive);

    limbAverageBtn.setup("",btn4x,btn4y,18,18);
    ofAddListener(limbAverageBtn.newHitEvent,this,&ofxMelanixLimbControlBtn::setLimbAverageActive);

    lowerJointBtn.setup("",btn5x,btn5y,18,18);
    ofAddListener(lowerJointBtn.newHitEvent,this,&ofxMelanixLimbControlBtn::setLowerJointActive);

    //-----------------------------------------------------------------------------------

    upperLimbBtn.bgCol      = 0x00ff00;
    jointBtn.bgCol          = 0x00ff00;
    lowerLimbBtn.bgCol      = 0x00ff00;
    limbAverageBtn.bgCol    = 0x00ff00;
    lowerJointBtn.bgCol     = 0x00ff00;

}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::update(){
}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::draw(){

    ofSetHexColor(bgCol);
    ofFill();
    ofRect(bx+padding,by+padding,bw-(padding*2),bh-(padding*2));

    ofSetHexColor(borderCol);
    ofNoFill();
    ofRect(bx,by,bw,bh);

    //-----------------------------------------------------------------
    /*upperLimbBtn.draw();
    jointBtn.draw();
    lowerLimbBtn.draw();
    limbAverageBtn.draw();
    lowerJointBtn.draw();*/

    if(!active) {
        ofSetHexColor(textCol);
    } else {
        ofSetHexColor(textColActive);
    }
    ofDrawBitmapString(label,bx+(padding*2),by+padding+(bh-12));

    int circleRadius        = 5;
    int circleRadiusActive  = 11;
    int activeCol           = 0x1e1e1e;

    //--------------------------------------------------
    ofEnableSmoothing();
    // white circle upper limb
    ofPushMatrix();
    ofTranslate(btn1x,btn1y);

        if(upperLimbActive){
            ofSetHexColor(activeCol);
            ofFill();
            ofCircle(circleRadius*2,circleRadius*2,circleRadiusActive);

        }
        ofSetHexColor(0xffffff);
        ofFill();
        ofCircle(circleRadius*2,circleRadius*2,circleRadius);

    ofPopMatrix();

    //--------------------------------------------------
    // red outline circle joint
    ofPushMatrix();
    ofTranslate(btn2x,btn2y);

        if(jointActive){
            ofSetHexColor(activeCol);
            ofFill();
            ofCircle(circleRadius*2,circleRadius*2,circleRadiusActive);

        }
        ofSetHexColor(0xff0000);
        ofNoFill();
        ofCircle(circleRadius*2,circleRadius*2,circleRadius);

    ofPopMatrix();

    //--------------------------------------------------
    // orange circle lower limb
    ofPushMatrix();
    ofTranslate(btn3x,btn3y);

        if(lowerLimbActive){
            ofSetHexColor(activeCol);
            ofFill();
            ofCircle(circleRadius*2,circleRadius*2,circleRadiusActive);

        }

        ofSetHexColor(0xFF8000);
        ofFill();
        ofCircle(circleRadius*2,circleRadius*2,circleRadius);

    ofPopMatrix();

    //--------------------------------------------------
    // grey outline circle whole limb average
    ofPushMatrix();
    ofTranslate(btn4x,btn4y);

        if(limbAverageActive){
            ofSetHexColor(activeCol);
            ofFill();
            ofCircle(circleRadius*2,circleRadius*2,circleRadiusActive);

        }

        ofSetHexColor(0xCCCCCC);
        ofNoFill();
        ofCircle(circleRadius*2,circleRadius*2,circleRadius);

    ofPopMatrix();

    //--------------------------------------------------
    // blue outline circle lower joint
    ofPushMatrix();
    ofTranslate(btn5x,btn5y);

        if(lowerJointActive){
            ofSetHexColor(activeCol);
            ofFill();
            ofCircle(circleRadius*2,circleRadius*2,circleRadiusActive);

        }

        ofSetHexColor(0x0000ff);
        ofNoFill();
        ofCircle(circleRadius*2,circleRadius*2,circleRadius);

    ofPopMatrix();


    //--------------------------------------------------
    ofDisableSmoothing();

}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::_mousePressed(ofMouseEventArgs &e) {

}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::_mouseMoved(ofMouseEventArgs &e) {

}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::setUpperLimbActive(bool & hit){
    upperLimbActive     = true;
    jointActive         = false;
    lowerLimbActive     = false;
    limbAverageActive   = false;
    lowerJointActive    = false;
    notifyChange();
}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::setJointActive(bool & hit){
    upperLimbActive     = false;
    jointActive         = true;
    lowerLimbActive     = false;
    limbAverageActive   = false;
    lowerJointActive    = false;
    notifyChange();
}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::setLowerLimbActive(bool & hit){
    upperLimbActive     = false;
    jointActive         = false;
    lowerLimbActive     = true;
    limbAverageActive   = false;
    lowerJointActive    = false;
    notifyChange();
}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::setLimbAverageActive(bool & hit){
    upperLimbActive     = false;
    jointActive         = false;
    lowerLimbActive     = false;
    limbAverageActive   = true;
    lowerJointActive    = false;
    notifyChange();
}
//----------------------------------------------------------------------------
void ofxMelanixLimbControlBtn::notifyChange(){
    bool hit = true;
    ofNotifyEvent(newHitEvent,hit,this);
}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::setLowerJointActive(bool & hit){
    upperLimbActive     = false;
    jointActive         = false;
    lowerLimbActive     = false;
    limbAverageActive   = false;
    lowerJointActive    = true;
}
//----------------------------------------------------------------------------
bool ofxMelanixLimbControlBtn::hitTest(int tx, int ty) {

    bool hit = false;
    if(((tx > bx) && (tx < bx + bw) && (ty > by) && (ty < by + bh))){
       hit = true;

    }
    return hit;
}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::keyPressed(int key){

}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::keyReleased(int key){

}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::mouseMoved(int x, int y ){

}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::mouseReleased(int x, int y, int button){

}
//--------------------------------------------------------------
void ofxMelanixLimbControlBtn::windowResized(int w, int h){

}
//--------------------------------------------------------------
ofxMelanixLimbControlBtn::~ofxMelanixLimbControlBtn(){

}


