#include "Friend.h"

Friend::Friend(int ox, int oy, int ow, int oh) : Entity(ox, oy, ow, oh)
{
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    ofImage sprite;
    ofImage temp;
    moveTimer = 60;
    interactingImage.load("images/ui/speechBalloon.png");
    sprite.load("images/entities/Friend/sprite.png");

    int w = 48, h = 48;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            temp.cropFrom(sprite, 6 + w * i, 192 + h * j, w - 12, h);
            if (j == 0)
                downFrames.push_back(temp);
            else if (j == 1)
                leftFrames.push_back(temp);
            else if (j == 2)
                rightFrames.push_back(temp);
            else
                upFrames.push_back(temp);
        }
    }
    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);

    direction = Direction::right;
}

void Friend::inOverworldUpdate()
{
    if (moveTimer == 60)
    {
        walking = true;
        switch (direction)
        {
        case Direction::right:
            direction = Direction::upLeft;
            break;
        case Direction::upLeft:
            direction = Direction::downLeft;
            break;
        case Direction::downLeft:
            direction = Direction::right;
            break;
        }
    }
    if (moveTimer == 45)
    {
        walking = false;
    }
    moveTimer--;
    if (moveTimer == 0)
        moveTimer = 60;

    if (walking)
    {
        switch (direction)
        {
        case Direction::left:
            this->ox -= speed;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += speed;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::upLeft:
            this->ox -= speed / 2;
            this->oy -= speed / 2;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upRight:
            this->ox += speed / 2;
            this->oy -= speed / 2;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::downLeft:
            this->ox -= speed / 2;
            this->oy += speed / 2;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::downRight:
            this->ox += speed / 2;
            this->oy += speed / 2;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        }
    }
    else
    {
        switch (direction)
        {
        case Direction::left:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            overworldSprite = walkRight->getCurrentFrame();
            ;
            break;
        case Direction::up:
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::upLeft:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upRight:
            overworldSprite = walkRight->getCurrentFrame();
            ;
            break;
        case Direction::downLeft:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::downRight:
            overworldSprite = walkRight->getCurrentFrame();
            break;
        }
    }
}

void Friend::inOverworldDraw()
{
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
    if (interacting)
        interactingImage.draw(renderX + 30, renderY - 30, 40, 40);
}
