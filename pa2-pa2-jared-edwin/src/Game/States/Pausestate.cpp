#include "PauseState.h"

PauseState::PauseState()
{
    pauseImage.load("images/ui/button_pause.png");
}

void PauseState::update()
{
}

void PauseState::draw()
{
    pauseImage.draw(ofGetWidth() / 2 - 150, ofGetHeight() / 2 - 100, 300, 200);
}

void PauseState::keyPressed(int key)
{
    if (key == OF_KEY_ESC)
    {
        pause = !pause;
    }
}

void PauseState::reset()
{
}
