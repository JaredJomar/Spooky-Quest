#pragma once

#include "Animation.h"
#include "Entity.h"
#include "FightingProperties.h"

class Enemy : public FightingProperties
{
protected:
    Direction direction;
    int speed = 8;
    bool walking = false;
    int max_Health;
    int renderX = 1000;
    int renderY = 1000;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    string id;
    int moveTimer;
    bool dead = false;
    string entityName;
    ofImage sprite;

public:
    Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy);
    ~Enemy();
    int getOX() { return ox; };
    int getOY() { return oy; };
    bool isDead() { return dead; };
    void kill() { this->dead = true; };
    void revive() { this->dead = false; };
    void setRenderX(int x) { renderX = x; };
    void setRenderY(int y) { renderY = y; };
    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw();
    void reset();
    string getId() { return id; };
    ofImage getSprite() { return overworldSprite; };
    // Code Added
    void setSpeed(int num) { speed = num; }
    int getSpeed() { return speed; }
    int getmax_Health() { return max_Health; }
};