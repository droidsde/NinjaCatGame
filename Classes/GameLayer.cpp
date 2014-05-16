#include "GameLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

CCScene* GameLayer::scene()
{

	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameLayer *layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameLayer::~GameLayer(){
//	CC_SAFE_RELEASE(_daos);
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	_screenSize=CCDirector::sharedDirector()->getWinSize();

	addBackground();
	addTerrain();
	addPlayer();

	_GameState=kGamePlay;

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(GameLayer::update));
	return true;
}


void GameLayer::addBackground(){
	CCSprite *bg=CCSprite::create("bg.jpg");
	bg->setPosition(ccp(_screenSize.width/2, _screenSize.height/2));
	this->addChild(bg);
}

void GameLayer::addTerrain(){
	_terrain=Terrain::create();
	this->addChild(_terrain, 1);

	_terrain->setStartTerrain(true);
}

void GameLayer::addPlayer(){
	_player=Player::create();
	this->addChild(_player, 2);
	_player->setState(kPlayerMoving);
	_player->updateAnimation(kPlayerMoving);
}

void GameLayer::update(float dt){
	if (!_running) return;

	if (_player->getPositionY() < -_player->getHeight() ||
		_player->getPositionX() < -_player->getWidth() * 0.5f) {

			if (_GameState == kGamePlay) {

				_running = false;

				//create GAME OVER state

				_GameState = kGameOver;


			}
	}

	_player->update(dt);
	_terrain->move(10.0);

	if (_player->getState() != kPlayerDying) {
		_terrain->checkCollision(_player);
	}

	_player->place();


		 			
	 if (_terrain->getStartTerrain() && _player->getVector().x > 0) {

		_speedIncreaseTimer += dt;
		if (_speedIncreaseTimer > _speedIncreaseInterval) {
			_speedIncreaseTimer = 0;
			_player->setMaxSpeed (_player->getMaxSpeed() + 4);
		}
	 }
}



void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if (_GameState == kGamePlay) {
		_player->setJumping(false);
		_player->setState(kPlayerMoving);
		_player->updateAnimation(kPlayerMoving);
	}
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCTouch *touch = (CCTouch *)pTouches->anyObject();

	if (touch) {

		CCPoint tap = touch->getLocation();
		         
		         switch (_GameState) {
		             
		             case kGameIntro:
		                 break;
		             case kGameOver:

		                 break;
		                 
		             case kGamePlay:

		                if (_player->getState() == kPlayerFalling) {
				                    // _player->setFloating( _player->getFloating() ? false : true );
				                 CCLog("================================lon");
				                 } else {
									 if (_player->getState() !=  kPlayerDying) {
										 _player->setJumping(true);
										 _player->updateAnimation(kPlayerFalling);
									 }
								}
									 break;
				}
		}
}