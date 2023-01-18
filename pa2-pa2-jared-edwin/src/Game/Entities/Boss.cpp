#include "Boss.h"

Boss::Boss(string id, int health, int baseDamage, string entityName, int ox, int oy) : Enemy(id, health, baseDamage, entityName, ox, oy){
    ow = 100;
    oh = 128;
}

