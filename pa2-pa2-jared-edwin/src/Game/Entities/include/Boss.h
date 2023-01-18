#pragma once
#include "ofMain.h"
#include "Enemy.h"

class Boss : public Enemy{
    private:
        int timesDefeated = 0;
    public:
        Boss(string id, int health, int baseDamage, string entityName, int ox, int oy);
        int getTimesDefeated(){return timesDefeated;}
        void setTimesDefeated(int num){timesDefeated = num;}
};