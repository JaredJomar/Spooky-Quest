#include "OverworldState.h"
#include "Friend.h"
OverworldState::OverworldState(Player *player, Area *area)
{
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
}

void OverworldState::loadArea(Area *area)
{
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}
// Code Added
vector<Entity *> OverworldState::renderOrderChanger()
{
    vector<Entity *> v;
    vector<Entity *> copy = area->getEntities();
    vector<Entity *>::iterator it = copy.begin();
    while (it != copy.end())
    {
        if (dynamic_cast<Tree *>(*it) != NULL && player->getOY() >= (*it)->getOY() + 50)
        {
            v.push_back(*it);
            copy.erase(it);
        }
        else
        {
            it++;
        }
    }

    v.push_back(player);

    for (Entity *e : copy)
        v.push_back(e);
    return v;
}

void OverworldState::ifCollisions()
{
    // Code Added
    area->specialFunction(player);
    player->inOverworldUpdate();
    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            area->getEnemies().at(i)->inOverworldUpdate();
            if (player->collides(area->getEnemies().at(i)))
            {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
                break;
            }
        }
    }

    // Code Added
    for (Entity *e : area->getEntities())
    {
        if (dynamic_cast<Tree *>(e) != NULL)
            dynamic_cast<Tree *>(e)->inOverworldUpdate();
        if (dynamic_cast<Friend *>(e) != NULL)
            dynamic_cast<Friend *>(e)->inOverworldUpdate();
    }

    player->setwalk_Left(true);
    player->setwalk_Right(true);
    player->setwalk_Up(true);
    player->setwalk_Down(true);
    for (unsigned int i = 0; i < area->getEntities().size(); i++)
    {
        if (area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX() - player->getSpeed(), player->getOY())))
        {
            player->setwalk_Left(false);
        }
        if (area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX() + player->getSpeed(), player->getOY())))
        {
            player->setwalk_Right(false);
        }
        if (area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX(), player->getOY() - player->getSpeed())))
        {
            player->setwalk_Up(false);
        }
        if (area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX(), player->getOY() + player->getSpeed())))
        {
            player->setwalk_Down(false);
        }
        // Code Added
        if (dynamic_cast<Friend *>(area->getEntities().at(i)) != NULL && area->getEntities().at(i)->getBounds().intersects(player->getBounds()))
        {
            if (dynamic_cast<Friend *>(area->getEntities().at(i))->getDirection() == Direction::downLeft)
            {
                player->setOX(player->getOX() - (dynamic_cast<Friend *>(area->getEntities().at(i))->getSpeed() / 2));
                player->setOY(player->getOY() + (dynamic_cast<Friend *>(area->getEntities().at(i))->getSpeed() / 2));
            }
            if (dynamic_cast<Friend *>(area->getEntities().at(i))->getDirection() == Direction::right)
            {
                player->setOX(player->getOX() + (dynamic_cast<Friend *>(area->getEntities().at(i))->getSpeed()));
            }
            if (dynamic_cast<Friend *>(area->getEntities().at(i))->getDirection() == Direction::upLeft)
            {
                player->setOX(player->getOX() - (dynamic_cast<Friend *>(area->getEntities().at(i))->getSpeed() / 2));
                player->setOY(player->getOY() - (dynamic_cast<Friend *>(area->getEntities().at(i))->getSpeed() / 2));
            }
        }
    }
}

void OverworldState::update()
{
    area->specialFunction(player);
    player->inOverworldUpdate();
    ifCollisions();
    camera->update();
}

void OverworldState::draw()
{
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->inOverworldDraw();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->inOverworldDraw();
        }
    }
    // Code Added
    for (Entity *e : renderOrderChanger())
    {
        if (dynamic_cast<Tree *>(e) != NULL)
        {
            int playerDistanceX = e->getOX() - camera->getPlayerX();
            int playerDistanceY = e->getOY() - camera->getPlayerY();
            e->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            e->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            dynamic_cast<Tree *>(e)->inOverworldDraw();
            continue;
        }
        // Code Added
        if (dynamic_cast<Friend *>(e) != NULL)
        {
            int playerDistanceX = e->getOX() - camera->getPlayerX();
            int playerDistanceY = e->getOY() - camera->getPlayerY();
            e->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            e->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            dynamic_cast<Friend *>(e)->inOverworldDraw();
            continue;
        }
        e->inOverworldDraw();
    }

    drawHud();
}

void OverworldState::drawHud()
{
    player->health_Bar();
    ofDrawBitmapString(area->getName() + "  Enemies: " + ofToString(area->getRemainingEnemies()), 60, 440);
}

void OverworldState::keyPressed(int key)
{
    player->keyPressed(key);
    // Code Added
    if (key == 'r')
        area->resetEnemies();
    // Code Added
    if (key == 'e')
    {
        for (unsigned int i = 0; i < area->getEntities().size(); i++)
        {
            if (dynamic_cast<Friend *>(area->getEntities().at(i)) != NULL)
            {
                if (area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX() - player->getSpeed(), player->getOY())) ||
                    area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX() + player->getSpeed(), player->getOY())) ||
                    area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX(), player->getOY() - player->getSpeed())) ||
                    area->getEntities().at(i)->getBounds().intersects(player->getBounds(player->getOX(), player->getOY() + player->getSpeed())))
                {
                    dynamic_cast<Friend *>(area->getEntities().at(i))->setInteracting(!dynamic_cast<Friend *>(area->getEntities().at(i))->getInteracting());
                }
            }
        }
    }
}

void OverworldState::keyReleased(int key)
{
    player->keyReleased(key);
}

void OverworldState::reset()
{
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}