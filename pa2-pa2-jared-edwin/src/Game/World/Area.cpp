#include "Area.h"

Area::Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Entity *> entities, Boss *boss, const Lambda &l) : lambda(l)
{
    this->nextArea = nextArea;
    areaImage.load(areaImagePath);
    areaMusic.load(areaMusicPath);
    areaStage.load(areaStagePath);
    this->entrancePosition = entrancePosition;
    this->enemies = enemies;
    // Code Added
    this->name = name;
    this->entities = entities;
    this->boss = boss;
}

void Area::resetEnemies()
{
    for (unsigned int i = 0; i < enemies.size(); i++)
        enemies.at(i)->revive();
}

int Area::getRemainingEnemies()
{
    int count = 0;
    for (unsigned int i = 0; i < enemies.size(); i++)
        if (!enemies.at(i)->isDead())
            count++;

    return count;
}
// Code Added
void Area::specialFunction(Player *p)
{
    lambda(p, enemies);
}
