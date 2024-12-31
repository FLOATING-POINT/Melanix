#include "ofxMelanixDiaphragmMoveDetector.h"

//--------------------------------------------------------------
void ofxMelanixDiaphragmMoveDetector::setup(){

    moveDetected            = false;
    shoulderWidthTolerance  = 0.1;

}

//--------------------------------------------------------------
bool ofxMelanixDiaphragmMoveDetector::update(ofVec3f _handLeftPnt, ofVec3f _handRightPnt, ofVec3f _headPnt, ofVec3f _waistPnt, ofVec3f _leftShoulderPnt, ofVec3f _rightShoulderPnt){

    moveDetected        = false;

    shoulderWidth       = rightShoulderPnt.x - leftShoulderPnt.x;

   float shouldRange    = shoulderWidth*shoulderWidthTolerance;

    handLeftPnt         = _handLeftPnt;
    handRightPnt        = _handRightPnt;
    headPnt             = _headPnt;
    waistPnt            = _waistPnt;
    rightShoulderPnt    = _rightShoulderPnt;
    leftShoulderPnt     = _leftShoulderPnt;

    if(handLeftPnt.x > (leftShoulderPnt.x+shouldRange) && handRightPnt.x < (rightShoulderPnt.x-shouldRange)){

        if(handLeftPnt.y > headPnt.y && handRightPnt.y > headPnt.y ){
             moveDetected = true;
        }
    }

    return moveDetected;

}

//--------------------------------------------------------------
void ofxMelanixDiaphragmMoveDetector::draw(){

}

