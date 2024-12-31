#ifndef _MELANIX_VIDEO_CONTROLLER
#define _MELANIX_VIDEO_CONTROLLER


#include "ofMain.h"
#include "ofxAlphaVideoPlayer.h"

class ofxMelanixVideoController{

	public:

        ~ofxMelanixVideoController();
		void setup(int _x, int _y, string videoFile);

		void update(float amt);
		void draw();
		void reset();

		float maxFrameRate;
		bool drawInfo;

        //ofVideoPlayer       videoPlayer;
        ofxAlphaVideoPlayer videoPlayer;

        int                 dX, dY;
        float               speed;
        float               maxspeedRec;
        float               maxspeed;
        string              videoFileName;

        bool                videoComplete;

};

#endif
