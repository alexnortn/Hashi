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
    movTexture.clear();
    movTexturePtr = &movTexture;

    // start the MovThread
    // movThread.startThread();    // blocking, non-verbose
    // movThread.load("movies1/Washi-18.mov");

    player.loadMovie("movies4/Washi-1.mov");

    loading = false;

    // How many video files do we have?
    fileNumber();

    playMov = &player;
    playMov1 = &player1;

    player.play();
    player1.play();

    clipNum = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

    // Signal the player to update
    playMov->update();
    playMov1->update();
    // player1.update();

    if (loading) updatePtr();

    movTexturePtr = playMov->getTexture();

    // movThread.lock();
    // movTexturePtr = playMov->getTexture();
    // movThread.unlock();


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255);

    // movTexturePtr->draw(20,20,w,h);

    ofShader *shader = player.getShader();
    // the result of getShader() will be NULL if the movie is not Hap Q
    if (shader)
    {
        cout << "NOT NULL" << endl;
        shader->begin();
    }
    movTexturePtr->draw(0,0,w,h);
    if (shader)
    {
        shader->end();
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

    if (player.isLoaded()) player.setPosition(position);
    if (player1.isLoaded()) player1.setPosition(position);

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

void ofApp::exit() {
 
    // stop the thread
    // movThread.stopThread();

}

void ofApp::movPlayer() {

    // Which file to load?
    string movCurrentPlus = ofToString(clipNum);
    vidPath = "movies1/Washi-" + movCurrentPlus + ".mov";

    if (playMov->isPlaying()) playMov->stop();

    loadMovie(vidPath);

    string movLength = ofToString(floor(playMov->getDuration()));
    string movName = playMov->getMoviePath();

    cout << movName + " is " + movLength + " seconds long" << endl;


}

void ofApp::loadMovie(string loadPath) {

    // movThread.loaded = false;

    // Unload previous video object
    if (playMov->isLoaded()) {
        playMov->close();
        cout << "appSide unloading our <player>" << endl;
    }

    // movThread.load(loadPath);  

    loading = true;

}

void ofApp::updatePtr() {

    if (movThread.loaded == true) {

        cout << "appSide feels the loaded video" << endl;

        // lock access to the resource
        // movThread.lock();

        // *playMov = movThread.playerThread;

        // Unlock access
        // movThread.unlock();

        if (playMov->isLoaded()) {
            cout << "Yo <player appSide> is totally loaded!!!" << endl;
            playMov->play();
        }

        loading = false;
    
    }

}
