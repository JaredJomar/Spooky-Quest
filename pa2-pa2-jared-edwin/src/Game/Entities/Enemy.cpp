#include "Enemy.h"

Enemy::Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy) : FightingProperties(ox, oy, 50, 64, 420, 220, 97, 125, health, baseDamage)
{
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    max_Health = health;
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    ofImage sprite;
    ofImage temp;

    sprite.load("images/entities/enemy/sprite.png");

    int w = 48, h = 48;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            temp.cropFrom(sprite, 6 + w * i, 192 + h * j, w - 12, h);
            if (j == 0)
                downFrames.push_back(temp);
            else if (j == 1)
                leftFrames.push_back(temp);
            else if (j == 2)
                rightFrames.push_back(temp);
            else
                upFrames.push_back(temp);
        }
    }
    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
    fighting = new Animation(7, leftFrames);

    direction = Direction::right;
}
// Code Added
void Enemy::inOverworldUpdate()
{
    if (moveTimer == 60)
    {
        walking = true;
        switch (direction)
        {
        case Direction::right:
            direction = Direction::upLeft;
            break;
        case Direction::upLeft:
            direction = Direction::downLeft;
            break;
        case Direction::downLeft:
            direction = Direction::right;
            break;
        }
    }
    if (moveTimer == 45)
    {
        walking = false;
    }
    moveTimer--;
    if (moveTimer == 0)
        moveTimer = 60;

    if (walking)
    {
        switch (direction)
        {
        case Direction::left:
            this->ox -= speed;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += speed;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::upLeft:
            this->ox -= speed / 2;
            this->oy -= speed / 2;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upRight:
            this->ox += speed / 2;
            this->oy -= speed / 2;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::downLeft:
            this->ox -= speed / 2;
            this->oy += speed / 2;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::downRight:
            this->ox += speed / 2;
            this->oy += speed / 2;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        }
    }
    else
    {
        switch (direction)
        {
        case Direction::left:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            overworldSprite = walkRight->getCurrentFrame();
            ;
            break;
        case Direction::up:
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::upLeft:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upRight:
            overworldSprite = walkRight->getCurrentFrame();
            ;
            break;
        case Direction::downLeft:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::downRight:
            overworldSprite = walkRight->getCurrentFrame();
            break;
        }
    }
}

void Enemy::inOverworldDraw()
{
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Enemy::fightingUpdate()
{
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();
}

void Enemy::reset()
{
}

Enemy::~Enemy()
{
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete fighting;
}