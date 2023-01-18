#pragma once

#include "ofMain.h"
// Code Added
enum Direction
{
    left,
    right,
    up,
    down,
    upLeft,
    upRight,
    downRight,
    downLeft
};

class Entity
{
protected:
    int ox, oy, ow, oh; // Overworld Coordinates and dimensions
    ofImage fightingSprite;
    ofImage overworldSprite;
    // Code Added
    int renderX = 1000;
    int renderY = 1000;

public:
    Entity(int ox, int oy, int ow, int oh);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw();
    int getOX() { return ox; };
    int getOY() { return oy; };
    int getOW() { return ow; };
    int getOH() { return oh; };
    virtual ofRectangle getBounds();
    virtual ofRectangle getBounds(int ox, int oy);
    bool collides(Entity *entity);
    void setOX(int ox) { this->ox = ox; };
    void setOY(int oy) { this->oy = oy; };
    // Code Added
    void setRenderX(int x) { renderX = x; };
    void setRenderY(int y) { renderY = y; };
};