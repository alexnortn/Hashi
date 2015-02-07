#include "ofApp.h"
#include "math.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Limit drawing to a sane rate
    ofSetVerticalSync(true);
    
    ofBackground(220, 220, 220);

    w = 1280;
    h = 800;

    movTexture.allocate(w, h, GL_RGB);
    movTexture.clear();
    movTexturePtr = &movTexture;

    player1.loadMovie("Japan.mov");
    player2.loadMovie("Mino.mov");
    player3.loadMovie("Tokyo.mov");
    player4.loadMovie("Washi.mov");

    // How many video files do we have?
    fileNumber();

    // How muchj music?
    songNumber();

    playMov1 = &player1;
    playMov2 = &player2;
    playMov3 = &player3;
    playMov4 = &player4;

    playMov1->play();
    playMov2->play();
    playMov3->play();
    playMov4->play();

    playMovRef = &player1;

    // player1.play();

    clipNum = 0;

    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    // serial.setup(0, baud); //open the first device
    serial.setup("COM3", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    memset(bytesReadString, 0, 4);

    // (1) write the letter "a" to serial:
    serial.writeByte('a');

    numberMu = ofRandom(0, (songNum-1));
    musicLoad = "music/music" + ofToString(numberMu) + ".mp3";
    song.loadSound(musicLoad);
    song.play();


    // the fft needs to be smoothed out, so we create an array of floats
    // for that purpose:
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    nBandsToGet = 128;

}

//--------------------------------------------------------------
void ofApp::update(){

    // update the sound playing system:
    ofSoundUpdate();
    song.setVolume(1.0);
    if (song.getPosition() > 0.9) {
        song.unloadSound();
        // (numberMu < songNum-1 ) ? numberMu++ : numberMu = 0;
        numberMu = ofRandom(0, (songNum-1));
        musicLoad = "music/music" + ofToString(numberMu) + ".mp3";
        song.loadSound(musicLoad);
        song.play();
    }



    // (5) grab the fft, and put in into a "smoothed" array,
    //      by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(nBandsToGet);      // request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }

    if (fftSmoothed[20] > 0.8f) if (playMovRef->isLoaded()) playMovRef->setPosition(ofRandom(0,1));



    // Signal the player to update
    // playMov1->update();
    // playMov2->update();
    // playMov3->update();
    // playMov4->update();

    nTimesRead = 0;
    nBytesRead = 0;
    int nRead  = 0;  // a temp variable to keep count per read
    
    if(serial.available()){  

        unsigned char bytesReturned[3];
        
        memset(bytesReadString, 0, 4);
        memset(bytesReturned, 0, 3);
        
        // if ( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
        //  nTimesRead++;   
        //  nBytesRead = nRead;
        // };

        serial.readBytes(bytesReturned, 3);
        serialData = (char*) bytesReturned;

        if (bytesReturned > 0)  serial.writeByte('a');

        if (bytesReturned > 0)  cout << "bytesReturned" << endl;
        if (bytesReturned > 0)  cout << serialData << endl;

        if ((bytesReturned > 0) && (serialData == "W")) cout << "Message Recieved!! W That was our letter!!" << endl; 
        if ((bytesReturned > 0) && (serialData == "M")) cout << "Message Recieved!! M That was our letter!!" << endl; 
        if ((bytesReturned > 0) && (serialData == "T")) cout << "Message Recieved!! T That was our letter!!" << endl; 
        if ((bytesReturned > 0) && (serialData == "J")) cout << "Message Recieved!! O That was our letter!!" << endl; 

        
        memcpy(bytesReadString, bytesReturned, 3);

    }


    if (serialData == "T") {
        
        playMovRef = &player1;
        if (playMovRef->isLoaded()) playMovRef->setPosition(ofRandom(0,1));

        // playMov2->stop();
        // playMov3->stop();
        // playMov4->stop();

    }

    if (serialData == "J") {

        playMovRef = &player2;
        if (playMovRef->isLoaded()) playMovRef->setPosition(ofRandom(0,1));

        // playMov1->stop();
        // playMov3->stop();
        // playMov4->stop();

    }

    if (serialData == "M") {

        playMovRef = &player3;
        if (playMovRef->isLoaded()) playMovRef->setPosition(ofRandom(0,1));

        // playMov1->stop();
        // playMov2->stop();
        // playMov4->stop();

    }

    if (serialData == "W") {

        playMovRef = &player4;
        if (playMovRef->isLoaded()) playMovRef->setPosition(ofRandom(0,1));

        // playMov1->stop();
        // playMov3->stop();
        // playMov2->stop();

    }

    if(playMovRef->isLoaded()) {
        playMovRef->play();
        playMovRef->setVolume(0.0f);
        playMovRef->update();
    }

    if (playMovRef->isFrameNew()) {
        movTexturePtr = playMovRef->getTexture();
        // cout << "New Frame" << endl;
    }


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255);

    // movTexturePtr->draw(20,20,w,h);

    ofShader *shader = playMovRef->getShader();
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

    if (key == '1') serialData = "T";
    if (key == '2') serialData = "J";
    if (key == '3') serialData = "M";
    if (key == '4') serialData = "W";

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

    if (playMovRef->isLoaded()) playMovRef->setPosition(position);


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

int ofApp::songNumber() {
    //some path, may be absolute or relative to bin/data
    string path = "music/"; 
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("mp3");
    //populate the directory object
    dir.listDir();

    songNum = dir.numFiles();
    cout << "There are " + ofToString(songNum) + " Mov files in your Bin \n" << endl;

    return songNum;
}