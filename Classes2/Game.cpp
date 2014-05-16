#include "Game.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* Game::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	_screenSize=CCDirector::sharedDirector()->getWinSize();
// 	CCNode *gameScene= SceneReader::sharedSceneReader()->createNodeWithSceneFile("menu.json");
// 	this->addChild(gameScene);
// 
// 	CCNode *uiNode=gameScene->getChildByTag(10004);
// 	UILayer *ui=(UILayer*) uiNode->getComponent("GUIComponent")->getNode();
// 
// 	UIButton *btnChoi=(UIButton*) ui->getWidgetByName("btnchoi");
// 	btnChoi->addReleaseEvent(this, coco_releaseselector(MenuLayer::Choi));
	addBackground();
	addTerrain();
	addPlayer();

	this->schedule(schedule_selector(Game::update));
    return true;
}

void Game::addBackground(){
	CCSprite *bg=CCSprite::create("bg.jpg");
	bg->setPosition(ccp(_screenSize.width/2, _screenSize.height/2));
	this->addChild(bg);
}

void Game::addTerrain(){
	_terrain=Terrain::create();
	this->addChild(_terrain, 1);

	_terrain->setStartTerrain(true);
}

void Game::addPlayer(){
	_player=Player::create();
	this->addChild(_player, 2);
}

void Game::update(float delta){

	_player->update(delta);

	_terrain->move(10.0);
	if (_player->getState() != kPlayerDying) _terrain->checkCollision(_player);

	_player->place();
}