#ifndef _OFXMELANIX_LIMB_CONTROL_BTN
#define _OFXMELANIX_LIMB_CONTROL_BTN

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxMelanixBtn.h"

class ofxMelanixLimbControlBtn{

	public:
        ~ofxMelanixLimbControlBtn();
		void setup(string _label, int _x, int _y, int _w, int _h);
		void update();
		void draw();
		bool hitTest(int tx, int ty);
		void _mousePressed(ofMouseEventArgs &e);
		void _mouseMoved(ofMouseEventArgs &e);

		void setUpperLimbActive(bool & hit);
		void setJointActive(bool & hit);
		void setLowerLimbActive(bool & hit);
		void setLimbAverageActive(bool & hit);
		void setLowerJointActive(bool & hit);
		void notifyChange();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		int             bw, bh, bx, by;
		int             padding;
		string          label;

		int             textCol;
		int             textColActive;
		int             borderCol;
		int             bgCol;

		bool            active;

        bool            upperLimbActive;
        bool            jointActive;
        bool            lowerLimbActive;
        bool            limbAverageActive;
        bool            lowerJointActive;

        int             btn1x, btn1y;
        int             btn2x, btn2y;
        int             btn3x, btn3y;
        int             btn4x, btn4y;
        int             btn5x, btn5y;

        ofxMelanixBtn   upperLimbBtn;
        ofxMelanixBtn   jointBtn;
        ofxMelanixBtn   lowerLimbBtn;
        ofxMelanixBtn   limbAverageBtn;
        ofxMelanixBtn   lowerJointBtn;

        ofEvent<bool> newHitEvent;

};

#endif
