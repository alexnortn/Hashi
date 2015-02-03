
#include "ofMain.h"

class MovThread : public ofThread {

    public:

    // Publically available variables n shit
    MovThread() {
        loaded = false;
        i = 0;
        // playerThread.setUseTexture(false);
        // playerThread1.setUseTexture(false);
        // playerThread2.setUseTexture(false);
    }

    void load(string movPath) {
        mutex.lock();
        path = movPath;

        if (i % 3 == 0) {
            playerThreadPtr = &playerThread;
            cout << "playerThread" << endl;
        } else if (i % 3 == 1) {
            playerThreadPtr = &playerThread1;
            cout << "playerThread1" << endl;
        } else if (i % 3 == 2) {
            playerThreadPtr = &playerThread2;
            cout << "playerThread2" << endl;
        }

        // Empty old player object
        if (playerThreadPtr->isLoaded()) {
            playerThreadPtr->stop();
            playerThreadPtr->close();
            loaded = false;
        }

        condition.signal();
        mutex.unlock();
    }

    void killThread() {
        stopThread();
        cout << "The Thread is Dead!!!" << endl;
    }
 
    // the thread function
    void MovThread::threadedFunction() {
 
        // start
 
        while(isThreadRunning()) {
 
            // lock access to the resource
            mutex.lock();

                cout << "Thread is on! like Usher" << endl;
                // Load next file into memory
                playerThreadPtr->loadMovie(path);
                if (playerThreadPtr->isLoaded()) {
                    cout << "We Made it Here Video Loaded!!!" << endl;
                    loaded = true;
                    playerThread.play();
                    i++;
                    condition.wait(mutex);
                }
            // done with the resource
            unlock();
        }
    }


 
    ofxHapPlayer    playerThread;
    ofxHapPlayer    playerThread1;
    ofxHapPlayer    playerThread2;

    ofxHapPlayer *    playerThreadPtr;

    string          path;

    int             i;

    bool            loaded;

    private:

    Poco::Condition condition;

};