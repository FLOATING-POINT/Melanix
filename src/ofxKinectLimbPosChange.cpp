#include "ofxKinectLimbPosChange.h"

//--------------------------------------------------------------
void ofxKinectLimbPosChange::setup(int id, string name){

    padding     = 10;
    _width       = 350;
    _height      = 80 + (padding*6);

    easeAmt     = 0.1f;

    _id         = id;
    _name       = name;
    _mouseDown  = false;

    changeX     = 0;
    changeY     = 0;
    changeZ     = 0;

    borderCol       = 0x000000;
    textCol         = 0x666666;
    barCol          = 0xff0000;
    textColLabel    = 0xffffff;

    labelCol        = 0x666666;
    labelColActive  = 0xff0000;
    bgColor         = 0x323232;

    xActive         = false;
    yActive         = true;
    zActive         = false;

    posMoves        = false;
    negMoves        = false;
    allPos          = false;
    firstRun        = true;

    amplification           = 1.0f;
    displayAmplification    = 10.0f;

    posOnlyBtn.setup("Pos Moves",0, 80, 55, 25);

    ofAddListener(posOnlyBtn.newHitEvent,this,&ofxKinectLimbPosChange::setPosMoves);

    posNegBtn.setup("Pos & Neg ",60, 105, 60, 25);
    ofAddListener(posNegBtn.newHitEvent,this,&ofxKinectLimbPosChange::setPosNegMoves);

    allPosBtn.setup("All Moves Positive",120, 105, 60, 25);
    ofAddListener(allPosBtn.newHitEvent,this,&ofxKinectLimbPosChange::setAllMovesPositive);


	ofAddListener(ofEvents.mousePressed, this, &ofxKinectLimbPosChange::_mousePressed);



}
//--------------------------------------------------------------
void ofxKinectLimbPosChange::update(){
    xRect.x         = _x+padding;
    xRect.y         = _y+20+padding;
    xRect.width     = _width;
    xRect.height    = 20;

    yRect.x         = _x+padding;
    yRect.y         = _y+40+(padding*2);
    yRect.width     = _width;
    yRect.height    = 20;

    zRect.x         = _x+padding;
    zRect.y         = _y+60+(padding*3);
    zRect.width     = _width;
    zRect.height    = 20;
}
//--------------------------------------------------------------
void ofxKinectLimbPosChange::update(float x, float y, float z){

    realX = x;
    realY = y;
    realZ = z;

    if(!firstRun){

        curX += (x-curX)*easeAmt;
        curY += (y-curY)*easeAmt;
        curZ += (z-curZ)*easeAmt;

        changeX = (curX - prevX)*amplification;
        changeY = (curY - prevY)*amplification;
        changeZ = (curZ - prevZ)*amplification;

    } else {

        curX = x;
        curY = y;
        curZ = z;
    }

    firstRun = false;

    prevX = curX;
    prevY = curY;
    prevZ = curZ;

    if(ofInRange(changeX, -0.001f, 0.001f))  changeX = 0.00f;
    if(ofInRange(changeY, -0.001f, 0.001f))  changeY = 0.00f;
    if(ofInRange(changeZ, -0.001f, 0.001f))  changeZ = 0.00f;

    //--------------------------------------------------------

    if(negMoves){
        if(changeX>0.0f) changeX = 0.0f;
        if(changeY>0.0f) changeY = 0.0f;
        if(changeZ>0.0f) changeZ = 0.0f;
    }

    if(posMoves){
        if(changeX<0.0f) changeX = 0.0f;
        if(changeY<0.0f) changeY = 0.0f;
        if(changeZ<0.0f) changeZ = 0.0f;
    }

    if(allPos){
        if(changeX<0.0f) changeX *= -1;
        if(changeY<0.0f) changeY *= -1;
        if(changeZ<0.0f) changeZ *= -1;
    }

    update();

}

