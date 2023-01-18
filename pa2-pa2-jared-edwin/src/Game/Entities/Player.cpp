#include "Player.h"
// Code Added
Player::Player(int health, int baseDamage) : FightingProperties(INIT_X, INIT_Y, 64, 64, 64, 164, 192, 192, health, baseDamage)
{
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> fightingFrames;
    ofImage temp;
    // Code Added
    max_Health = health;

    for (int i = 1; i < 5; i++)
    {
        temp.load("images/entities/player/downframes/player-ow-front" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/player/upframes/player-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/player/leftframes/player-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/player/rightframes/player-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }

    temp.load("images/entities/player/fightingframes/player-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/player/fightingframes/player-f2.png");
    fightingFrames.push_back(temp);

    walkDown = new Animation(5, downFrames);
    walkUp = new Animation(5, upFrames);
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    fighting = new Animation(7, fightingFrames);
}

void Player::inOverworldUpdate()
{
    if (!pressedKeys.empty())
    {
        switch (pressedKeys[0])
        {
        case 'a':
            direction = Direction::left;
            if (this->ox - speed >= CENTER_X)
                // Code Added
                if (walk_Left)
                    this->ox -= speed;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case 'd':
            direction = Direction::right;
            if (this->ox + speed <= OXDIMENSION - CENTER_X)
                // Code Added
                if (walk_Right)
                    this->ox += speed;
            // Code Added
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case 'w':
            direction = Direction::up;
            if (this->oy - speed >= CENTER_Y)
                // Code Added
                if (walk_Up)
                    this->oy -= speed;
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();

            break;
        case 's':
            direction = Direction::down;
            if (this->oy + speed <= OYDIMENSION - CENTER_Y)
                // Code Added
                if (walk_Down)
                    this->oy += speed;
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
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
            break;
        case Direction::up:
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            overworldSprite = walkDown->getCurrentFrame();
            break;
        }
    }
}

void Player::fightingUpdate()
{
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();
}

void Player::inOverworldDraw()
{
    overworldSprite.draw(CENTER_X, CENTER_Y, ow, oh);
}

// Code Added
ofRectangle Player::getBounds(int ox, int oy)
{
    return ofRectangle(ox, oy + 32, ow, oh - 32);
}
// Code Added
ofRectangle Player::getBounds()
{
    return ofRectangle(ox, oy, ow, oh);
}

void Player::health_Bar()
{
    ofImage healthbar;
    healthbar.load("images/ui/healthbar.png");
    healthbar.draw(5, ofGetHeight() - 120, 192, 192);

    for (int i = 0; i < 3; i++)
    {
        double playerHealthRatio = (double)health / (double)max_Health;
        if (playerHealthRatio < 0)
            playerHealthRatio = 0;
        else if (playerHealthRatio < 0.33)
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        else if (playerHealthRatio < 0.66)
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        else
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);

        ofDrawRectangle(49, ofGetHeight() - 120 + 88 + i * 4, (int)(36 * playerHealthRatio) * 4, 4);
    }
    ofFill();
    ofSetColor(255, 255, 255);
}

void Player::keyPressed(int key)
{
    if (key == 'w' || key == 'a' || key == 's' || key == 'd')
        if (find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end())
            pressedKeys.push_back(key);
}

void Player::keyReleased(int key)
{
    if (key == 'w' || key == 'a' || key == 's' || key == 'd')
    {
        vector<char>::iterator pos = find(pressedKeys.begin(), pressedKeys.end(), key);
        if (pos != pressedKeys.end())
            pressedKeys.erase(pos);
    }
}

void Player::reset()
{
    ox = INIT_X;
    oy = INIT_Y;
    fx = INIT_X;
    fy = INIT_Y;
}

Player::~Player()
{
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}