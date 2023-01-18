#pragma once

#include "Animation.h"
#include "State.h"

class PauseState : public State {
   private:
    ofImage pauseImage;
    bool pause = false;

   public:
    PauseState();
    void update();
    void draw();
    void keyPressed(int key);
    void reset();
    bool isPause(){return pause;}
};