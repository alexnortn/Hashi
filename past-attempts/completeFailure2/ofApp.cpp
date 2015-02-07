#include "ofApp.h"
#include "math.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// Limit drawing to a sane rate
    ofSetVerticalSync(true);
    
    ofBackground(220, 220, 220);

    w = 800;
    h = 450;

    movTexture.allocate(w, h, GL_RGB);
    movTexture1.allocate(w, h, GL_RGB);

    movThread.load("movies1/Washi-1.mov");

    // start the MovThread
    movThread.startThread();    // blocking, non-verbose


    // player1.loadMovie("movies/Washi-18.mov");

    loading = false;

    // Load a movie file
    playMov->loadMovie("movies1/Washi-1.mov");
    playMov1->loadMovie("movies1/Washi-1.mov");

    // How many video files do we have?
    fileNumber();

    // Start playing the movies
    playMov->play();
    playMov1->play();

    clipNum = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

	if (loading) updatePtr();

	if (playMov->isLoaded()) {
		playMov->update();
		movThread.lock();
		movTexture.loadData(playMov->getPixelsRef());
		movThread.unlock();
	}

	if (playMov1->isLoaded()) {
		playMov1->update();
		movThread.lock();
		movTexture.loadData(playMov1->getPixelsRef());
		movThread.unlock();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255, 255, 255, alpha);
    if (playMov->isLoaded()) {
    	movTexture.draw(20,20,w,h);
    	playMov->setVolume(0.0f);
	}

    ofSetColor(255, 255, 255, alpha1);
    if (playMov1->isLoaded()) {
    	movTexture1.draw(20,20,w,h);
    	playMov1->setVolume(0.0f);
	}

    // Draw the FPS display
    ofSetColor(255,0,0);
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + " FPS", 20, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == ' ') {
        
        // Increment the clip index
        (clipNum <= movNum) ? clipNum++ : clipNum = 0;

        // Perform the cut / transition | switch
        (alpha == 255) ? alpha = 0 : alpha = 255;
        (alpha1 == 255) ? alpha1 = 0 : alpha1 = 255;

    }

    movPlayer();
    // movThread.load(vidPath);  

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float position = (float) x / (float) ofGetWindowWidth();
    cout << "Setting playhead to " << ofToString(position) << endl;

    if (playMov->isLoaded()) playMov->setPosition(position);
    if (playMov1->isLoaded()) playMov1->setPosition(position);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

int ofApp::fileNumber() {
    //some path, may be absolute or relative to bin/data
    string path = "movies1/"; 
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("mov");
    //populate the directory object
    dir.listDir();

    movNum = dir.numFiles();
    cout << "There are " + ofToString(movNum) + " Mov files in your Bin \n" << endl;

    return movNum;
}

void ofApp::exit() {
 
    // stop the thread
    movThread.stopThread();

}

void ofApp::movPlayer() {

    // Which file to load?
    string movCurrentPlus = ofToString(clipNum);
    vidPath = "movies1/Washi-" + movCurrentPlus + ".mov";

     if (clipNum % 2 == 0) {

        movPoint = 0;

        // stop playing previous clip
        if (playMov->isPlaying()) playMov->stop();

        // Load player
        loadMovie(movPoint, vidPath);


    } else if (clipNum % 2 == 1) {
        cout << "clipNum mod 3 == 1" << endl;

        movPoint = 1;

        // stop playing previous clip
        if (playMov1->isPlaying()) playMov1->stop();

        // Load player1
        loadMovie(movPoint, vidPath);

    }

    string movLength = ofToString(floor(playMov->getDuration()));
    string movName = playMov->getMoviePath();

    cout << movName + " is " + movLength + " seconds long" << endl;


}

void ofApp::loadMovie(int movPointer, string loadPath) {


    if (movPointer == 0) {
        playMov->close();
        delete playMov;
        playMov = new ofVideoPlayer();
        cout << "appSide movPoint = 0 :: playMoveRef = &player" << endl;
    } else if (movPointer == 1) {
        playMov1->close();
        delete playMov1;
        playMov1 = new ofVideoPlayer();
    }
        

    // Let's do it with Threads!

    movThread.load(loadPath);  

    loading = true;

}

void ofApp::updatePtr() {

    if (movThread.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        movThread.lock();
 
        // copy image
        if (movPoint == 0) {
            playMov = movThread.playerThread;
        } else if (movPoint == 1) {
            playMov1 = movThread.playerThread;
        }

        // Unlock access
        movThread.unlock();

        if (playMov->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread.loaded = false;
            playMov->play();
        }

         if (playMov1->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread.loaded = false;
            playMov1->play();
        }


        loading = false;

    } 

}

