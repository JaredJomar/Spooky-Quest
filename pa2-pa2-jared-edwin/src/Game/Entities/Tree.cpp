#include "Tree.h"

Tree::Tree(int ox, int oy) : Entity(ox, oy, 120, 140)
{
    overworldSprite.load("images/entities/staticEntities/tree.png");
}

void Tree::inOverworldUpdate()
{
}

void Tree::inOverworldDraw()
{
    overworldSprite.draw(renderX, renderY, ow, oh);
}

ofRectangle Tree::getBounds()
{
    return ofRectangle(ox + 50, oy + 100, 20, 20);
}