#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Animation.h"

class Friend : public Entity{
    private:
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        Direction direction;
        int speed = 8;
        bool walking = false;
        int moveTimer;
        string entityName;
        string id;
        bool interacting = false;
        ofImage interactingImage;
    public:
        Friend(int ox, int oy, int ow, int oh);
        void inOverworldUpdate();
        void inOverworldDraw();
        Direction getDirection(){return direction;}
        void setSpeed(int num){speed = num;}
        int getSpeed(){return speed;}
        void setInteracting(bool b){interacting = b;}
        bool getInteracting(){return interacting;}
};