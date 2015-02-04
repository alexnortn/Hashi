
#include "ofMain.h"

class MovThread : public ofThread {

    public:

    // Publically available variables n shit
    MovThread() {
        loaded = false;
        playerThread.setUseTexture(false);
    }

    void load(string movPath) {
        mutex.lock();
        path = movPath;
        count = path.length();

        // Empty old player object
        if (playerThread.isLoaded()) {
            playerThread.stop();
            playerThread.close();
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
                if(count > 0) {
                    playerThread.loadMovie(path);
                    if (playerThread.isLoaded()) {
                        cout << "We Made it Here Video Loaded!!!" << endl;
                        loaded = true;
                        playerThread.play();
                        condition.wait(mutex);
                    }
                }
            // done with the resource
            unlock();
        }
    }


 
    ofVideoPlayer    playerThread;

    string          path;

    int             count;

    bool            loaded;

    private:

    Poco::Condition condition;

};