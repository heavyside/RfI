#include "ShapeFromShadingAnalysis.h"
#include "ofMain.h"

#include "Poco/Timer.h"
#include "Poco/Thread.h"

#include "RefractiveIndex.h"

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;

void ShapeFromShadingAnalysis::setup(int camWidth, int camHeight)
{    
    NUM_RUN = 1;
    
    int acq_run_time = 20;   // 20 seconds of acquiring per run
    
    DELTA_T_SAVE = 10*acq_run_time/2; // for 20 seconds, we want this to be around 200 files
    // or 10 times per second = every 100 ms
    
    _frame_cnt_max = acq_run_time*ofGetFrameRate();  // e.g.: 30 frames per second * 20 seconds = 600 frames
    
    create_dir();
    
    _frame_cnt = 0;
    c = 0;
    
    int anim_time = 5;   // 10 seconds
    _anim_cnt_max = anim_time*ofGetFrameRate();  // e.g.: 30 frames per second = 150 frames
    
    _show_image = false;
    _image_shown = false;
    
    //for an ofxOpenCv.h image i would like to use..."
    //image3.allocate(RefractiveIndex::_vid_w, RefractiveIndex::_vid_h);

    image1.setUseTexture(false);
    image2.setUseTexture(true);
}



void ShapeFromShadingAnalysis::acquire()
{

    Timer* save_timer;

    TimerCallback<ShapeFromShadingAnalysis> save_callback(*this, &ShapeFromShadingAnalysis::save_cb);

    // RUN ROUTINE
    for(int i = 0; i < NUM_RUN; i++) {

        _run_cnt = i;

        cout << "RUN NUM = " << i;

        save_timer = new Timer(0, DELTA_T_SAVE); // timing interval for saving files
        save_timer->start(save_callback);
        _RUN_DONE = false;
         _frame_cnt = 0; _save_cnt = 0; _anim_cnt = 0;
        
        _animation_cnt1 = 0;
        _animation_cnt2 = 0;
        _animation_cnt3 = 0;
        _animation_cnt4 = 0;
        _animation_cnt5 = 0;
        _animation_cnt6 = 0;
        _animation_cnt7 = 0;
        _animation_cnt8 = 0;
        _animation_cnt9 = 0;
        _animation_cnt10 = 0;
        _animation_cnt11 = 0;
        _animation_cnt12 = 0;
        _animation_cnt13 = 0;
        _animation_cnt14 = 0;
        _animation_cnt15 = 0;
        _animation_cnt16 = 0;
        _animation_reset = false;  // coundn't get this to work - so using seperate counters - shitty!
        
        while(!_RUN_DONE)
            Thread::sleep(3);

        save_timer->stop();
        
        _RUN_DONE = false;

    }
}

void ShapeFromShadingAnalysis::synthesise()
{
    while(!_RUN_DONE)
        Thread::sleep(3);
}

void ShapeFromShadingAnalysis::displayresults()
{
    
    for(float i=1;i<_saved_filenames.size();i++){
        
        cout << "_saved_filenames[i]" << _saved_filenames[i] << endl;
        
        while(!_image_shown){
            Thread::sleep(2);
            //cout << "!_image_shown" << endl;
        }
        
        
        if(!image1.loadImage(_saved_filenames[i])){
            //couldn't load image
            cout << "didn't load image" << endl;
        } 
        
        
        if(image1.loadImage(_saved_filenames[i])){
            image1.loadImage(_saved_filenames[i]);
            //cout << "_show_image = true;" << endl;
            _show_image = true;
            _image_shown = false;
        }
    }
}

