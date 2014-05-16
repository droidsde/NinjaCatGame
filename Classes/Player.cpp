#include "Player.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#define ACCELERATION 0.05

using namespace CocosDenshion;

USING_NS_CC_EXT;

Player::~Player(){

}

Player::Player() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	_speed = PLAYER_INITIAL_SPEED;
	_maxSpeed = PLAYER_INITIAL_SPEED;
	_nextPosition = CCPointZero;
	_nextPosition.y = _screenSize.height * 0.6f;
	_state = kPlayerMoving;
	_jumping = false;
}

Player * Player::create () {

	Player * player = new Player();
	if (player && player->init()) {
		player->autorelease();
		player->setSize();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::update (float dt) {

	if (_speed + ACCELERATION <= _maxSpeed) {
		_speed += ACCELERATION;
	} else {
		_speed = _maxSpeed;
	}

	_vector.x = _speed;

	switch (_state) {
	case kPlayerMoving:
		_vector.y -= GRAVITY;
		break;
	case kPlayerFalling:

			_vector.y -= GRAVITY;
			_vector.x *= AIR_FRICTION;

		break;
	case kPlayerDying:
		_vector.y -= GRAVITY;
		_vector.x = -_speed;
		this->setPositionX(this->getPositionX() + _vector.x);
		break;

	}

	if (_jumping) {
		_state = kPlayerFalling;
		_vector.y += PLAYER_JUMP * 0.25f;
		if (_vector.y > PLAYER_JUMP ) _jumping = false;
	}

	if (_vector.y < -TERMINAL_VELOCITY) _vector.y = -TERMINAL_VELOCITY;

	_nextPosition.y = this->getPositionY() + _vector.y;


	if (_vector.x * _vector.x < 0.01) _vector.x = 0;
	if (_vector.y * _vector.y < 0.01) _vector.y = 0;

}

void Player::reset () {

	_speed = PLAYER_INITIAL_SPEED;
	_maxSpeed = PLAYER_INITIAL_SPEED;

	_vector = ccp(0,0);
	this->setRotation(0);
	_nextPosition.y = _screenSize.height * 0.6f;
	this->setPosition(ccp( _screenSize.width * 0.2f, _nextPosition.y ));
	_state = kPlayerMoving;
	_jumping = false;
}

void Player::initPlayer () {

	this->setPosition(ccp(_screenSize.width * 0.2f, _nextPosition.y));
	_catRun=CCArmature::create("anicat");
			//_catRun->getAnimation()->playByIndex(0);
	this->addChild(_catRun);

	_width=_screenSize.width/8;
	_height=_screenSize.height/20;
	this->setWidth(_width);
	this->setHeight(_height);
}

void Player::updateAnimation(PlayerState pState){
	switch(pState){
	case kPlayerMoving:

		_catRun->getAnimation()->playByIndex(0);
		break;
	case kPlayerFalling:
		_catRun->getAnimation()->playByIndex(1);
		break;
	}
}