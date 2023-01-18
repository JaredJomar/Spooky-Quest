#pragma once

#include "Animation.h"
#include "Entity.h"
#include "FightingProperties.h"

#define INIT_X 100
#define INIT_Y 100
#define INIT_BATTLE_X 64
#define INIT_BATTLE_Y 164
#define CENTER_X 288
#define CENTER_Y 208

#define OXDIMENSION 2688
#define OYDIMENSION 2560

class Player : public FightingProperties
{
private:
    Direction direction = Direction::up;
    int speed = 8;
    // Code Added
    int max_Health;
    bool walking = false;
    bool walk_Left, walk_Right, walk_Up, walk_Down = true;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    vector<char> pressedKeys;

public:
    Player(int health, int baseDamage);
    ~Player();
    void setwalk_Left(bool b) { walk_Left = b; }
    void setwalk_Right(bool b) { walk_Right = b; }
    void setwalk_Up(bool b) { walk_Up = b; }
    void setwalk_Down(bool b) { walk_Down = b; }
    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw();
    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
    // Code Added
    void health_Bar();
    int getmax_Health() { return max_Health; }
    void setSpeed(int num) { speed = num; }
    int getSpeed() { return speed; }
    ofRectangle getBounds(int ox, int oy);
    ofRectangle getBounds();
};