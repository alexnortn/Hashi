#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "MovThread.h"

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
		void exit();
		void loadMovie(string loadPath);
		void updatePtr();
		void movPlayer();
		int  fileNumber();

		ofVideoPlayer 	player;
		ofVideoPlayer 	player1;

		ofTexture		movTexture;

		ofVideoPlayer *	playMov;

		MovThread 		movThread;

		bool			loading;

		int				clipNum;
		int				movNum;
		int 			w, h;

		string			vidPath;
		
};
