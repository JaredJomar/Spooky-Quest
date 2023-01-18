#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Tree.h"

class Tree : public Entity
{
private:
public:
    Tree(int ox, int oy);
    void inOverworldUpdate();
    void inOverworldDraw();
    ofRectangle getBounds();
};