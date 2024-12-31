#ifndef _DIAPHRAGM_DETECTOR
#define _DIAPHRAGM_DETECTOR


#include "ofMain.h"

class ofxMelanixDiaphragmMoveDetector{

	public:
		void setup();
		bool update(ofVec3f _handLeftPnt, ofVec3f _handRightPnt, ofVec3f _headPnt, ofVec3f _waistPnt, ofVec3f _leftShoulderPnt, ofVec3f _rightShoulderPnt);
		void draw();

		bool moveDetected;
		int hTolerance; // horizontal tolerance

		ofVec3f handLeftPnt,handRightPnt;
		ofVec3f headPnt, waistPnt;
		ofVec3f leftShoulderPnt, rightShoulderPnt;

		int shoulderWidth;
		float shoulderWidthTolerance;


};

#endif
