#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		int  fileNumber();
		int  songNumber();

		ofxHapPlayer 	player1;
		ofxHapPlayer 	player2;
		ofxHapPlayer 	player3;
		ofxHapPlayer 	player4;

		ofTexture	 	movTexture;
		ofTexture	 *	movTexturePtr;

		ofxHapPlayer *	playMov1;
		ofxHapPlayer *	playMov2;
		ofxHapPlayer *	playMov3;
		ofxHapPlayer *	playMov4;

		ofxHapPlayer *	playMovRef;

		bool			bSendSerialMessage;			// a flag for sending serial
		char			bytesRead[3];				// data from serial, we will be trying to read 3
		char			bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
		int				nBytesRead;					// how much did we read?
		int				nTimesRead;					// how many times did we read?
		float			readTime;					// when did we last read?				
		
		ofSerial		serial;

		string 			serialData;

		int				clipNum;
		int				movNum;
		int				songNum;
		int 			w, h;
		int				numberMu;

		float 				* fftSmoothed;
		// we will draw a rectangle, bouncing off the wall:
		float 				px, py, vx, vy;

		int nBandsToGet;
		float prevx, prevy;

		ofSoundPlayer 		song;

		string musicLoad;
		
};
