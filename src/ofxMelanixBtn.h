#ifndef _OFXMELANIX_BTN
#define _OFXMELANIX_BTN

#include "ofMain.h"
#include "ofEvents.h"


class ofxMelanixBtn{

	public:
        ~ofxMelanixBtn();
		void setup(string _label, int _x, int _y, int _w, int _h);
		void update();
		void draw();
		void setPos(int _x, int _y, int _w, int _h);
		bool hitTest(int tx, int ty);
		void _mousePressed(ofMouseEventArgs &e);
		void _mouseMoved(ofMouseEventArgs &e);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		int bw, bh, bx, by;
		int padding;
		string label;

		int textCol;
		int textColActive;
		int borderCol;
		int bgCol;

		bool hit;
		bool active;

		ofEvent<bool> newHitEvent;

};

#endif
