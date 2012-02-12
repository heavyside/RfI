/*
 ~ author: dviid
 ~ contact: dviid@labs.ciid.dk
 */

#include "DiffNoiseAnalysis.h"
#include "ofMain.h"

#include "Poco/Timer.h"
#include "Poco/Thread.h"

#include "RefractiveIndex.h"

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;


void DiffNoiseAnalysis::setup(int camWidth, int camHeight)
{
    DELTA_T_SAVE = 100;
    NUM_PHASE = 1;
    NUM_RUN = 1;
    NUM_SAVE_PER_RUN = 100;    
    
    create_dir();
    _frame_cnt = 0;
    _frame_cnt_max = ofGetFrameRate() * ((DELTA_T_SAVE * NUM_SAVE_PER_RUN) / 1000);
    c = 0;
}


void DiffNoiseAnalysis::synthesize()
{

    Timer* save_timer;

    TimerCallback<DiffNoiseAnalysis> save_callback(*this, &DiffNoiseAnalysis::save_cb);

    // RUN ROUTINE
    for(int i = 0; i < NUM_RUN; i++) {

        _run_cnt = i;

        cout << "RUN NUM = " << i;

        save_timer = new Timer(0, DELTA_T_SAVE); // timing interval for saving files
        save_timer->start(save_callback);
        _RUN_DONE = false;
        _frame_cnt = 0; _save_cnt = 0;

        while(!_RUN_DONE)
            Thread::sleep(3);

        save_timer->stop();
    }
}

// this runs at frame rate = 33 ms for 30 FPS
void DiffNoiseAnalysis::draw()
{
    /// *** TODO  *** ///
    // still need to deal with latency frames here - i.e.: there are frames
    /// *** TODO  *** ///
    ofColor aColour;

    c = ofRandom(0,255);
    aColour.setHsb(c, 255, 255);
    if (_frame_cnt < _frame_cnt_max)
    {
        ofSetColor(aColour);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());

    }
    _frame_cnt++;


}

// this runs at save_cb timer rate = DELTA_T_SAVE
void DiffNoiseAnalysis::save_cb(Timer& timer)
{


    float rand10 = ofRandom(0,10);

    if (rand10 > 5.0) {

    cout << "DiffNoiseAnalysis::saving...\n";
    cout << "c_last... " << c << endl;
    cout<<"rand10... " <<rand10<<endl;

    string file_name = ofToString(_save_cnt,2)+"_"+ ofToString(c,2)+"_"+ofToString(_run_cnt,2)+".jpg";
    string thisLocation = RefractiveIndex::_location;

    //RefractiveIndex::_pixels = RefractiveIndex::_vidGrabber.getPixelsRef(); //get ofPixels from the camera
    //    fileName = imageSaveFolderPath+whichAnalysis+"_"+ofToString(100.0*i*scanLineSpeed/ofGetHeight(),2)+"%_"+ofToString(i)+".jpg";
    //ofSaveImage(vectorOfPixels[i], fileName, OF_IMAGE_QUALITY_BEST);

    ofSaveImage(RefractiveIndex::_pixels, _whole_file_path+"/"+file_name, OF_IMAGE_QUALITY_BEST);

    }
    _save_cnt++;
    if(_save_cnt >= NUM_SAVE_PER_RUN)
        _RUN_DONE = true;

}
