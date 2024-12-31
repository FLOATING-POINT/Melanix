#ifndef _TESTAPP
#define _TESTAPP

#include "ofMain.h"
#include "MSKinectWrapper.h"
#include "ofxKinectLimbPosChange.h"
#include "ofxMSKinectSkelDataReader.h"
#include "dataContainer.h"
#include "ofxMelanixVideoController.h"
#include "ofxMelanixBtn.h"
#include "ofxMelanixLimbControlBtn.h"
#include "ofxMelanixDiaphragmMoveDetector.h"
#include "ofxXmlSettings.h"
#include "ofxTween.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void resetAllVideos();
		void resetAllAnalysis();
		void resetAllVideosEvt(bool & hit);
		void startStopDataEvt(bool & hit);
        void frameLeftBtnEvt(bool & hit);
        void frameRightBtnEvt(bool & hit);
        void close(bool & hit);
        void changeFullScreen(bool & hit);


        //void setPosNegMoves(bool & hit);
        //void setPosMoves(bool & hit);
        //void setNegMoves(bool & hit);
        //void setAllMovesPositive(bool & hit);

        void setSettingsOne(bool & hit);
        void setSettingsTwo(bool & hit);
        void setSettingsThree(bool & hit);
        void setSettingsFour(bool & hit);

        void loadSettings(int num);

		void resetLimbPosChangeColors();
		void setLimbPosChangeColorsForInstallation();

        void fadeOutVideoParts();
        void fadeInVideoParts();

        void fadeOutSkeletonVideo();
        void fadeInSkeletonVideo();

        void fadeOutUnwindVideo();
        void fadeInUnwindVideo();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void saveSettings();

		int lastkey;

		float * skelPos1;
        float * skelPos2;

        vector< float >             easingValues;
        vector< float >             ampRightArm;
        vector< float >             ampLeftArm;
        vector< float >             ampRightLeg;
        vector< float >             ampLeftLeg;
        vector< float >             ampHead;
        vector< float >             ampDiaphragm;
        vector< float >             ampFinalTorso;

        float                       maxMovieSpeed;

        bool                        presentationMode;
        int                         presentationModeID;

        bool                        useSecondSkelForTorso;
        bool                        useDiaphragmForTorso;

        bool                        skelTwirlStarted;
        bool                        unwindStarted;

        bool                        useLiveData;
        ofxMSKinectSkelDataReader   *loader;
		MSKinectWrapper             MSkinect;

		int                         settingsID;
		int                         nSettings;

		ofxKinectLimbPosChange      armUpperLeft;
		ofxKinectLimbPosChange      armLowerLeft;

		ofxKinectLimbPosChange      armUpperRight;
		ofxKinectLimbPosChange      armLowerRight;

		ofxKinectLimbPosChange      legUpperLeft;
		ofxKinectLimbPosChange      legLowerLeft;

		ofxKinectLimbPosChange      legUpperRight;
		ofxKinectLimbPosChange      legLowerRight;

		ofxKinectLimbPosChange      diaphragmMove;

		ofxKinectLimbPosChange      finalTorsoMove;

		//-----------------------------------------

		ofxMelanixVideoController   leftArmVideo;
		ofxMelanixVideoController   leftLegVideo;
		ofxMelanixVideoController   rightArmVideo;
		ofxMelanixVideoController   rightLegVideo;

		ofxMelanixVideoController   torsoVideo;
		ofxMelanixVideoController   skeletonRotationVideo;
		ofxMelanixVideoController   unwindVideo;

		int                         videoPartsAlpha; // used to hide or show individual body parts
		ofxTween                    videoPartsAlphaTween;

        int                         skeletonVideoAlpha; // used to hide or show skeleton video
		ofxTween                    skeletonVideoAlphaTween;

		int                         unwindVideoAlpha; // used to hide or show skeleton video
		ofxTween                    unwindVideoAlphaTween;

        ofxEasingExpo               expoEase;
        ofxEasingCirc               circEase;
        ofxEasingCubic              cubicEase;
		//-----------------------------------------

		ofxMelanixBtn               settingsBtnOne;
		ofxMelanixBtn               settingsBtnTwo;
		ofxMelanixBtn               settingsBtnThree;
		ofxMelanixBtn               settingsBtnFour;

		ofxMelanixBtn               resetVideoBtn;
		ofxMelanixBtn               startDataBtn;
		ofxMelanixBtn               frameLeftBtn;
		ofxMelanixBtn               frameRightBtn;

		ofxMelanixBtn               posOnlyBtn;
		ofxMelanixBtn               negOnlyBtn;
		ofxMelanixBtn               posNegBtn;
		ofxMelanixBtn               allPosBtn;

		ofxMelanixBtn               closeBtn;

		//ofxMelanixBtn               screenModeBtn;
		bool                        appIsFullscreen;


		ofxMelanixLimbControlBtn    rightUpperLimbPntBtn;
		ofxMelanixLimbControlBtn    rightLowerLimbPntBtn;
		ofxMelanixLimbControlBtn    leftUpperLimbPntBtn;
		ofxMelanixLimbControlBtn    leftLowerLimbPntBtn;

		bool                        posMoves;
		bool                        negMoves;
		bool                        posNegMoves;
		bool                        allMovesPos;

		//-----------------------------------------

		ofxMelanixDiaphragmMoveDetector diaphragmMoveDetector;

		//-----------------------------------------

		ofxXmlSettings              XML;

	private:
		void drawDebug();
		bool kinectFailedToInit;


};
#endif
