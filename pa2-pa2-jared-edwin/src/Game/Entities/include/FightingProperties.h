#pragma once
#include "ofMain.h"
#include "Entity.h"

class FightingProperties : public Entity{
    protected:
        double health;
        int baseDamage;
        int fx, fy, fw, fh; // Fighting coordinates and dimensions
        ofImage fightingSprite;
    public:
        FightingProperties(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, double health, int baseDamage);
        double getHealth() { return health; };
        void setHealth(double health) { this->health = health; };
        int getDmg() { return baseDamage; };
        void setDmg(int baseDamage) { this->baseDamage = baseDamage; };
        virtual void fightingUpdate() = 0;
        virtual void fightingDraw();
};