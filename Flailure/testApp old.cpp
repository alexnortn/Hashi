    /*
 testApp.cpp
 ofxHapPlayerExample
 
 Copyright (c) 2013, Tom Butterworth. All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "testApp.h"
#include "math.h"

//--------------------------------------------------------------
void testApp::setup(){
    // Limit drawing to a sane rate
    ofSetVerticalSync(true);
    
    ofBackground(220, 220, 220);

    // start the MovThread
    movThread.load("movies/Washi-18.mov");
    movThread.startThread(true, false);    // blocking, non-verbose

    movThread1.load("movies/Washi-18.mov");
    movThread1.startThread(true, false);    // blocking, non-verbose

    movThread2.load("movies/Washi-18.mov");
    movThread2.startThread(true, false);    // blocking, non-verbose

    loading = false;
    
    // Load a movie file
    player.loadMovie("movies/Washi-0.mov");
    player1.loadMovie("movies/Washi-1.mov");
    player2.loadMovie("movies/Washi-2.mov");
    
    // How many video files do we have?
    fileNumber();

    clipNum = -1;

    // Give our pointer something to get started with
    playMov = &player;
    playMov1 = &player1;

    // Start playing the movies
    playMov->play();
    playMov1->play();

    play = true;
    alpha = 255;
    alpha1 = 0;

}

//--------------------------------------------------------------
void testApp::update(){

    if (loading) updatePtr();

    // Signal the player to update
    if (playMov->isLoaded()) {
        playMov->update();
    }
    if (playMov1->isLoaded()) {
        playMov1->update(); 
    }

}

//--------------------------------------------------------------
void testApp::draw(){

    ofEnableAlphaBlending();
    
    if (playMov->isLoaded()) {
        // Draw the frame
        ofSetColor(255, 255, 255, alpha);
        playMov->setVolume(0.0f);
        playMov->draw(0, 0, 800, 450);
    } else {
        cout << "WTF LOAD" << endl;
    }
    
    if (playMov1->isLoaded()) {
        // Draw the frame
        ofSetColor(255, 255, 255, alpha1);
        playMov1->setVolume(0.0f);
        playMov1->draw(0, 0, 800, 450);
    }  else {
        cout << "WTF LOAD1" << endl;
    }

    // Draw the FPS display
    ofSetColor(255,0,0);
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + " FPS", 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key == ' ') {
        
        // Increment the clip index
        (clipNum <= movNum) ? clipNum++ : clipNum = 0;
        
        // Perform the cut / transition | switch
        (alpha == 255) ? alpha = 0 : alpha = 255;
        (alpha1 == 255) ? alpha1 = 0 : alpha1 = 255;

        play = !play;

        // // Load the next movie file
        movPlayer();
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    float position = (float) x / (float) ofGetWindowWidth();
    cout << "Setting playhead to " << ofToString(position) << endl;

    if (playMov->isLoaded()) playMov->setPosition(position);
    if (playMov1->isLoaded()) playMov1->setPosition(position);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	vector< string > fileList = dragInfo.files;
    // playMov->loadMovie(fileList[0]);
}

int testApp::fileNumber() {
    //some path, may be absolute or relative to bin/data
    string path = "movies/"; 
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("mov");
    //populate the directory object
    dir.listDir();

    movNum = dir.numFiles();
    cout << "There are " + ofToString(movNum) + " Mov files in your Bin \n" << endl;

    return movNum;
}

void testApp::movPlayer() {

    // Which file to load?
    string movCurrentPlus = ofToString(clipNum);
    vidPath = "movies/Washi-" + movCurrentPlus + ".mov";

    int movPoint;

    if (clipNum % 3 == 0) {

        movPoint = 0;
        cout << "clipNum mod 3 == 0" << endl;  

        // stop playing previous clip
        if (playMov->isPlaying()) playMov->stop();
        
        // Swap nation
        if (player2.isLoaded()) {
            playMov = &player2;
            playMov->play();
        }

        // Do all the async threading...
        loadMovie(movPoint, vidPath);


    } else if (clipNum % 3 == 1) {
        cout << "clipNum mod 3 == 1" << endl;

        movPoint = 1;

        // stop playing previous clip
        if (playMov1->isPlaying()) playMov1->stop();

        // Swap nation
        if (player.isLoaded()) {
            playMov1 = &player;
            playMov1->play();
        } 

        // Do all the async threading...
        loadMovie(movPoint, vidPath);

    } else if (clipNum % 3 == 2) {
        cout << "clipNum mod 3 == 2" << endl;

        movPoint = 2;
        
        // stop playing previous clip
        if (playMov->isPlaying()) playMov->stop();
        
        // Swap nation
        if (player1.isLoaded()) {
            playMov = &player1;
            playMov->play();
        } 

        // Do all the async threading...
        loadMovie(movPoint, vidPath);

    }

    string movLength = ofToString(floor(playMov->getDuration()));
    string movName = playMov->getMoviePath();

    cout << movName + " is " + movLength + " seconds long" << endl;

}

void testApp::exit() {
 
    // stop the thread
    movThread.stopThread();

}

void testApp::loadMovie(int movPointer, string loadPath) {


    if (movPointer == 0) {
        playMovRef = &player;
        cout << "appSide movPoint = 0 :: playMoveRef = &player" << endl;
    } else if (movPointer == 1) {
        playMovRef = &player1;
        cout << "appSide movPoint = 1 :: playMoveRef = &player1" << endl;
    } else if (movPointer == 2) {
        playMovRef = &player2;
        cout << "appSide movPoint = 2 :: playMoveRef = &player2" << endl;
    }
        

    // Unload previous video object
    if (playMovRef->isLoaded()) {
        playMovRef->close();
        cout << "appSide unloading our <player>" << endl;
    }

    // Let's do it with Threads!

    movThread.load(loadPath);  

    loading = true;

}


void testApp::updatePtr() {

    if (movThread.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        movThread.lock();
 
        // copy image
        *playMovRef = movThread.playerThread;

        if (playMovRef->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread.loaded = false;
        }

        // Unlock access
        movThread.unlock();

        loading = false;

    } 

}