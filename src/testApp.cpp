#include "testApp.h"
#include "ofxSimpleGuiToo.h"
//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(50,50,50);
    ofSetLogLevel( OF_LOG_VERBOSE);
    ofSetFrameRate(30);

    //---------------------------------------------

    useLiveData             = true;
    useSecondSkelForTorso   = false;
    useDiaphragmForTorso    = false;

    if(useLiveData){
        MSkinect.setup();
    } else {
        loader = new ofxMSKinectSkelDataReader("rec30fps_01_05_18-18-55-1.knct");
        loader->start();
    }


    presentationMode    = false;
    presentationModeID  = 0;

    skelTwirlStarted    = false;
    unwindStarted       = false;

    //---------------------------------------------

    diaphragmMoveDetector.setup();

    //---------------------------------------------

    nSettings       = 3;

    easingValues.resize(nSettings);
    ampDiaphragm.resize(nSettings);
    ampLeftArm.resize(nSettings);
    ampRightArm.resize(nSettings);
    ampLeftLeg.resize(nSettings);
    ampRightLeg.resize(nSettings);
    ampFinalTorso.resize(nSettings);


    for(int i = 0 ; i <= nSettings; i++){
        easingValues[i]     = 0.1f;

        ampRightArm[i]      = 10.0f;
        ampLeftArm[i]       = 10.0f;
        ampRightLeg[i]      = 10.0f;
        ampLeftLeg[i]       = 10.0f;
        ampDiaphragm[i]     = 10.0f;
        ampFinalTorso[i]     = 10.0f;
    }

	armLowerLeft.setup(1, "Arm Lower left");
	armLowerLeft.amplification = ampLeftArm[settingsID];

	armLowerRight.setup(1, "Arm Lower Right");
	armLowerRight.amplification = ampRightArm[settingsID];

	legLowerLeft.setup(1, "Leg Lower left");
	legLowerLeft.amplification = ampLeftLeg[settingsID];

	legLowerRight.setup(1, "Leg Lower Right");
	legLowerRight.amplification = ampRightLeg[settingsID];

    diaphragmMove.setup(1, "Diaphragm Move");
    diaphragmMove.amplification = ampDiaphragm[settingsID];

    finalTorsoMove.setup(1, "Final Torso Move");
    finalTorsoMove.amplification = ampFinalTorso[settingsID];

    //--------------------------------------------------------------

    leftArmVideo.setup(100,0,"movies/top_left.mov");
    leftLegVideo.setup(100,900,"movies/bottom_left.mov");
    rightArmVideo.setup(350,0,"movies/top_right.mov");
    rightLegVideo.setup(350,900,"movies/bottom_right.mov");
	torsoVideo.setup(200,350,"movies/torso_1.mov");

	skeletonRotationVideo.setup(100,0,"movies/skeletontwirl.mov");
	unwindVideo.setup(100,0,"movies/finalunwind.mov");

    //--------------------------------------------------------------

    int monitorX = ofGetWidth() - 400;

    resetVideoBtn.setup("Reset all",monitorX, 20, 180, 25);
    ofAddListener(resetVideoBtn.newHitEvent,this,&testApp::resetAllVideosEvt);

    startDataBtn.setup("Start/stop data ",monitorX+190, 20, 180,25);
    ofAddListener(startDataBtn.newHitEvent,this,&testApp::startStopDataEvt);

    frameLeftBtn.setup("<- Frame left ",monitorX, 45, 180, 25);
    ofAddListener(frameLeftBtn.newHitEvent,this,&testApp::frameLeftBtnEvt);

    frameRightBtn.setup("Frame right ->",monitorX+190, 45, 180,25);
    ofAddListener(frameRightBtn.newHitEvent,this,&testApp::frameRightBtnEvt);

    //--------------------------------------------------------------

    closeBtn.setup("CLOSE THE APP", 20, 80, 120,25);
    ofAddListener(closeBtn.newHitEvent,this,&testApp::close);

    appIsFullscreen = true;
    //screenModeBtn.setup("Exit Fullscreen", 20, 940, 260, 25);
    //ofAddListener(screenModeBtn.newHitEvent,this,&testApp::changeFullScreen);

    //--------------------------------------------------------------

    maxMovieSpeed           = 60;

    settingsID              = 0;

    gui.addPage("Settings page 1").setXMLName("_settings_0.xml");

    gui.addSlider("Torso x",                    torsoVideo.dX, 0.0, ofGetScreenWidth()).setSize(260,40);
    gui.addSlider("Torso y",                    torsoVideo.dY, 0.0, ofGetScreenHeight()).setSize(260,40);
    gui.addSlider("Easing of values 1",         easingValues[settingsID], 0.0, 1.0f).setSize(260,40);
    gui.addSlider("Amplication Diaghram 1",     ampDiaphragm[settingsID], -1.0, 80.0f).setSize(260,40);
    gui.addSlider("Amplication Left Arm 1",     ampLeftArm[settingsID], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Right Arm 1",    ampRightArm[settingsID], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Left Leg 1",     ampLeftLeg[settingsID], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Right Leg 1",    ampRightLeg[settingsID], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Final Torso 1",  ampFinalTorso[settingsID], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Max movie fps",              maxMovieSpeed, 30.0, 150.0f).setSize(260,40);
    gui.addToggle("Use 2nd Skel for Torso",     useSecondSkelForTorso).setSize(260,40);
    gui.addToggle("Use Diaphragm for Torso",    useDiaphragmForTorso).setSize(260,40);

    gui.addPage("Settings page 2").setXMLName("_settings_1.xml");
    gui.addSlider("Torso x",                    torsoVideo.dX, 0.0, ofGetScreenWidth()).setSize(260,40);
    gui.addSlider("Torso y",                    torsoVideo.dY, 0.0, ofGetScreenHeight()).setSize(260,40);
    gui.addSlider("Easing of values 2",         easingValues[1], 0.0, 1.0f).setSize(260,40);
    gui.addSlider("Amplication Diaghram 2",     ampDiaphragm[1], -1.0, 80.0f).setSize(260,40);
    gui.addSlider("Amplication Left Arm 2",     ampLeftArm[1], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Right Arm 2",    ampRightArm[1], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Left Leg 2",     ampLeftLeg[1], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Right Leg 2",    ampRightLeg[1], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Final Torso 2",  ampFinalTorso[1], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Max movie fps",              maxMovieSpeed, 30.0, 150.0f).setSize(260,40);
    gui.addToggle("Use 2nd Skel for Torso",     useSecondSkelForTorso).setSize(260,40);
    gui.addToggle("Use Diaphragm for Torso",    useDiaphragmForTorso).setSize(260,40);

    gui.addPage("Settings page 3").setXMLName("_settings_2.xml");
    gui.addSlider("Torso x",                    torsoVideo.dX, 0.0, ofGetScreenWidth()).setSize(260,40);
    gui.addSlider("Torso y",                    torsoVideo.dY, 0.0, ofGetScreenHeight()).setSize(260,40);
    gui.addSlider("Easing of values 3",         easingValues[2], 0.0, 1.0f).setSize(260,40);
    gui.addSlider("Amplication Diaghram 3",     ampDiaphragm[2], -1.0, 80.0f).setSize(260,40);
    gui.addSlider("Amplication Left Arm 3",     ampLeftArm[2], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Right Arm 3",    ampRightArm[2], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Left Leg 3",     ampLeftLeg[2], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Right Leg 3",    ampRightLeg[2], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Final Torso 3",  ampFinalTorso[2], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Max movie fps",              maxMovieSpeed, 30.0, 150.0f).setSize(260,40);
    gui.addToggle("Use 2nd Skel for Torso",     useSecondSkelForTorso).setSize(260,40);
    gui.addToggle("Use Diaphragm for Torso",    useDiaphragmForTorso).setSize(260,40);


    gui.addPage("Settings page 4").setXMLName("_settings_3.xml");
    gui.addSlider("Torso x",                    torsoVideo.dX, 0.0, ofGetScreenWidth()).setSize(260,40);
    gui.addSlider("Torso y",                    torsoVideo.dY, 0.0, ofGetScreenHeight()).setSize(260,40);
    gui.addSlider("Easing of values 4",         easingValues[3], 0.0, 1.0f).setSize(260,40);
    gui.addSlider("Amplication Diaghram 4",     ampDiaphragm[3], -1.0, 80.0f).setSize(260,40);
    gui.addSlider("Amplication Left Arm 4",     ampLeftArm[3], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Right Arm 4",    ampRightArm[3], -1.0, 5.0f).setSize(260,40);
    gui.addSlider("Amplication Left Leg 4",     ampLeftLeg[3], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Right Leg 4",    ampRightLeg[3], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Amplication Final Torso 4",  ampFinalTorso[3], -1.0, 10.0f).setSize(260,40);
    gui.addSlider("Max movie fps",              maxMovieSpeed, 30.0, 150.0f).setSize(260,40);
    gui.addToggle("Use 2nd Skel for Torso",     useSecondSkelForTorso).setSize(260,40);
    gui.addToggle("Use Diaphragm for Torso",    useDiaphragmForTorso).setSize(260,40);


    settingsBtnOne.setup("Settings One", 20, 710, 260,25);
    ofAddListener(settingsBtnOne.newHitEvent,this,&testApp::setSettingsOne);
    settingsBtnOne.active   = true;

    settingsBtnTwo.setup("Settings Two", 20, 740, 260,25);
    ofAddListener(settingsBtnTwo.newHitEvent,this,&testApp::setSettingsTwo);
    settingsBtnTwo.active   = false;

    settingsBtnThree.setup("Settings Three", 20, 770, 260,25);
    ofAddListener(settingsBtnThree.newHitEvent,this,&testApp::setSettingsThree);
    settingsBtnThree.active = false;

    settingsBtnFour.setup("Settings Four", 20, 800, 260,25);
    ofAddListener(settingsBtnFour.newHitEvent,this,&testApp::setSettingsFour);
    settingsBtnFour.active  = false;

    //--------------------------------------------------------------

    rightUpperLimbPntBtn.setup("Analysis: Right Upper Limb", 20, 830, 260, 54);
    rightLowerLimbPntBtn.setup("Analysis: Right Lower Limb", 20, 890, 260, 54);
    leftUpperLimbPntBtn.setup("Analysis: Left Upper Limb", 20, 950, 260, 54);
    leftLowerLimbPntBtn.setup("Analysis: left Lower Limb", 20, 1010, 260, 54);

    gui.loadFromXML();

    gui.setPage("Settings page 1");
    gui.show();

    loadSettings(settingsID);


    //-----------------------------------------------------------------------------------------
    videoPartsAlpha     = 255;
    skeletonVideoAlpha  = 0;
    unwindVideoAlpha    = 0;

    //ofToggleFullscreen();

}

//--------------------------------------------------------------
void testApp::update(){

    //screenModeBtn.update();

    if(useLiveData){

        MSkinect.update();

        //------------------------------------------------------------------------------------------------------------
        // LEFT LIMB

        if(leftUpperLimbPntBtn.upperLimbActive){
            armLowerLeft.update(MSkinect.leftUpperArmPntS1.x, MSkinect.leftUpperArmPntS1.y, MSkinect.leftUpperArmPntS1.z);

        } else if(leftUpperLimbPntBtn.jointActive){
            armLowerLeft.update(MSkinect.getLeftElbowPoint(0).x, MSkinect.getLeftElbowPoint(0).y, MSkinect.getLeftElbowPoint(0).z);

        } else if(leftUpperLimbPntBtn.lowerLimbActive){
            armLowerLeft.update(MSkinect.leftLowerArmPntS1.x, MSkinect.leftLowerArmPntS1.y, MSkinect.leftLowerArmPntS1.z);

        } else if(leftUpperLimbPntBtn.limbAverageActive){
            armLowerLeft.update(MSkinect.leftArmPntS1.x, MSkinect.leftArmPntS1.y, MSkinect.leftArmPntS1.z);

        } else if(leftUpperLimbPntBtn.lowerJointActive){
            armLowerLeft.update(MSkinect.leftLowerArmPntS1.x, MSkinect.leftLowerArmPntS1.y, MSkinect.leftLowerArmPntS1.z);

        }

        //------------------------------------------------------------------------------------------------------------
        // RIGHT LIMB

        if(rightUpperLimbPntBtn.upperLimbActive){
            armLowerRight.update(MSkinect.rightUpperArmPntS1.x, MSkinect.rightUpperArmPntS1.y, MSkinect.rightUpperArmPntS1.z);

        } else if(rightUpperLimbPntBtn.jointActive){

            armLowerRight.update(MSkinect.getRightElbowPoint(0).x,MSkinect.getRightElbowPoint(0).y,MSkinect.getRightElbowPoint(0).z);

        } else if(rightUpperLimbPntBtn.lowerLimbActive){
            armLowerRight.update(MSkinect.rightLowerArmPntS1.x, MSkinect.rightLowerArmPntS1.y, MSkinect.rightLowerArmPntS1.z);

        } else if(rightUpperLimbPntBtn.limbAverageActive){
            armLowerRight.update(MSkinect.rightArmPntS1.x, MSkinect.rightArmPntS1.y, MSkinect.rightArmPntS1.z);

        } else if(rightUpperLimbPntBtn.lowerJointActive){
            armLowerRight.update(MSkinect.rightLowerArmPntS1.x, MSkinect.rightLowerArmPntS1.y, MSkinect.rightLowerArmPntS1.z);
        }

        //------------------------------------------------------------------------------------------------------------
        // LEFT LEG

        if(leftLowerLimbPntBtn.upperLimbActive){
            legLowerLeft.update(MSkinect.leftUpperLegPntS1.x, MSkinect.leftUpperLegPntS1.y, MSkinect.leftUpperLegPntS1.z);

        } else if(leftLowerLimbPntBtn.jointActive){

            legLowerLeft.update(MSkinect.getLeftKneePoint(0).x,MSkinect.getLeftKneePoint(0).y,MSkinect.getLeftKneePoint(0).z);

        } else if(leftLowerLimbPntBtn.lowerLimbActive){
            legLowerLeft.update(MSkinect.leftLowerlegPntS1.x, MSkinect.leftLowerlegPntS1.y, MSkinect.leftLowerlegPntS1.z);

        } else if(leftLowerLimbPntBtn.limbAverageActive){
            legLowerLeft.update(MSkinect.leftLegPntS1.x, MSkinect.leftLegPntS1.y, MSkinect.leftLegPntS1.z);

        } else if(leftLowerLimbPntBtn.lowerJointActive){
            legLowerLeft.update(MSkinect.leftLowerlegPntS1.x, MSkinect.leftLowerlegPntS1.y, MSkinect.leftLowerlegPntS1.z);
        }

        //------------------------------------------------------------------------------------------------------------
        // RIGHT LEG

        if(rightLowerLimbPntBtn.upperLimbActive){
            legLowerRight.update(MSkinect.rightUpperLegPntS1.x, MSkinect.rightUpperLegPntS1.y, MSkinect.rightUpperLegPntS1.z);

        } else if(rightLowerLimbPntBtn.jointActive){
            legLowerRight.update(MSkinect.getRightKneePoint(0).x,MSkinect.getRightKneePoint(0).y,MSkinect.getRightKneePoint(0).z);

        } else if(rightLowerLimbPntBtn.lowerLimbActive){
            legLowerRight.update(MSkinect.rightLowerlegPntS1.x, MSkinect.rightLowerlegPntS1.y, MSkinect.rightLowerlegPntS1.z);

        } else if(rightLowerLimbPntBtn.limbAverageActive){
            legLowerRight.update(MSkinect.rightLegPntS1.x, MSkinect.rightLegPntS1.y, MSkinect.rightLegPntS1.z);

        } else if(rightLowerLimbPntBtn.lowerJointActive){
            legLowerRight.update(MSkinect.rightLowerlegPntS1.x, MSkinect.rightLowerlegPntS1.y, MSkinect.rightLowerlegPntS1.z);
        }

        //---------------------------------------------------------------------

        if(leftArmVideo.videoComplete &&
            leftLegVideo.videoComplete &&
            rightArmVideo.videoComplete &&
            rightLegVideo.videoComplete &&
            torsoVideo.videoComplete){

            finalTorsoMove.update(MSkinect.getGroinPoint(0).x ,MSkinect.getGroinPoint(0).y,MSkinect.getGroinPoint(0).z);
        } else {
            finalTorsoMove.reset();
        }
        finalTorsoMove.update();


            //---------------------------------------------------------------------
            // if using performers the torso move is used

            if(useSecondSkelForTorso){
                if(useDiaphragmForTorso){
                    diaphragmMoveDetector.update(MSkinect.getLeftHandPoint(1),MSkinect.getRightHandPoint(1),MSkinect.getHeadPoint(1),MSkinect.getStomachPoint(1),MSkinect.getLeftShoulderPoint(1),MSkinect.getRightShoulderPoint(1));
                    if(diaphragmMoveDetector.moveDetected) {
                        diaphragmMove.update(MSkinect.getRightHandPoint(1).x,MSkinect.getRightHandPoint(1).y,MSkinect.getRightHandPoint(1).z);
                    }else {
                        diaphragmMove.reset();
                    }
                } else {
                    diaphragmMove.update(MSkinect.getHeadPoint(1).x,MSkinect.getHeadPoint(1).y,MSkinect.getHeadPoint(1).z);
                }

            } else {

                if(useDiaphragmForTorso){
                    diaphragmMoveDetector.update(MSkinect.getLeftHandPoint(0),MSkinect.getRightHandPoint(0),MSkinect.getHeadPoint(0),MSkinect.getStomachPoint(0),MSkinect.getLeftShoulderPoint(0),MSkinect.getRightShoulderPoint(0));
                    if(diaphragmMoveDetector.moveDetected){
                        diaphragmMove.update(MSkinect.getRightHandPoint(0).x,MSkinect.getRightHandPoint(0).y,MSkinect.getRightHandPoint(0).z);
                    }else {
                        diaphragmMove.reset();
                    }
                } else {
                    printf("diaphragmMove \n");
                    diaphragmMove.update(MSkinect.getHeadPoint(0).x,MSkinect.getHeadPoint(0).y,MSkinect.getHeadPoint(0).z);
                }
            }

        diaphragmMove.update();

    } else {

        loader->readTo();
        loader->updatePnts();

        skelPos1 = loader->getPoints(0);
        skelPos2 = loader->getPoints(1);

        //-------------------------------------------------------------------------------------
        // points for skel 1
        //------------------------------------------------------------------------------------------------------------
        // LEFT LIMB

        if(leftUpperLimbPntBtn.upperLimbActive){
            armLowerLeft.update(loader->leftUpperArmPntS1.x, loader->leftUpperArmPntS1.y, loader->leftUpperArmPntS1.z);

        } else if(leftUpperLimbPntBtn.jointActive){
            armLowerLeft.update(loader->getLeftElbowPoint(0).x, loader->getLeftElbowPoint(0).y, loader->getLeftElbowPoint(0).z);

        } else if(leftUpperLimbPntBtn.lowerLimbActive){
            armLowerLeft.update(loader->leftLowerArmPntS1.x, loader->leftLowerArmPntS1.y, loader->leftLowerArmPntS1.z);

        } else if(leftUpperLimbPntBtn.limbAverageActive){
            armLowerLeft.update(loader->leftArmPntS1.x, loader->leftArmPntS1.y, loader->leftArmPntS1.z);

        } else if(leftUpperLimbPntBtn.lowerJointActive){
            armLowerLeft.update(loader->leftLowerArmPntS1.x, loader->leftLowerArmPntS1.y, loader->leftLowerArmPntS1.z);

        }

        //------------------------------------------------------------------------------------------------------------
        // RIGHT LIMB

        if(rightUpperLimbPntBtn.upperLimbActive){
            armLowerRight.update(loader->rightUpperArmPntS1.x, loader->rightUpperArmPntS1.y, loader->rightUpperArmPntS1.z);

        } else if(rightUpperLimbPntBtn.jointActive){

            armLowerRight.update(loader->getRightElbowPoint(0).x,loader->getRightElbowPoint(0).y,loader->getRightElbowPoint(0).z);

        } else if(rightUpperLimbPntBtn.lowerLimbActive){
            armLowerRight.update(loader->rightLowerArmPntS1.x, loader->rightLowerArmPntS1.y, loader->rightLowerArmPntS1.z);

        } else if(rightUpperLimbPntBtn.limbAverageActive){
            armLowerRight.update(loader->rightArmPntS1.x, loader->rightArmPntS1.y, loader->rightArmPntS1.z);

        } else if(rightUpperLimbPntBtn.lowerJointActive){
            armLowerRight.update(loader->rightLowerArmPntS1.x, loader->rightLowerArmPntS1.y, loader->rightLowerArmPntS1.z);
        }

        //------------------------------------------------------------------------------------------------------------
        // LEFT LEG

        if(leftLowerLimbPntBtn.upperLimbActive){
            legLowerLeft.update(loader->leftUpperLegPntS1.x, loader->leftUpperLegPntS1.y, loader->leftUpperLegPntS1.z);

        } else if(leftLowerLimbPntBtn.jointActive){

            legLowerLeft.update(loader->getLeftKneePoint(0).x,loader->getLeftKneePoint(0).y,loader->getLeftKneePoint(0).z);

        } else if(leftLowerLimbPntBtn.lowerLimbActive){
            legLowerLeft.update(loader->leftLowerlegPntS1.x, loader->leftLowerlegPntS1.y, loader->leftLowerlegPntS1.z);

        } else if(leftLowerLimbPntBtn.limbAverageActive){
            legLowerLeft.update(loader->leftLegPntS1.x, loader->leftLegPntS1.y, loader->leftLegPntS1.z);

        } else if(leftLowerLimbPntBtn.lowerJointActive){
            legLowerLeft.update(loader->leftLowerlegPntS1.x, loader->leftLowerlegPntS1.y, loader->leftLowerlegPntS1.z);
        }

        //------------------------------------------------------------------------------------------------------------
        // RIGHT LEG

        if(rightLowerLimbPntBtn.upperLimbActive){
            legLowerRight.update(loader->rightUpperLegPntS1.x, loader->rightUpperLegPntS1.y, loader->rightUpperLegPntS1.z);

        } else if(rightLowerLimbPntBtn.jointActive){
            legLowerRight.update(loader->getRightKneePoint(0).x,loader->getRightKneePoint(0).y,loader->getRightKneePoint(0).z);

        } else if(rightLowerLimbPntBtn.lowerLimbActive){
            legLowerRight.update(loader->rightLowerlegPntS1.x, loader->rightLowerlegPntS1.y, loader->rightLowerlegPntS1.z);

        } else if(rightLowerLimbPntBtn.limbAverageActive){
            legLowerRight.update(loader->rightLegPntS1.x, loader->rightLegPntS1.y, loader->rightLegPntS1.z);

        } else if(rightLowerLimbPntBtn.lowerJointActive){
            legLowerRight.update(loader->rightLowerlegPntS1.x, loader->rightLowerlegPntS1.y, loader->rightLowerlegPntS1.z);
        }

        if(leftArmVideo.videoComplete &&
            leftLegVideo.videoComplete &&
            rightArmVideo.videoComplete &&
            rightLegVideo.videoComplete &&
            torsoVideo.videoComplete){

                finalTorsoMove.update(loader->getGroinPoint(0).x,loader->getGroinPoint(0).y,loader->getGroinPoint(0).z);
       } else {
                finalTorsoMove.reset();
       }
         finalTorsoMove.update();

        //------------------------------------------------------------------------------------

         if(useSecondSkelForTorso){
             // Use skeleton two
             if(useDiaphragmForTorso){

                diaphragmMoveDetector.update(loader->getLeftHandPoint(1),loader->getRightHandPoint(1),loader->getHeadPoint(1),loader->getStomachPoint(1),loader->getLeftShoulderPoint(1),loader->getRightShoulderPoint(1));
                if(diaphragmMoveDetector.moveDetected){
                    diaphragmMove.update(loader->getRightHandPoint(1).x,loader->getRightHandPoint(1).y,loader->getRightHandPoint(1).z);
                } else {
                    diaphragmMove.reset();
                }
             } else {
                    diaphragmMove.update(loader->getHeadPoint(1).x,loader->getHeadPoint(1).y,loader->getHeadPoint(1).z);
             }
         } else {
             // Use skeleton one
              if(useDiaphragmForTorso){

                diaphragmMoveDetector.update(loader->getLeftHandPoint(0),loader->getRightHandPoint(0),loader->getHeadPoint(0),loader->getStomachPoint(0),loader->getLeftShoulderPoint(0),loader->getRightShoulderPoint(0));
                if(diaphragmMoveDetector.moveDetected){
                    diaphragmMove.update(loader->getRightHandPoint(0).x,loader->getRightHandPoint(0).y,loader->getRightHandPoint(0).z);

                } else {
                    diaphragmMove.reset();
                }
              } else {
                    diaphragmMove.update(loader->getHeadPoint(0).x,loader->getHeadPoint(0).y,loader->getHeadPoint(0).z);
             }
        }
        diaphragmMove.update();

    }

    if(!useLiveData) ofSetWindowTitle("Key:"+ofToString(lastkey)+" loader cur frame: "+ofToString(loader->currentFrame)+" of "+ofToString(loader->maxFrame));

    //----------------------------------------------------------------------------------------

    if(ampLeftArm[settingsID] == 0.0f)       ampLeftArm[settingsID]     = 1.0f;
	if(ampRightArm[settingsID] == 0.0f)     ampRightArm[settingsID]     = 1.0f;
	if(ampLeftLeg[settingsID] == 0.0f)      ampLeftLeg[settingsID]      = 1.0f;
	if(ampRightLeg[settingsID] == 0.0f)     ampRightLeg[settingsID]     = 1.0f;
    if(ampDiaphragm[settingsID] == 0.0f)    ampDiaphragm[settingsID]    = 1.0f;
    if(ampFinalTorso[settingsID] == 0.0f)   ampFinalTorso[settingsID]   = 1.0f;

	armLowerLeft.amplification      = ampLeftArm[settingsID];
	armLowerRight.amplification     = ampRightArm[settingsID];
	legLowerLeft.amplification      = ampLeftLeg[settingsID];
	legLowerRight.amplification     = ampRightLeg[settingsID];
    diaphragmMove.amplification     = ampDiaphragm[settingsID];
    finalTorsoMove.amplification    = ampFinalTorso[settingsID];

    armLowerLeft.easeAmt        = 1-easingValues[settingsID];
	armLowerRight.easeAmt       = 1-easingValues[settingsID];
	legLowerLeft.easeAmt        = 1-easingValues[settingsID];
	legLowerRight.easeAmt       = 1-easingValues[settingsID];
    diaphragmMove.easeAmt       = 1-easingValues[settingsID];
    finalTorsoMove.easeAmt      = 1-easingValues[settingsID];

    leftArmVideo.maxspeed               = maxMovieSpeed;
    leftLegVideo.maxspeed               = maxMovieSpeed;
    rightArmVideo.maxspeed              = maxMovieSpeed;
    rightLegVideo.maxspeed              = maxMovieSpeed;
    torsoVideo.maxspeed                 = maxMovieSpeed;
    skeletonRotationVideo.maxspeed      = maxMovieSpeed;
    unwindVideo.maxspeed                = maxMovieSpeed;

    //----------------------------------------------------------------------------------------
    //
    // for presentation mode 4 the limbs are flipped - camera behind the performer - who is looking away
    //

    if(presentationMode == 4){

        rightArmVideo.update(armLowerLeft.getTotalChange());
        rightLegVideo.update(legLowerLeft.getTotalChange());

        leftArmVideo.update(armLowerRight.getTotalChange());
        leftLegVideo.update(legLowerRight.getTotalChange());

    } else {

        leftArmVideo.update(armLowerLeft.getTotalChange());
        leftLegVideo.update(legLowerLeft.getTotalChange());

        rightArmVideo.update(armLowerRight.getTotalChange());
        rightLegVideo.update(legLowerRight.getTotalChange());
    }

    if(useDiaphragmForTorso){
        if(diaphragmMoveDetector.moveDetected){
            torsoVideo.update(diaphragmMove.getTotalChange());
        } else {
            torsoVideo.update(0.0f);
        }
    } else {
        torsoVideo.update(diaphragmMove.getTotalChange());
    }


    if(leftArmVideo.videoComplete   &&
       leftLegVideo.videoComplete   &&
       rightArmVideo.videoComplete  &&
       rightLegVideo.videoComplete  &&
       torsoVideo.videoComplete     &&
       !skeletonRotationVideo.videoComplete
       ){
            // trigger the skeleton video
            if(!skelTwirlStarted) fadeInSkeletonVideo();
            if(!skeletonRotationVideo.videoComplete) skeletonRotationVideo.update(finalTorsoMove.getTotalChange());

    } else if(

        leftArmVideo.videoComplete   &&
        leftLegVideo.videoComplete   &&
        rightArmVideo.videoComplete  &&
        rightLegVideo.videoComplete  &&
        torsoVideo.videoComplete     &&
        skeletonRotationVideo.videoComplete
        ){
            //trigger the unwind video
            skeletonRotationVideo.update(0.0f);

            unwindVideo.update(1.0f);
            if(!unwindStarted) fadeInUnwindVideo();
            if(unwindVideo.videoComplete) resetAllVideos();

    } else {
        unwindVideo.update(0.0f);
        skeletonRotationVideo.update(0.0f);
    }


    //-----------------------------------------------------------------------------------------

    if(videoPartsAlphaTween.isRunning())    videoPartsAlpha     = int(videoPartsAlphaTween.update());
    if(skeletonVideoAlphaTween.isRunning()) skeletonVideoAlpha  = int(skeletonVideoAlphaTween.update());
    if(unwindVideoAlphaTween.isRunning())   unwindVideoAlpha    = int(unwindVideoAlphaTween.update());


}
//--------------------------------------------------------------
void testApp::draw(){

    ofEnableAlphaBlending();


    if(presentationModeID == 0){

        ofBackground(50,50,50);

        if(useLiveData){

            MSkinect.drawVideoDepthData = true;
            MSkinect.draw(310,105, 650,105);

            ofEnableSmoothing();
            ofPushMatrix();
            ofTranslate(200,500);

                MSkinect.drawLines(0);
                MSkinect.drawLines(1);

                MSkinect.drawCirclePoints(0);
                MSkinect.drawCirclePoints(1);

                MSkinect.drawLimbPoints(0);
                MSkinect.drawLimbPoints(1);

            ofPopMatrix();
            ofDisableSmoothing();

        } else {

            ofNoFill();

            ofEnableSmoothing();
            ofPushMatrix();
            ofTranslate(200,500);


                // Lines
                loader->drawLines(0);
                loader->drawLines(1);

                // Points

                //loader->drawPoints(0);
                loader->drawCirclePoints(0);
                loader->drawCirclePoints(1);

                // limbs

                loader->drawLimbPoints(0);
                loader->drawLimbPoints(1);

            ofPopMatrix();
            ofDisableSmoothing();
        }
    }

    //-----------------------------------------------------------------------------------------
    // videos


    if(presentationModeID == 0){

        ofPushMatrix();
        ofTranslate(950,50,0);
        ofScale(0.5,0.5,1.0);

            if(videoPartsAlpha > 0){
                ofSetColor(255,255,255,videoPartsAlpha);
                rightArmVideo.draw();
                rightLegVideo.draw();

                leftArmVideo.draw();
                leftLegVideo.draw();

                torsoVideo.draw();
            }
            if(skelTwirlStarted){
                ofSetColor(255,255,255,skeletonVideoAlpha);
                skeletonRotationVideo.draw();
            }
            if(unwindStarted){
                ofSetColor(255,255,255,unwindVideoAlpha);
                unwindVideo.draw();
            }

        ofPopMatrix();

    } else if(presentationModeID == 1 ){

        //ofDrawBitmapString("FR:"+ofToString(ofGetFrameRate()),10,10);
        ofPushMatrix();
        ofBackgroundHex(0x000000);
        ofTranslate(60,(ofGetScreenHeight()*.5) +375,0); // movies are 500 wide, 1800 deep
        ofRotateZ(-90);


            if(videoPartsAlpha > 0){
                ofSetColor(255,255,255,videoPartsAlpha);
                leftArmVideo.draw();
                leftLegVideo.draw();

                rightArmVideo.draw();
                rightLegVideo.draw();

                torsoVideo.draw();
            }

            if(skelTwirlStarted){
                ofSetColor(255,255,255,skeletonVideoAlpha);
                skeletonRotationVideo.draw();
            }
            if(unwindStarted){
                ofSetColor(255,255,255,unwindVideoAlpha);
                unwindVideo.draw();
            }

        ofPopMatrix();

    } else if(presentationModeID == 2 || presentationModeID == 4){

        ofBackgroundHex(0x000000);

        ofPushMatrix();
        float displayScale = 0.65;
        ofTranslate((ofGetScreenWidth()-(1000*displayScale))*.5,(ofGetScreenHeight()-(1800*displayScale))*.5,0);
        ofScale(displayScale,displayScale,1.0);


            if(videoPartsAlpha > 0){

                ofSetColor(255,255,255,videoPartsAlpha);
                rightArmVideo.draw();
                rightLegVideo.draw();

                leftArmVideo.draw();
                leftLegVideo.draw();

                torsoVideo.draw();
            }

             if(skelTwirlStarted){
                ofSetColor(255,255,255,skeletonVideoAlpha);
                skeletonRotationVideo.draw();
             }
             if(unwindStarted){
                ofSetColor(255,255,255,unwindVideoAlpha);
                unwindVideo.draw();
             }

        ofPopMatrix();

    } else if(presentationModeID == 3 ){

        ofBackgroundHex(0x000000);

        // ----------------------------------------------------
        // Kinect stuff
        MSkinect.drawVideoDepthData = false;
        MSkinect.draw(310,105, 650,105);

        ofEnableSmoothing();
        ofPushMatrix();
        ofTranslate(200,200);
        ofScale(1.2,1.2,1.0);

            MSkinect.drawLines(0);
            MSkinect.drawLines(1);

            MSkinect.drawCirclePoints(0);
            MSkinect.drawCirclePoints(1);

            MSkinect.drawLimbPoints(0);
            MSkinect.drawLimbPoints(1);

        ofPopMatrix();
        ofDisableSmoothing();

        // ----------------------------------------------------

        ofPushMatrix();
        ofTranslate(950,0,0);
        ofScale(0.6,0.6,1.0);

            if(videoPartsAlpha > 0){

                ofSetColor(255,255,255,videoPartsAlpha);
                rightArmVideo.draw();
                rightLegVideo.draw();
                leftArmVideo.draw();
                leftLegVideo.draw();
                torsoVideo.draw();
            }
            if(skelTwirlStarted){
                ofSetColor(255,255,255,skeletonVideoAlpha);
                skeletonRotationVideo.draw();
            }
            if(unwindStarted){
                ofSetColor(255,255,255,unwindVideoAlpha);
                unwindVideo.draw();
            }

        ofPopMatrix();

        // ----------------------------------

        int monitorX = ofGetWidth() - 400;

        armLowerLeft.draw(monitorX,30);
        armLowerRight.draw(monitorX,195);
        legLowerLeft.draw(monitorX,360);
        legLowerRight.draw(monitorX,525);
        diaphragmMove.draw(monitorX,690);
        finalTorsoMove.draw(monitorX,855);


    }

    ofDisableAlphaBlending();
    //----------------------------------------------------------------------------------------
    // DEBUG INFO

    if(presentationModeID == 0){

        // ----------------------------------

        int monitorX = ofGetWidth() - 400;

        armLowerLeft.draw(monitorX,80);
        armLowerRight.draw(monitorX,245);
        legLowerLeft.draw(monitorX,410);
        legLowerRight.draw(monitorX,575);
        diaphragmMove.draw(monitorX,740);
        finalTorsoMove.draw(monitorX,905);

        // ----------------------------------
        gui.draw();

        closeBtn.draw();

        settingsBtnOne.draw();
        settingsBtnTwo.draw();
        settingsBtnThree.draw();
        settingsBtnFour.draw();

        resetVideoBtn.draw();
        startDataBtn.draw();
        frameLeftBtn.draw();
        frameRightBtn.draw();

        // ----------------------------------

        rightUpperLimbPntBtn.draw();
        rightLowerLimbPntBtn.draw();
        leftUpperLimbPntBtn.draw();
        leftLowerLimbPntBtn.draw();

        // ----------------------------------



        if(diaphragmMoveDetector.moveDetected && !useLiveData){
            ofSetHexColor(0xff0000);
            ofDrawBitmapString("DIAPHRAGM MOVE\n  DETECTED "+ofToString(diaphragmMove.getTotalChange()), loader->getHeadPoint(0).x+10+ 150, loader->getHeadPoint(0).y - 50 + 500);
        } else if(!useLiveData){
            ofSetHexColor(0xffffff);
            ofDrawBitmapString("DIAPHRAGM MOVE\n NOT DETECTED "+ofToString(diaphragmMove.getTotalChange()), loader->getHeadPoint(0).x+10+ 150, loader->getHeadPoint(0).y - 50 + 500);
        }

        if(diaphragmMoveDetector.moveDetected && useLiveData){
            ofSetHexColor(0xff0000);
            ofDrawBitmapString("DIAPHRAGM MOVE\n  DETECTED "+ofToString(diaphragmMove.getTotalChange()), MSkinect.getHeadPoint(0).x+10+ 150, MSkinect.getHeadPoint(0).y - 50 + 500);
        } else if(!diaphragmMoveDetector.moveDetected && useLiveData){
            ofSetHexColor(0xffffff);
            ofDrawBitmapString("DIAPHRAGM MOVE\n NOT DETECTED ", 400,  500);
        } else if(useLiveData){
            ofSetHexColor(0xffffff);
            ofDrawBitmapString("DIAPHRAGM MOVE\n NOT DETECTED "+ofToString(diaphragmMove.getTotalChange()), MSkinect.getHeadPoint(0).x+10+ 150, MSkinect.getHeadPoint(0).y - 50 + 500);
        }

         //ofDrawBitmapString("SKEL ALPHA "+ofToString(skeletonVideoAlpha)+" UNWIND ALPHA "+ofToString(unwindVideoAlpha),1000 , 20);

        if(skeletonRotationVideo.videoComplete){
            ofDrawBitmapString("skeletonRotationVideo COMPLETE ",1000 , 20);
        }else{
            ofDrawBitmapString("skeletonRotationVideo NOT COMPLETE ",1000 , 20);
        }
    }




}

//--------------------------------------------------------------
void testApp::resetAllAnalysis(){

    armUpperLeft.reset();
    armLowerLeft.reset();

    armUpperRight.reset();
    armLowerRight.reset();

    legUpperLeft.reset();
    legLowerLeft.reset();

    legUpperRight.reset();
    legLowerRight.reset();

    diaphragmMove.reset();
    finalTorsoMove.reset();

}
//--------------------------------------------------------------
void testApp::resetAllVideos(){

    skelTwirlStarted    = false;
    unwindStarted       = false;

    leftArmVideo.reset();
    leftLegVideo.reset();
    rightArmVideo.reset();
    rightLegVideo.reset();
    torsoVideo.reset();
    unwindVideo.reset();
    skeletonRotationVideo.reset();

    videoPartsAlpha     = 255;
    skeletonVideoAlpha  = 0;
    unwindVideoAlpha    = 0;

    resetAllAnalysis();

    //fadeOutUnwindVideo();

}
//--------------------------------------------------------------
void testApp::resetAllVideosEvt(bool & hit){
	resetAllVideos();
	if(!useLiveData) {
        loader->start();
    }

}
//--------------------------------------------------------------
void testApp::startStopDataEvt(bool & hit){

    if(!useLiveData){
        if(loader->isStarted) {
            loader->stop();
        } else if(!loader->isStarted) {
            loader->resume();
        }
    }
}
//--------------------------------------------------------------
void testApp::frameLeftBtnEvt(bool & hit){
    if(loader->isStarted) loader->stop();
    if(!useLiveData) loader->prevFrame();
}
//--------------------------------------------------------------
void testApp::frameRightBtnEvt(bool & hit){
    if(loader->isStarted) loader->stop();
    if(!useLiveData) loader->nextFrame();
}
//--------------------------------------------------------------
void testApp::setSettingsOne(bool & hit){

    saveSettings();

    settingsID = 0;
    loadSettings(settingsID);

    gui.setPage("Settings page 1");
    gui.show();

    settingsBtnOne.active   = true;
    settingsBtnTwo.active   = false;
    settingsBtnThree.active = false;
    settingsBtnFour.active  = false;

    resetAllVideos();
}
//--------------------------------------------------------------
void testApp::setSettingsTwo(bool & hit){

    saveSettings();

    settingsID = 1;
    loadSettings(settingsID);
    gui.setPage("Settings page 2");
    gui.show();

    settingsBtnOne.active   = false;
    settingsBtnTwo.active   = true;
    settingsBtnThree.active = false;
    settingsBtnFour.active  = false;

    resetAllVideos();

}
//--------------------------------------------------------------
void testApp::setSettingsThree(bool & hit){

    saveSettings();

    settingsID = 2;
    loadSettings(settingsID);
    gui.setPage("Settings page 3");
    gui.show();

    settingsBtnOne.active   = false;
    settingsBtnTwo.active   = false;
    settingsBtnThree.active = true;
    settingsBtnFour.active  = false;

    resetAllVideos();

}
//--------------------------------------------------------------
void testApp::setSettingsFour(bool & hit){

    saveSettings();

    settingsID = 3;
    loadSettings(settingsID);
    gui.setPage("Settings page 4");
    gui.show();

    settingsBtnOne.active   = false;
    settingsBtnTwo.active   = false;
    settingsBtnThree.active = false;
    settingsBtnFour.active  = true;

    resetAllVideos();

}
//--------------------------------------------------------------
void testApp::close(bool & hit){
    ofExit(1);
}
//--------------------------------------------------------------
void testApp::changeFullScreen(bool & hit){

    printf("changeFullScreen \n");


    appIsFullscreen = !appIsFullscreen;

    if(appIsFullscreen){
       // screenModeBtn.label = "Exit Fullscreen";
    }else{
       // screenModeBtn.label = "Go Fullscreen";
    }

    //

    //ofToggleFullscreen();

}
//--------------------------------------------------------------
void testApp::saveSettings(){

    printf("saveSettings \n");

    XML.pushTag("SETTINGS",0);

        armLowerRight.posMoves ?        XML.setValue("RIGHT-ARM-POS-MOVES-ONLY",1,0) : XML.setValue("RIGHT-ARM-POS-MOVES-ONLY",0,0);
        armLowerRight.posNegMoves ?     XML.setValue("RIGHT-ARM-POS-NEG-MOVES",1,0) : XML.setValue("RIGHT-ARM-POS-NEG-MOVES",0,0);
        armLowerRight.allPos ?          XML.setValue("RIGHT-ARM-ALL-MOVES-POS",1,0) : XML.setValue("RIGHT-ARM-ALL-MOVES-POS",0,0);


        armLowerLeft.posMoves ?        XML.setValue("LEFT-ARM-POS-MOVES-ONLY",1,0) : XML.setValue("LEFT-ARM-POS-MOVES-ONLY",0,0);
        armLowerLeft.posNegMoves ?     XML.setValue("LEFT-ARM-POS-NEG-MOVES",1,0) : XML.setValue("LEFT-ARM-POS-NEG-MOVES",0,0);
        armLowerLeft.allPos ?          XML.setValue("LEFT-ARM-ALL-MOVES-POS",1,0) : XML.setValue("LEFT-ARM-ALL-MOVES-POS",0,0);

        legLowerLeft.posMoves ?        XML.setValue("LEFT-LEG-POS-MOVES-ONLY",1,0) : XML.setValue("LEFT-LEG-POS-MOVES-ONLY",0,0);
        legLowerLeft.posNegMoves ?     XML.setValue("LEFT-LEG-POS-NEG-MOVES",1,0) : XML.setValue("LEFT-LEG-POS-NEG-MOVES",0,0);
        legLowerLeft.allPos ?          XML.setValue("LEFT-LEG-ALL-MOVES-POS",1,0) : XML.setValue("LEFT-LEG-ALL-MOVES-POS",0,0);

        legLowerRight.posMoves ?        XML.setValue("RIGHT-LEG-POS-MOVES-ONLY",1,0) : XML.setValue("RIGHT-LEG-POS-MOVES-ONLY",0,0);
        legLowerRight.posNegMoves ?     XML.setValue("RIGHT-LEG-POS-NEG-MOVES",1,0) : XML.setValue("RIGHT-LEG-POS-NEG-MOVES",0,0);
        legLowerRight.allPos ?          XML.setValue("RIGHT-LEG-ALL-MOVES-POS",1,0) : XML.setValue("RIGHT-LEG-ALL-MOVES-POS",0,0);

        diaphragmMove.posMoves ?        XML.setValue("DIAPHRAGM-POS-MOVES-ONLY",1,0) : XML.setValue("DIAPHRAGM-POS-MOVES-ONLY",0,0);
        diaphragmMove.posNegMoves ?     XML.setValue("DIAPHRAGM-POS-NEG-MOVES",1,0) : XML.setValue("DIAPHRAGM-POS-NEG-MOVES",0,0);
        diaphragmMove.allPos ?          XML.setValue("DIAPHRAGM-ALL-MOVES-POS",1,0) : XML.setValue("DIAPHRAGM-ALL-MOVES-POS",0,0);



        finalTorsoMove.posMoves ?        XML.setValue("FINALTORSO-POS-MOVES-ONLY",1,0) : XML.setValue("FINALTORSO-POS-MOVES-ONLY",0,0);
        finalTorsoMove.posNegMoves ?     XML.setValue("FINALTORSO-POS-NEG-MOVES",1,0) : XML.setValue("FINALTORSO-POS-NEG-MOVES",0,0);
        finalTorsoMove.allPos ?          XML.setValue("FINALTORSO-ALL-MOVES-POS",1,0) : XML.setValue("FINALTORSO-ALL-MOVES-POS",0,0);


        diaphragmMove.xActive ? XML.setValue("diaphragmx",1,0) : XML.setValue("diaphragmx",0,0);
        diaphragmMove.yActive ? XML.setValue("diaphragmy",1,0) : XML.setValue("diaphragmy",0,0);
        diaphragmMove.zActive ? XML.setValue("diaphragmz",1,0) : XML.setValue("diaphragmz",0,0);

        finalTorsoMove.xActive ? XML.setValue("finaltorsox",1,0) : XML.setValue("finaltorsox",0,0);
        finalTorsoMove.yActive ? XML.setValue("finaltorsoy",1,0) : XML.setValue("finaltorsoy",0,0);
        finalTorsoMove.zActive ? XML.setValue("finaltorsoz",1,0) : XML.setValue("finaltorsoz",0,0);


        armLowerRight.xActive ? XML.setValue("armLowerRightx",1,0) : XML.setValue("armLowerRightx",0,0);
        armLowerRight.yActive ? XML.setValue("armLowerRighty",1,0) : XML.setValue("armLowerRighty",0,0);
        armLowerRight.zActive ? XML.setValue("armLowerRightz",1,0) : XML.setValue("armLowerRightz",0,0);

        legLowerRight.xActive ? XML.setValue("legLowerRightx",1,0) : XML.setValue("legLowerRightx",0,0);
        legLowerRight.yActive ? XML.setValue("legLowerRighty",1,0) : XML.setValue("legLowerRighty",0,0);
        legLowerRight.zActive ? XML.setValue("legLowerRightz",1,0) : XML.setValue("legLowerRightz",0,0);

        armLowerLeft.xActive ? XML.setValue("armLowerLeftx",1,0) : XML.setValue("armLowerLeftx",0,0);
        armLowerLeft.yActive ? XML.setValue("armLowerLefty",1,0) : XML.setValue("armLowerLefty",0,0);
        armLowerLeft.zActive ? XML.setValue("armLowerLeftz",1,0) : XML.setValue("armLowerLeftz",0,0);

        legLowerLeft.xActive ? XML.setValue("legLowerLeftx",1,0) : XML.setValue("legLowerLeftx",0,0);
        legLowerLeft.yActive ? XML.setValue("legLowerLefty",1,0) : XML.setValue("legLowerLefty",0,0);
        legLowerLeft.zActive ? XML.setValue("legLowerLeftz",1,0) : XML.setValue("legLowerLeftz",0,0);


        //------------------------------------------------------------------------------------------------

        rightUpperLimbPntBtn.upperLimbActive    ? XML.setValue("rightArmUpperLimbActive",1,0)   : XML.setValue("rightArmUpperLimbActive",0,0);
        rightUpperLimbPntBtn.jointActive        ? XML.setValue("rightArmJointActive",1,0)       : XML.setValue("rightArmJointActive",0,0);
        rightUpperLimbPntBtn.lowerLimbActive    ? XML.setValue("rightArmLowerLimbActive",1,0)   : XML.setValue("rightArmLowerLimbActive",0,0);
        rightUpperLimbPntBtn.limbAverageActive  ? XML.setValue("rightArmLimbAverageActive",1,0) : XML.setValue("rightArmLimbAverageActive",0,0);
        rightUpperLimbPntBtn.lowerJointActive   ? XML.setValue("rightArmLowerJointActive",1,0)  : XML.setValue("rightArmLowerJointActive",0,0);


        leftUpperLimbPntBtn.upperLimbActive    ? XML.setValue("leftArmUpperLimbActive",1,0)     : XML.setValue("leftArmUpperLimbActive",0,0);
        leftUpperLimbPntBtn.jointActive        ? XML.setValue("leftArmJointActive",1,0)         : XML.setValue("leftArmJointActive",0,0);
        leftUpperLimbPntBtn.lowerLimbActive    ? XML.setValue("leftArmLowerLimbActive",1,0)     : XML.setValue("leftArmLowerLimbActive",0,0);
        leftUpperLimbPntBtn.limbAverageActive  ? XML.setValue("leftArmLimbAverageActive",1,0)   : XML.setValue("leftArmLimbAverageActive",0,0);
        leftUpperLimbPntBtn.lowerJointActive   ? XML.setValue("leftArmLowerJointActive",1,0)    : XML.setValue("leftArmLowerJointActive",0,0);


        rightLowerLimbPntBtn.upperLimbActive    ? XML.setValue("rightLegUpperLimbActive",1,0)   : XML.setValue("rightLegUpperLimbActive",0,0);
        rightLowerLimbPntBtn.jointActive        ? XML.setValue("rightLegJointActive",1,0)       : XML.setValue("rightLegJointActive",0,0);
        rightLowerLimbPntBtn.lowerLimbActive    ? XML.setValue("rightLegLowerLimbActive",1,0)   : XML.setValue("rightLegLowerLimbActive",0,0);
        rightLowerLimbPntBtn.limbAverageActive  ? XML.setValue("rightLegLimbAverageActive",1,0) : XML.setValue("rightLegLimbAverageActive",0,0);
        rightLowerLimbPntBtn.lowerJointActive   ? XML.setValue("rightLegLowerJointActive",1,0)  : XML.setValue("rightLegLowerJointActive",0,0);


        leftLowerLimbPntBtn.upperLimbActive    ? XML.setValue("leftLegUpperLimbActive",1,0)     : XML.setValue("leftLegUpperLimbActive",0,0);
        leftLowerLimbPntBtn.jointActive        ? XML.setValue("leftLegJointActive",1,0)         : XML.setValue("leftLegJointActive",0,0);
        leftLowerLimbPntBtn.lowerLimbActive    ? XML.setValue("leftLegLowerLimbActive",1,0)     : XML.setValue("leftLegLowerLimbActive",0,0);
        leftLowerLimbPntBtn.limbAverageActive  ? XML.setValue("leftLegLimbAverageActive",1,0)   : XML.setValue("leftLegLimbAverageActive",0,0);
        leftLowerLimbPntBtn.lowerJointActive   ? XML.setValue("leftLegLowerJointActive",1,0)    : XML.setValue("leftLegLowerJointActive",0,0);


    XML.popTag();

    XML.saveFile("settings/bespokeSettings_"+ofToString(settingsID)+".xml");
    string name = "bespokeSettings_"+ofToString(settingsID)+".xml saved!\n";
    printf(name.c_str());

}
//--------------------------------------------------------------
void testApp::loadSettings(int num){


    printf("loadSettings \n");


    if( XML.loadFile("settings/bespokeSettings_"+ofToString(num)+".xml") ){
		string name = "bespokeSettings_"+ofToString(num)+".xml loaded!\n";
        printf(name.c_str());
	}else{
		printf("unable to load Settings file check data/ folder\n");
	}

    XML.pushTag("SETTINGS",0);


    //--------------------------------------------------------------

        bool headX              = bool(XML.getValue("diaphragmx",0,0));
        bool headY              = bool(XML.getValue("diaphragmy",0,0));
        bool headZ              = bool(XML.getValue("diaphragmz",0,0));

        diaphragmMove.xActive   = headX;
        diaphragmMove.yActive   = headY;
        diaphragmMove.zActive   = headZ;

        bool armLowerRightX     = bool(XML.getValue("armLowerRightx",0,0));
        bool armLowerRightY     = bool(XML.getValue("armLowerRighty",1,0));
        bool armLowerRightZ     = bool(XML.getValue("armLowerRightz",0,0));

        armLowerRight.xActive   = armLowerRightX;
        armLowerRight.yActive   = armLowerRightY;
        armLowerRight.zActive   = armLowerRightZ;

        bool legLowerRightX     = bool(XML.getValue("legLowerRightx",0,0));
        bool legLowerRightY     = bool(XML.getValue("legLowerRighty",1,0));
        bool legLowerRightZ     = bool(XML.getValue("legLowerRightz",0,0));

        legLowerRight.xActive   = legLowerRightX;
        legLowerRight.yActive   = legLowerRightY;
        legLowerRight.zActive   = legLowerRightZ;

        bool armLowerLeftX      = bool(XML.getValue("armLowerLeftx",0,0));
        bool armLowerLeftY      = bool(XML.getValue("armLowerLefty",1,0));
        bool armLowerLeftZ      = bool(XML.getValue("armLowerLeftz",0,0));

        armLowerLeft.xActive    = armLowerLeftX;
        armLowerLeft.yActive    = armLowerLeftY;
        armLowerLeft.zActive    = armLowerLeftZ;

        bool legLowerLeftX      = bool(XML.getValue("legLowerLeftx",0,0));
        bool legLowerLeftY      = bool(XML.getValue("legLowerLefty",1,0));
        bool legLowerLeftZ      = bool(XML.getValue("legLowerLeftz",0,0));

        legLowerLeft.xActive    = legLowerLeftX;
        legLowerLeft.yActive    = legLowerLeftY;
        legLowerLeft.zActive    = legLowerLeftZ;

        bool finalTorsoX      = bool(XML.getValue("finaltorsox",0,0));
        bool finalTorsoY      = bool(XML.getValue("finaltorsoy",1,0));
        bool finalTorsoZ      = bool(XML.getValue("finaltorsoz",0,0));

        finalTorsoMove.xActive    = finalTorsoX;
        finalTorsoMove.yActive    = finalTorsoY;
        finalTorsoMove.zActive    = finalTorsoZ;


        //--------------------------------------------------------------------------------


        if(bool(XML.getValue("RIGHT-ARM-POS-MOVES-ONLY",0,0))){
            armLowerRight.setPosMoves();
        }
        if(bool(XML.getValue("RIGHT-ARM-POS-NEG-MOVES",0,0))){
            armLowerRight.setPosNegMoves();
        }
        if(bool(XML.getValue("RIGHT-ARM-ALL-MOVES-POS",0,0))){
            armLowerRight.setAllMovesPositive();
        }

        if(bool(XML.getValue("LEFT-ARM-POS-MOVES-ONLY",0,0))){
            armLowerLeft.setPosMoves();
        }
        if(bool(XML.getValue("LEFT-ARM-POS-NEG-MOVES",0,0))){
            armLowerLeft.setPosNegMoves();
        }
        if(bool(XML.getValue("LEFT-ARM-ALL-MOVES-POS",0,0))){
            armLowerLeft.setAllMovesPositive();
        }

        if(bool(XML.getValue("LEFT-LEG-POS-MOVES-ONLY",0,0))){
            legLowerLeft.setPosMoves();
        }
        if(bool(XML.getValue("LEFT-LEG-POS-NEG-MOVES",0,0))){
            legLowerLeft.setPosNegMoves();
        }
        if(bool(XML.getValue("LEFT-LEG-ALL-MOVES-POS",0,0))){
            legLowerLeft.setAllMovesPositive();
        }

        if(bool(XML.getValue("RIGHT-LEG-POS-MOVES-ONLY",0,0))){
            legLowerRight.setPosMoves();
        }
        if(bool(XML.getValue("RIGHT-LEG-POS-NEG-MOVES",0,0))){
            legLowerRight.setPosNegMoves();
        }
        if(bool(XML.getValue("RIGHT-LEG-ALL-MOVES-POS",0,0))){
            legLowerRight.setAllMovesPositive();
        }

        if(bool(XML.getValue("DIAPHRAGM-POS-MOVES-ONLY",0,0))){
            diaphragmMove.setPosMoves();
        }
        if(bool(XML.getValue("DIAPHRAGM-POS-NEG-MOVES",0,0))){
            diaphragmMove.setPosNegMoves();
        }
        if(bool(XML.getValue("DIAPHRAGM-ALL-MOVES-POS",0,0))){
            diaphragmMove.setAllMovesPositive();
        }

        if(bool(XML.getValue("FINALTORSO-POS-MOVES-ONLY",0,0))){
            finalTorsoMove.setPosMoves();
        }
        if(bool(XML.getValue("FINALTORSO-POS-NEG-MOVES",0,0))){
            finalTorsoMove.setPosNegMoves();
        }
        if(bool(XML.getValue("FINALTORSO-ALL-MOVES-POS",0,0))){
            finalTorsoMove.setAllMovesPositive();
        }



        //--------------------------------------------------------------------------------

        rightUpperLimbPntBtn.upperLimbActive    = bool(XML.getValue("rightArmUpperLimbActive",0,0));
        rightUpperLimbPntBtn.jointActive        = bool(XML.getValue("rightArmJointActive",0,0));
        rightUpperLimbPntBtn.lowerLimbActive    = bool(XML.getValue("rightArmLowerLimbActive",0,0));
        rightUpperLimbPntBtn.limbAverageActive  = bool(XML.getValue("rightArmLimbAverageActive",0,0));
        rightUpperLimbPntBtn.lowerJointActive   = bool(XML.getValue("rightArmLowerJointActive",0,0));

        leftUpperLimbPntBtn.upperLimbActive    = bool(XML.getValue("leftArmUpperLimbActive",0,0));
        leftUpperLimbPntBtn.jointActive        = bool(XML.getValue("leftArmJointActive",0,0));
        leftUpperLimbPntBtn.lowerLimbActive    = bool(XML.getValue("leftArmLowerLimbActive",0,0));
        leftUpperLimbPntBtn.limbAverageActive  = bool(XML.getValue("leftArmLimbAverageActive",0,0));
        leftUpperLimbPntBtn.lowerJointActive   = bool(XML.getValue("leftArmLowerJointActive",0,0));

        rightLowerLimbPntBtn.upperLimbActive    = bool(XML.getValue("rightLegUpperLimbActive",0,0));
        rightLowerLimbPntBtn.jointActive        = bool(XML.getValue("rightLegJointActive",0,0));
        rightLowerLimbPntBtn.lowerLimbActive    = bool(XML.getValue("rightLegLowerLimbActive",0,0));
        rightLowerLimbPntBtn.limbAverageActive  = bool(XML.getValue("rightLegLimbAverageActive",0,0));
        rightLowerLimbPntBtn.lowerJointActive   = bool(XML.getValue("rightLegLowerJointActive",0,0));

        leftLowerLimbPntBtn.upperLimbActive    = bool(XML.getValue("leftLegUpperLimbActive",0,0));
        leftLowerLimbPntBtn.jointActive        = bool(XML.getValue("leftLegJointActive",0,0));
        leftLowerLimbPntBtn.lowerLimbActive    = bool(XML.getValue("leftLegLowerLimbActive",0,0));
        leftLowerLimbPntBtn.limbAverageActive  = bool(XML.getValue("leftLegLimbAverageActive",0,0));
        leftLowerLimbPntBtn.lowerJointActive   = bool(XML.getValue("leftLegLowerJointActive",0,0));


    XML.popTag();

    resetAllVideos();

}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

    lastkey = key;

    if(key == 358 && !useLiveData)  loader->nextFrame(); // right arrow key
    if(key == 356 && !useLiveData)  loader->prevFrame(); // left arrow key
    if(key =='s' && !useLiveData)  loader->start();
    if(key =='a'&& !useLiveData)  loader->stop();

    /*if(key =='p') {
        //presentationMode = !presentationMode;
        presentationModeID++;
        if(presentationModeID >= 4) presentationModeID = 0;

        if(presentationModeID == 0) resetLimbPosChangeColors();
        if(presentationModeID == 3) setLimbPosChangeColorsForInstallation();

    }*/

    if(key =='s' || key =='S') presentationModeID = 0;
    if(key =='h' || key =='H') presentationModeID = 1;
    if(key =='v' || key =='V') presentationModeID = 2;
    if(key =='i' || key =='I') presentationModeID = 3;
    if(key =='f' || key =='F') presentationModeID = 4;


    if(key == '1') {
        bool hit = true;
        setSettingsOne(hit);
    };
    if(key == '2') {
        bool hit = true;
        setSettingsTwo(hit);
    };
    if(key == '3') {
        bool hit = true;
        setSettingsThree(hit);
    };
    if(key == '4') {
        bool hit = true;
        setSettingsFour(hit);
    };

    if(presentationModeID == 0){

        leftArmVideo.drawInfo   = true;
        leftLegVideo.drawInfo   = true;
        rightArmVideo.drawInfo  = true;
        rightLegVideo.drawInfo  = true;
        torsoVideo.drawInfo     = true;
        unwindVideo.drawInfo    = true;
        skeletonRotationVideo.drawInfo = true;

        ofShowCursor();

    } else {

        leftArmVideo.drawInfo   = false;
        leftLegVideo.drawInfo   = false;
        rightArmVideo.drawInfo  = false;
        rightLegVideo.drawInfo  = false;
        torsoVideo.drawInfo     = false;
        unwindVideo.drawInfo    = false;
        skeletonRotationVideo.drawInfo = false;

        ofHideCursor();

    }

}
//--------------------------------------------------------------
void testApp::resetLimbPosChangeColors(){

    if(useLiveData) MSkinect.lineCol = 0x000000;

}
//--------------------------------------------------------------
void testApp::setLimbPosChangeColorsForInstallation(){
    //----------------------------------------------

    armLowerLeft.bgColor            = 0x1a1a1a;
    armLowerRight.bgColor           = 0x1a1a1a;
    legLowerLeft.bgColor            = 0x1a1a1a;
    legLowerRight.bgColor           = 0x1a1a1a;
    diaphragmMove.bgColor           = 0x1a1a1a;
    finalTorsoMove.bgColor          = 0x1a1a1a;

    if(useLiveData) MSkinect.lineCol = 0x333333;

}
//--------------------------------------------------------------
void testApp::fadeOutVideoParts(){
    videoPartsAlphaTween.setParameters(cubicEase,ofxTween::easeOut,255,0, 500, 0);
}
//--------------------------------------------------------------
void testApp::fadeInVideoParts(){
    videoPartsAlphaTween.setParameters(cubicEase,ofxTween::easeOut,0,255, 500, 0);
}
//--------------------------------------------------------------
void testApp::fadeOutSkeletonVideo(){
    skeletonVideoAlphaTween.setParameters(cubicEase,ofxTween::easeOut,255,0, 500, 0);
}
//--------------------------------------------------------------
void testApp::fadeInSkeletonVideo(){
    skelTwirlStarted    = true;
    skeletonVideoAlphaTween.setParameters(cubicEase,ofxTween::easeOut,0,255, 500, 0);
    fadeOutVideoParts();
}
//--------------------------------------------------------------
void testApp::fadeOutUnwindVideo(){
    unwindVideoAlphaTween.setParameters(cubicEase,ofxTween::easeOut,255,0, 500, 0);
}
//--------------------------------------------------------------
void testApp::fadeInUnwindVideo(){
    unwindStarted       = true;
    unwindVideoAlpha    = 255;
    fadeOutSkeletonVideo();
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    saveSettings();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
