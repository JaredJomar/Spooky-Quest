#pragma once

#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "Boss.h"

class Area
{
private:
    // Code Added
    using Lambda = std::function<void(Player *, std::vector<Enemy *>)>;
    Lambda lambda;
    string name;
    ofImage areaImage;
    ofSoundPlayer areaMusic;
    ofImage areaStage;
    ofPoint entrancePosition;
    std::vector<Enemy *> enemies;
    // Code Added
    std::vector<Entity *> entities;
    Area *nextArea;
    Boss *boss;

public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Entity *> entities, Boss *boss, const Lambda &l);
    void resetEnemies();
    string getName() { return name; }
    ofImage getImage() { return areaImage; }
    ofSoundPlayer getMusic() { return areaMusic; }
    ofImage getStage() { return areaStage; }
    ofPoint getEntrancePos() { return entrancePosition; }
    vector<Enemy *> getEnemies() { return enemies; }
    // Code Added
    vector<Entity *> getEntities() { return entities; }
    int getRemainingEnemies();
    Area *getNextArea() { return nextArea; }
    void setName(string name) { this->name = name; }
    void setEnemies(std::vector<Enemy *> enemies) { this->enemies = enemies; }
    // Code Added
    void specialFunction(Player *p);
    Boss *getBoss() { return boss; }
    void spawnBoss() { enemies.push_back(boss); }
};