
#include "Player.h"
#include "SimpleAudioEngine.h"
#define ACCELERATION 0.05

using namespace CocosDenshion;

Player::~Player(){
    
//    CC_SAFE_RELEASE(_rideAnimation);
}

Player::Player() {
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _speed = PLAYER_INITIAL_SPEED;
    _maxSpeed = PLAYER_INITIAL_SPEED;
    _nextPosition = CCPointZero;
	_nextPosition.y = _screenSize.height * 0.42f;
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
    _nextPosition.y = _screenSize.height * 0.42f;
    this->setPosition(ccp( _screenSize.width * 0.2f, _nextPosition.y));
    _state = kPlayerMoving;
    _jumping = false;
}


void Player::initPlayer () {
    
    this->setAnchorPoint(ccp(0.5f, 1.0f));
    this->setPosition(ccp(_screenSize.width * 0.2f, _nextPosition.y));

    
	CCAnimation *animation=CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	CCSprite * _chay = CCSprite::create("chay1.png");
	for (int i=0; i<=2; i++)
	{
	 	name=CCString::createWithFormat("chay%d.png", i+1);
	 	frame=CCSpriteFrame::create(name->getCString(), _chay->getTextureRect());
	 	animation->addSpriteFrame(frame);
	}
	 	 
	animation->setDelayPerUnit(0.05);
	animation->setRestoreOriginalFrame(true);
    
	//CCAnimation *animation =CCAnimation::createWithSpriteFrames(frames, 0.05);
	CCAnimate *animate=CCAnimate::create(animation);

	CCRepeatForever *repeat=CCRepeatForever::create(animate);

    this->runAction(repeat);

	_height = 252 * 0.95f /*_chay->boundingBox().size.height*/;
	_width = 184/*_chay->boundingBox().size.width*/;
}
