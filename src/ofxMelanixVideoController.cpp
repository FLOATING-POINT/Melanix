#include "ofxMelanixVideoController.h"

//--------------------------------------------------------------
void ofxMelanixVideoController::setup(int _x, int _y, string videoFile){

    dX = _x;
    dY = _y;

    videoFileName = videoFile;
    videoPlayer.loadMovie(videoFile);
    videoPlayer.play();
    videoPlayer.setLoopState(OF_LOOP_NONE);

    videoPlayer.setSpeed(0.0f);
    maxFrameRate    = 100;

    drawInfo        = true;
    videoComplete   = false;

    maxspeed        = 0;

}
//--------------------------------------------------------------
void ofxMelanixVideoController::update(float amt){


    if(amt > maxspeed)      amt = maxspeed;
    if(amt > maxspeedRec)   maxspeedRec = amt;

    speed = amt;

    if(ofInRange(speed, -0.01, 0.01)) speed = 0.00f;
   // float amtN = (2 * amt - 1) * 5.0f;
   // if(amtN < 0.0f) amtN *=-1;
    //printf(" amt %f \n",amtN);
    if(!videoComplete) videoPlayer.setSpeed(speed);

    if(speed < -0.01f && videoPlayer.getCurrentFrame() == 0) {
        // dont loop the video backwards
    } else if(speed > 0.01f && videoPlayer.getCurrentFrame() == videoPlayer.getTotalNumFrames()) {
        // dont loop the video forwards
    }else {
        videoPlayer.idleMovie();
    }

    if(videoPlayer.getCurrentFrame() == videoPlayer.getTotalNumFrames() && !videoComplete) videoComplete = true;
}
//--------------------------------------------------------------
void ofxMelanixVideoController::draw(){


    videoPlayer.draw(dX, dY);

    if(drawInfo){
        ofPushMatrix();
        ofScale(2.0f,2.0f,1.0f);
       // ofSetHexColor(0xffffff);
            ofDrawBitmapString("Video :"+videoFileName+"\nCur Frame:"+ofToString(videoPlayer.getCurrentFrame())+" \nMovie speed: "+ofToString(speed)+" \nMax speed recorded: "+ofToString(maxspeedRec)+" \nMax frames: "+ofToString(videoPlayer.getTotalNumFrames()),dX-30, dY);
            if(videoComplete){
                ofDrawBitmapString("Video Complete: true",dX-30, dY+70);
            }else{
                ofDrawBitmapString("Video Complete: false",dX-30, dY+70);
            }
        ofPopMatrix();
    }

}
//--------------------------------------------------------------
void ofxMelanixVideoController::reset(){

    videoComplete = false;
    videoPlayer.setFrame(0);
}
//--------------------------------------------------------------
ofxMelanixVideoController::~ofxMelanixVideoController(){
    videoPlayer.close();
}
