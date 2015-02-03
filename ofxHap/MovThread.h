
#include "ofMain.h"

class MovThread : public ofThread {

    public:

    // Publically available variables n shit
    MovThread() {
        loaded = false;
        // playerThread.setUseTexture(false);
    }

    void load(string movPath) {
        lock();
        path = movPath;

        // Empty old player object
        if (playerThread.isLoaded()) {
            playerThread.stop();
            playerThread.close();
            loaded = false;
        }

        unlock();
        condition.signal();
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
            lock();

                cout << "Thread is on! like Usher" << endl;
                // Load next file into memory
                playerThread.loadMovie(path);
                if (playerThread.isLoaded()) {
                    cout << "We Made it Here Video Loaded!!!" << endl;
                    loaded = true;
                    playerThread.play();
                    condition.wait(mutex);
                }
            // done with the resource
            unlock();
        }
    }

 
    ofxHapPlayer   playerThread;

    string          path;

    bool            loaded;

    private:

    Poco::Condition condition;

};