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
		void loadMovie(int movPointer, string loadPath);
		void updatePtr();
		void movPlayer();
		int  fileNumber();

        ofVideoPlayer 	*	playMov;
        ofVideoPlayer 	*	playMov1;

		ofTexture		movTexture;
		ofTexture		movTexture1;

		MovThread 		movThread;

		bool			loading;

		int				clipNum;
		int				movNum;
		int 			w, h;
		int     		movPoint;

        float 			alpha;
        float   		alpha1;

		string			vidPath;
		
};