// this runs at frame rate = 33 ms for 30 FPS
void ShapeFromShadingAnalysis::draw()
{
    
    switch (_state) {
        case STATE_ACQUIRING:
        {
            if (_frame_cnt < _frame_cnt_max)
            {
                
                ofEnableAlphaBlending();
                
                int _quarter_frame_cnt_max = _frame_cnt_max/4;
                int _half_frame_cnt_max = _frame_cnt_max/2;
                int _threequarters_frame_cnt_max = 3*_frame_cnt_max/4;
                
                if(_frame_cnt < _quarter_frame_cnt_max) {
                    
                    quad =  "QUAD1";
                    //cout << quad << endl;
                    
                    if(_frame_cnt <= _quarter_frame_cnt_max/4)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt1, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(3*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());
                        _animation_cnt1++;
                    }
                    
                    if(_frame_cnt <= _quarter_frame_cnt_max/2)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt2, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(2.5*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());   
                        _animation_cnt2++;
                    }
                    
                    if(_frame_cnt <= _quarter_frame_cnt_max) 
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt3, 0, _quarter_frame_cnt_max/4, 0, 255));
                        
                        ofRect(2.25*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());      
                        _animation_cnt3++;
                    }
                    
                    if((7*_quarter_frame_cnt_max/8 < _frame_cnt) && (_frame_cnt < _quarter_frame_cnt_max))
                    {
                        
                        ofSetColor(0, 0, 0, ofMap(_animation_cnt4, 0, _quarter_frame_cnt_max/8, 0, 255));                    
                        //cout << "4 counter: " << ofMap(_animation_cnt4, 0, _quarter_frame_cnt_max/8, 0, 255) << endl;
                        
                        ofRect(2.25*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());
                        //ofRect(2.25*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());   
                        //ofRect(2.5*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight()); 
                        //ofRect(2.75*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());      
                        _animation_cnt4++;
                    }  
                    
                    
                } 
                
                
                if((_frame_cnt >= _frame_cnt_max/4) && (_frame_cnt < _frame_cnt_max/2)){
                    
                    quad =  "QUAD2";
                    //cout << quad << endl;
                    
                    int _local_frame_count = _frame_cnt - _quarter_frame_cnt_max;
                    //cout << "_local_frame_count" << _local_frame_count << endl;
                    
                    if(_local_frame_count < _quarter_frame_cnt_max/4)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt5, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(0, 3*ofGetHeight()/4, ofGetWidth(), ofGetHeight()/2);
                        //cout << "_animation_cnt1: " << _animation_cnt1 << endl;
                        
                        _animation_cnt5++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max/2)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt6, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(0, 2.5*ofGetHeight()/4, ofGetWidth(), ofGetHeight()/2);
                        _animation_cnt6++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max) 
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt7, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(0, 2.25*ofGetHeight()/4, ofGetWidth(), ofGetHeight()/2);
                        _animation_cnt7++;
                    }
                    
                    if((7*_quarter_frame_cnt_max/8 < _local_frame_count) && (_local_frame_count < _quarter_frame_cnt_max))
                    {
                        
                        ofSetColor(0, 0, 0, ofMap(_animation_cnt8, 0, _quarter_frame_cnt_max/8, 0, 255));                    
                        //cout << "4 counter: " << ofMap(_animation_cnt4, 0, _quarter_frame_cnt_max/8, 0, 255) << endl;
                        
                        ofRect(0, 2.25*ofGetHeight()/4, ofGetWidth(), ofGetHeight()/2);
                        //ofRect(2.25*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());   
                        //ofRect(2.5*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight()); 
                        //ofRect(2.75*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());      
                        _animation_cnt8++;
                    }  
                    
                    
            
                }
                
                
                //draw bottom middle
                if ((_frame_cnt >= _frame_cnt_max/2)  && (_frame_cnt < 3*_frame_cnt_max/4)) {
                    
                    quad =  "QUAD3";
                    //cout << quad << endl;
                    
                    int _local_frame_count = _frame_cnt - _half_frame_cnt_max;
                    //cout << "_local_frame_count" << _local_frame_count << endl;
                    
                    
                    
                    if(_local_frame_count <= _quarter_frame_cnt_max/4)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt9, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(ofGetWidth()/4, 0, -ofGetWidth()/2, ofGetHeight());
                        //cout << "_animation_cnt1: " << _animation_cnt1 << endl;
                        
                        _animation_cnt9++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max/2)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt10, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(1.25*ofGetWidth()/4, 0, -ofGetWidth()/2, ofGetHeight());
                        _animation_cnt10++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max) 
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt11, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(1.5*ofGetWidth()/4, 0, -ofGetWidth()/2, ofGetHeight());
                        _animation_cnt11++;
                    }
                    
                    if((7*_quarter_frame_cnt_max/8 < _local_frame_count) && (_local_frame_count < _quarter_frame_cnt_max))
                    {
                        
                        ofSetColor(0, 0, 0, ofMap(_animation_cnt12, 0, _quarter_frame_cnt_max/8, 0, 255));                    
                        //cout << "4 counter: " << ofMap(_animation_cnt4, 0, _quarter_frame_cnt_max/8, 0, 255) << endl;
                        
                        ofRect(1.5*ofGetWidth()/4, 0, -ofGetWidth()/2, ofGetHeight());
                        //ofRect(2.25*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());   
                        //ofRect(2.5*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight()); 
                        //ofRect(2.75*ofGetWidth()/4, 0, ofGetWidth()/2, ofGetHeight());      
                        _animation_cnt12++;
                    }  
                
                }
                
                
                //draw left
                if((_frame_cnt >= 3*_frame_cnt_max/4) && (_frame_cnt <= _frame_cnt_max) ){
                    
                    quad =  "QUAD4";
                    //cout << quad << endl;
                    
                    int _local_frame_count = _frame_cnt - _threequarters_frame_cnt_max;
                    //cout << "_local_frame_count" << _local_frame_count << endl;
                    
                    
                    if(_local_frame_count <= _quarter_frame_cnt_max/4)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt13, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(0, ofGetHeight()/4, ofGetWidth(), -ofGetHeight()/2);
                        //cout << "_animation_cnt13: " << _animation_cnt1 << endl;
                        
                        _animation_cnt13++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max/2)
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt14, 0, _quarter_frame_cnt_max/4, 0, 255));
                        
                        ofRect(0, 1.25*ofGetHeight()/4, ofGetWidth(), -ofGetHeight()/2);
                        _animation_cnt14++;
                    }
                    
                    if(_local_frame_count < _quarter_frame_cnt_max) 
                    {
                        ofSetColor(255, 255, 255, ofMap(_animation_cnt15, 0, _quarter_frame_cnt_max/4, 0, 255));
                        ofRect(0, 1.5*ofGetHeight()/4, ofGetWidth(), -ofGetHeight()/2);
                        _animation_cnt15++;
                    }
                    
                    if((7*_quarter_frame_cnt_max/8 < _local_frame_count) && (_local_frame_count < _quarter_frame_cnt_max))
                    {
                        
                        ofSetColor(0, 0, 0, ofMap(_animation_cnt16, 0, _quarter_frame_cnt_max/8, 0, 255));                    
                        //cout << "4 counter: " << ofMap(_animation_cnt4, 0, _quarter_frame_cnt_max/8, 0, 255) << endl;
                        
                        ofRect(0, 1.5*ofGetHeight()/4, ofGetWidth(), -ofGetHeight()/2);
                        
                        _animation_cnt16++;
                    }  
                    
                }
                
                ofDisableAlphaBlending();
            } else {
                //_state = STATE_SYNTHESISING;
                _frame_cnt = 0;
                _RUN_DONE = true;
            }
            
            _frame_cnt++;
            //cout << "_frame_cnt:" << _frame_cnt << endl;            
            
            break;
        }
            
        case STATE_SYNTHESISING:
        {
            // display animation of something while the synthesis in on-going...
            
            cout << "RelaxRateAnalysis = STATE_SYNTHESISING...\n";
            
            // display animation of something while the synthesis in on-going...
            ofEnableAlphaBlending();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            
            if(_anim_cnt < _anim_cnt_max){
                
                ofColor aColour;
                int rectSizeW = ofGetWidth()/4;
                int rectSizeH = ofGetHeight()/4;
                int _fade_in_frames = _anim_cnt_max/2;
                
                int c_anim = 10;
                int fade;
                
                //ofRotate(ofMap(_anim_cnt/2.0, 0, _anim_cnt_max, 0, 360));
                
                if (_anim_cnt < _fade_in_frames) {
                    cout << "ShadowScapesAnalysis STATE_SYNTHESIZING = FADING IN ANIMATION...\n";
                    
                    fade = ofMap(_anim_cnt, 0, _fade_in_frames, 0, 255);
                    
                    for (int i=0; i <= 15; i++){
                        c_anim = 0+17*i;
                        
                        aColour.set(c_anim, c_anim, c_anim, fade);
                        ofSetColor(aColour);
                        
                        ofRect(0, 0, rectSizeW+10*i, rectSizeH+10*i);
                        ofRect(0, 0, rectSizeW-10*i, rectSizeH-10*i);
                    }
                }
                
                if (_anim_cnt >= _fade_in_frames && _anim_cnt <= (_anim_cnt_max-_fade_in_frames)){
                    
                    for (int i=0; i <= 15; i++){
                        c_anim = 255;
                        aColour.set(c_anim, c_anim, c_anim, 255);
                        ofSetColor(aColour);
                        
                        ofRect(0, 0, rectSizeW+10*i, rectSizeH+10*i);
                        ofRect(0, 0, rectSizeW-10*i, rectSizeH-10*i);
                    }
                }
                
                if (_anim_cnt > (_anim_cnt_max-_fade_in_frames) && _anim_cnt <= _anim_cnt_max) {
                    
                    cout << "_anim_cnt = " << _anim_cnt-(_anim_cnt_max-_fade_in_frames) << endl;
                    fade = ofMap(_anim_cnt-(_anim_cnt_max-_fade_in_frames), 0, _fade_in_frames, 0, 255);
                    cout << "fade down = " << fade << endl;
                    
                    for (int i=0; i <= 15; i++){
                        
                        c_anim = (17*i);
                        
                        aColour.set(c_anim, c_anim, c_anim, 255-fade);
                        ofSetColor(aColour);
                        ofRect(0, 0, rectSizeW+10*i, rectSizeH+10*i);
                        ofRect(0, 0, rectSizeW-10*i, rectSizeH-10*i);
                    }
                    
                }
                _anim_cnt++;
                
            } else {
                _RUN_DONE = true;
                //_state = STATE_DISPLAY_RESULTS;
                _anim_cnt=0;
            }
            ofPopMatrix();
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofDisableAlphaBlending();
            
            break;
        }
            
        
            
        case STATE_DISPLAY_RESULTS:
        {   
            if (_frame_cnt > 2)
            {
                _image_shown = true;
                _frame_cnt=0;
            }
            
            _frame_cnt++;
            
            if (_show_image)
            {  
                ofEnableAlphaBlending();
                
                    ofSetColor(255, 255, 255, 255);
                    image2.setFromPixels(image1.getPixels(),image1.width,image1.height, OF_IMAGE_COLOR);
                    image2.draw(0,0, ofGetWidth(), ofGetHeight());
                
                ofDisableAlphaBlending();
            }

            // display results of the synthesis
            _RUN_DONE = true;
            break;
        }
            
            
        default:
            break;
    }


}

// this runs at save_cb timer rate = DELTA_T_SAVE
void ShapeFromShadingAnalysis::save_cb(Timer& timer)
{
    _save_cnt++;
        
    RefractiveIndex::_vidGrabber.grabFrame();  // get a new frame from the camera
    
    if (RefractiveIndex::_vidGrabber.isFrameNew())
    {
        RefractiveIndex::_pixels = RefractiveIndex::_vidGrabber.getPixelsRef(); //get ofPixels from the camera
    }
    
    //cout << "ShapeFromShadingAnalysis::saving...\n";
    
    string file_name = ofToString(_save_cnt,2)+"_"+ quad +"_"+ofToString(_run_cnt,2)+".jpg";
    
    ofSaveImage(RefractiveIndex::_pixels, _whole_file_path+"/"+file_name, OF_IMAGE_QUALITY_BEST);
    
    _saved_filenames.push_back(_whole_file_path+"/"+file_name);

}