//--------------------------------------------------------------
void ofxKinectLimbPosChange::draw(int x, int y){

    _x = x;
    _y = y;


    //-----------------------------------------------------------------------

    ofFill();
    ofSetHexColor(bgColor);
    ofRect(x,y, _width+(padding*2), _height+(padding*2));

    ofNoFill();
    ofSetHexColor(borderCol);
    ofRect(x,y, _width+(padding*2), _height+(padding*2));

    ofSetHexColor(textCol);
    string title = _name+" Pos x:"+ofToString(realX,2)+" y:"+ofToString(realY,2)+" z:"+ofToString(realZ,2);
    ofDrawBitmapString(title,x+padding, y+(padding*2));

    // -----------------------------------------------------------------
    // x

    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(0,0,0,30);
    ofRect(xRect);

    ofSetHexColor(barCol);
    ofFill();

    if(xActive) ofRect(x+padding+(_width*.5), y+20+padding, ofClamp(changeX*displayAmplification, _width*-.5,_width*.5), 20);

    ofSetHexColor(borderCol);
    ofLine(x+padding+(_width*.5), y+20+padding, x+padding+(_width*.5), y+20+padding+20);

    ofNoFill();
    ofSetHexColor(borderCol);
    ofRect(x+padding, y+20+padding, _width, 20);

    // Label  and change values ---------------------------

    xActive ? ofSetHexColor(labelColActive) : ofSetHexColor(labelCol);
    ofDrawBitmapString("Change x: ",x+padding+5, y+35+padding);

    xActive ? ofSetHexColor(textColLabel) : ofSetHexColor(labelCol);
    ofDrawBitmapString(ofToString(changeX,2),x+padding+85, y+35+padding);

    // -----------------------------------------------------------------
    // y

    ofSetHexColor(barCol);
    ofFill();
    ofSetColor(0,0,0,30);
    ofRect(yRect);

    ofSetHexColor(barCol);
    if(yActive) ofRect(x+padding+(_width*.5), y+40+(padding*2), ofClamp(changeY*displayAmplification, _width*-.5,_width*.5), 20);


    ofSetHexColor(borderCol);
    ofLine(x+padding+(_width*.5), y+40+padding, x+padding+(_width*.5), y+40+padding+30);

    ofNoFill();
    ofSetHexColor(borderCol);
    ofRect(x+padding, y+40+(padding*2), _width, 20);

    // Label  and change values ---------------------------

    yActive ? ofSetHexColor(labelColActive) : ofSetHexColor(labelCol);
    ofDrawBitmapString("Change y: ",x+padding+5, y+65+padding);

    yActive ? ofSetHexColor(textColLabel) : ofSetHexColor(labelCol);
    ofDrawBitmapString(ofToString(changeY,2),x+padding+85, y+65+padding);

    // -----------------------------------------------------------------
    // z

    ofSetHexColor(barCol);
    ofFill();
    ofSetColor(0,0,0,30);
    ofRect(zRect);

    ofSetHexColor(barCol);
    if(zActive) ofRect(x+padding+(_width*.5), y+60+(padding*3), ofClamp(changeZ*displayAmplification, _width*-.5,_width*.5), 20);


    ofSetHexColor(borderCol);
    ofLine(x+padding+(_width*.5), y+60+padding, x+padding+(_width*.5), y+60+padding+40);

    ofNoFill();
    ofSetHexColor(borderCol);
    ofRect(x+padding, y+60+(padding*3), _width, 20);

    // z ---------------------------

    zActive ? ofSetHexColor(labelColActive) : ofSetHexColor(labelCol);
    ofDrawBitmapString("Change z: ",x+padding+5, y+95+padding);

    //ofSetHexColor(textColLabel);
    zActive ? ofSetHexColor(textColLabel) : ofSetHexColor(labelCol);
    ofDrawBitmapString(ofToString(changeZ,2),x+padding+85, y+95+padding);

    //-------------------------------------------------------------------------


    posOnlyBtn.setPos(x+padding, y+120, 90, 25);
	posNegBtn.setPos(x+padding+95, y+120, 90, 25);
	allPosBtn.setPos(x+padding+190, y+120, 160, 25);

    posOnlyBtn.draw();
    posNegBtn.draw();
    allPosBtn.draw();

    ofDisableAlphaBlending();


}
//----------------------------------------------------------------------------
float ofxKinectLimbPosChange::getTotalChange(){

    float change = 0.0f;

    if(xActive) change += changeX;
    if(yActive) change += changeY;
    if(zActive) change += changeZ;

    return change;

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::_mousePressed(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;

	hitTest(x, y);

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::hitTest(int tx, int ty) {

    if(((tx > xRect.x) && (tx < xRect.x + xRect.width) && (ty > xRect.y) && (ty < xRect.y + xRect.height))){
        xActive = !xActive;

    } else if (((tx > yRect.x) && (tx < yRect.x + yRect.width) && (ty > yRect.y) && (ty < yRect.y + yRect.height))){
        yActive = !yActive;

    } else if (((tx > zRect.x) && (tx < zRect.x + zRect.width) && (ty > zRect.y) && (ty < zRect.y + zRect.height))){
        zActive = !zActive;

    }
}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setPosNegMoves(){
    posMoves        = false;
    negMoves        = false;
    allPos          = false;
    posNegMoves     = true;

    posOnlyBtn.active = false;
    posNegBtn.active = true;
    allPosBtn.active = false;
}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setPosNegMoves(bool & hit){
    setPosNegMoves();

    bool change = true;
    ofNotifyEvent(newHitEvent,change,this);

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setPosMoves(){
    posMoves        = true;
    negMoves        = false;
    allPos          = false;
    posNegMoves     = false;

    posOnlyBtn.active = true;
    posNegBtn.active = false;
    allPosBtn.active = false;

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setPosMoves(bool & hit){
    setPosMoves();
    bool change = true;
    ofNotifyEvent(newHitEvent,change,this);
}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setAllMovesPositive(){
    posMoves        = false;
    negMoves        = false;
    allPos          = true;
    posNegMoves     = false;

    posOnlyBtn.active   = false;
    posNegBtn.active    = false;
    allPosBtn.active    = true;

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setAllMovesPositive(bool & hit){

    setAllMovesPositive();
    bool change = true;
    ofNotifyEvent(newHitEvent,change,this);
}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::_mouseReleased(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::reset(){

    firstRun    = true;

    changeX     = 0.0f;
    changeY     = 0.0f;
    changeZ     = 0.0f;

    prevX       = 0.0f;
    prevY       = 0.0f;
    prevZ       = 0.0f;

}
//----------------------------------------------------------------------------
void ofxKinectLimbPosChange::setBtnDisplay(){
}
//----------------------------------------------------------------------------

ofxKinectLimbPosChange::~ofxKinectLimbPosChange(){
}

