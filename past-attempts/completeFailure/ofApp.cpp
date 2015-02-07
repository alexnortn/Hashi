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

    // start the MovThread
    movThread.startThread();    // blocking, non-verbose
    movThread1.startThread();    // blocking, non-verbose

    // movThread.load("movies3/Mino.Town-1.mov");
    // movThread1.load("movies3/Mino.Town-1.mov");

    // player1.loadMovie("movies/Washi-18.mov");

    loading = false;
    loading1 = false;

    // Load a movie file
    player.loadMovie("movies3/Mino.Town-1.mov");
    player1.loadMovie("movies3/Mino.Town-1.mov");

    // How many video files do we have?
    fileNumber();

    // Give our pointer something to get started with
    playMov  = &player;
    playMov1 = &player1;

    // Start playing the movies
    playMov->play();
    playMov1->play();

    clipNum = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

	if (loading) updatePtr();
    if (loading1) updatePtr1();

	if (playMov->isLoaded()) {
		playMov->update();
		movThread.lock();
		movTexture.loadData(playMov->getPixelsRef());
		movThread.unlock();
	}

	if (playMov1->isLoaded()) {
		playMov1->update();
		movThread1.lock();
		movTexture1.loadData(playMov1->getPixelsRef());
		movThread1.unlock();
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
    string path = "movies3/"; 
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
    movThread1.stopThread();

}

void ofApp::movPlayer() {

    // Which file to load?
    string movCurrentPlus = ofToString(clipNum);
    vidPath = "movies3/Mino.Town-" + movCurrentPlus + ".mov";

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
        // Unload previous video object
        if (player.isLoaded()) {
            player.close();
            movThread.load(loadPath);  
            cout << "appSide unloading our <player>" << endl;
            loading = true;
        }
        
        cout << "appSide movPoint = 0 :: playMoveRef = &player" << endl;
    } else if (movPointer == 1) {
        if (player1.isLoaded()) {
            player1.close();
            movThread1.load(loadPath);  
            cout << "appSide unloading our <player>" << endl;
            loading1 = true;
        }
    }        

}

void ofApp::updatePtr() {

    if (movThread.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        movThread.lock();

        *playMov = movThread.playerThread;

        // Unlock access
        movThread.unlock();

        if (playMov->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread.loaded = false;
            playMov->play();
        }

        loading = false;

    } 

    if (movThread1.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        movThread1.lock();
 
        // copy image
        *playMov1 = movThread1.playerThread;

        // Unlock access
        movThread1.unlock();

       if (playMov1->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread1.loaded = false;
            playMov1->play();
        }

        loading1 = false;

    } 

}

void ofApp::updatePtr1() {

    if (movThread1.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        movThread1.lock();
 
        // copy image
        *playMov1 = movThread1.playerThread;

        // Unlock access
        movThread1.unlock();

       if (playMov1->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            movThread1.loaded = false;
            playMov1->play();
        }

        loading1 = false;

    } 

}
