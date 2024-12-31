#ifndef _ofxKinectLimbPosChange
#define _ofxKinectLimbPosChange


#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"
#include "ofxMelanixBtn.h"
#include "ofEvents.h"

class ofxKinectLimbPosChange {

	public:
        ~ofxKinectLimbPosChange();
		void setup(int id, string name);
		void update();
		void update(float x, float y, float z);
		void draw(int x, int y);
		void reset();

        void setPosNegMoves();
		void setPosNegMoves(bool & hit);
		void setPosMoves();
        void setPosMoves(bool & hit);
        void setAllMovesPositive();
        void setAllMovesPositive(bool & hit);
        void setBtnDisplay();

		void _mousePressed(ofMouseEventArgs &e);
        void _mouseReleased(ofMouseEventArgs &e);
        void hitTest(int tx, int ty);
        float getTotalChange();

		int _id;
		string _name;

		float minx, maxX, minY, maxY, minZ, maxZ;
		float changeX, changeY, changeZ;
		bool xActive, yActive, zActive;
		float curX, curY, curZ;
		float realX, realY, realZ;
		float prevX, prevY, prevZ;
		float easeAmt;
		float amplification;
		float displayAmplification;

		int _width, _height;
		int _x, _y;
		bool _mouseDown;

		bool firstRun;

		ofTrueTypeFont font;

		ofRectangle xRect;
		ofRectangle yRect;
		ofRectangle zRect;

		bool posMoves, negMoves, allPos, posNegMoves;

		int borderCol, textCol, labelCol, labelColActive, barCol, textColLabel;
		int bgColor;
		int padding;

        ofxMelanixBtn               posOnlyBtn;
		ofxMelanixBtn               posNegBtn;
		ofxMelanixBtn               allPosBtn;

		ofEvent<bool>               newHitEvent;

};

#endif
