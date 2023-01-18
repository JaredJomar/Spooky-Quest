#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    initAreas();
    // Declaration and Initialization of States
    player = new Player(100.0, 6);
    titleState = new TitleState();
    overworldState = new OverworldState(player, currentArea);
    battleState = new BattleState(player, currentArea);
    winState = new WinState();
    endGameState = new EndGameState();
    // Code Added
    pauseState = new PauseState();

    // Initial State
    currentState = titleState;
}

//--------------------------------------------------------------
void ofApp::initAreas()
{
    /**
     * @brief
     * each area is 672 pixels wide al;p.[]..l;nd 640 pixels high,
     * with 10 and 8 pixels of space between the player and the edge of the map respectively
     * each in-game pixel is 4 * 1 screen pixel
     */
    // Code Added
    Player *p = player;

    vector<Enemy *> enemies2;
    ofPoint entrancePosition2(4 * 110, 4 * 116);
    Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
    Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
    Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
    Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
    Enemy *area2Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
    Enemy *area2Enemy6 = new Enemy("26", 30, 6, "enemy2", 4 * 194, 4 * 532);
    // Code Added
    Boss *boss2 = new Boss("27", 30, 6, "enemy2", 4 * 194, 4 * 532 + 200);
    enemies2.push_back(area2Enemy1);
    enemies2.push_back(area2Enemy2);
    enemies2.push_back(area2Enemy3);
    enemies2.push_back(area2Enemy4);
    enemies2.push_back(area2Enemy5);
    enemies2.push_back(area2Enemy6);
    // Code Added
    area2 = new Area("Area2", NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2, {}, boss2,
                     [](Player *p, std::vector<Enemy *> e) {

                     });

    vector<Enemy *> enemies3;
    ofPoint entrancePosition3(4 * 414, 4 * 566);
    Enemy *specialAreaEnemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
    Enemy *specialAreaEnemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
    Enemy *specialAreaEnemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178);
    // Code Added
    Boss *bossSpecialArea = new Boss("14", 20, 4, "enemy1", 4 * 420, 4 * 178 + 200);
    enemies3.push_back(specialAreaEnemy1);
    enemies3.push_back(specialAreaEnemy2);
    enemies3.push_back(specialAreaEnemy3);
    specialArea = new Area("Grass Type", area2, "images/areas/specialArea.png", "audio/The_Witcher_Burn_Butcher_Burn_Piano.wav", "images/stages/stage1.png", entrancePosition3, enemies3, {}, bossSpecialArea,
                           [](Player *p, std::vector<Enemy *> e)
                           {
                               if (p->getHealth() < p->getmax_Health() && int(ofGetElapsedTimef()) % 5 == 0)
                               {
                                   p->setHealth(p->getHealth() + .15);
                               }
                           });

    vector<Enemy *> enemies1;
    ofPoint entrancePosition1(4 * 414, 4 * 566);
    // Code Added
    Enemy *area1Enemy1 = new Enemy("1", 20, 4, "enemy1", 4 * 480, 4 * 432);
    Enemy *area1Enemy2 = new Enemy("2", 20, 4, "enemy1", 4 * 225, 4 * 178);
    Enemy *area1Enemy3 = new Enemy("3", 20, 4, "enemy1", 4 * 420, 4 * 178);
    // Code Added
    Boss *boss1 = new Boss("4", 20, 4, "boss1", 4 * 420, 4 * 178 + 200);
    vector<Entity *> entities1;
    Tree *tree1 = new Tree(4 * 480, 4 * 432);
    Tree *tree2 = new Tree(4 * 225, 4 * 178);
    Tree *tree3 = new Tree(4 * 420, 4 * 178);
    // Code Added
    Friend *friend1 = new Friend(4 * 480 - 400, 4 * 432, 64, 64);
    entities1.push_back(tree1);
    entities1.push_back(tree2);
    entities1.push_back(tree3);
    entities1.push_back(friend1);
    // Code Added
    enemies1.push_back(area1Enemy1);
    enemies1.push_back(area1Enemy2);
    enemies1.push_back(area1Enemy3);
    // Code Added
    area1 = new Area("Area1", specialArea, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, entities1, boss1,
                     [](Player *p, std::vector<Enemy *> e) {

                     });
    currentArea = area1;
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Code Added
    if (!pauseState->isPause())
        currentState->update();
    if (currentState->hasFinished())
    {
        currentState->toggleMusic();
        if (currentState->getNextState() == "Title")
        {
            endGameState->setWin(false);
            area1->resetEnemies();
            area2->resetEnemies();
            currentArea = area1;
            battleState->reset();
            battleState->setStage(currentArea->getStage());
            overworldState->loadArea(currentArea);
            currentState = titleState;
        }
        else if (currentState->getNextState() == "Overworld")
        {
            currentState = overworldState;
        }
        else if (currentState->getNextState() == "Battle")
        {
            battleState->startBattle(overworldState->getEnemy());
            currentState = battleState;
        }
        else if (currentState->getNextState() == "Win")
        {
            overworldState->getEnemy()->kill();
            if (currentArea->getRemainingEnemies() == 0 || currentArea->getBoss()->isDead())
            {
                if (!currentArea->getBoss()->isDead())
                {
                    currentArea->spawnBoss();
                    currentState = winState;
                }
                else if (currentArea->getNextArea() == NULL)
                {
                    endGameState->setWin(true);
                    currentState = endGameState;
                }
                else
                {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            }
            else
            {
                currentState = winState;
            }
        }
        else if (currentState->getNextState() == "End")
        {
            currentState = endGameState;
            player->reset();
        }
        currentState->toggleMusic();
        currentState->reset();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    currentState->draw();
    // Code Added
    if (pauseState->isPause())
        pauseState->draw();
    // Code Added
    ofDrawBitmapString(mouseX, 20, 20);
    ofDrawBitmapString(mouseY, 50, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // Code Added
    if (currentState == battleState)
        pauseState->keyPressed(key);
    if (!pauseState->isPause())
        currentState->keyPressed(key);
    // Code Added
    if (key == 'h')
        player->setHealth(player->getmax_Health());
    if (key == 'b')
        currentArea->spawnBoss();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    // Code Added
    if (!pauseState->isPause())
        currentState->dragEvent(dragInfo);
}