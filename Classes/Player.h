#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_INITIAL_SPEED 5
#define PLAYER_JUMP 15
#define GRAVITY 1.5
#define FLOATNG_GRAVITY 0.4
#define TERMINAL_VELOCITY 50
#define FLOATING_FRICTION 0.98f
#define AIR_FRICTION 0.99f

#include "cocos2d.h"
#include "GameSprite.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum
{
    kPlayerMoving,
    kPlayerFalling,
    kPlayerDying
    
} PlayerState; 


class Player : public GameSprite {
    
    float _speed;
    
    CCSize _screenSize;
    
    void initPlayer (void);
	CC_SYNTHESIZE(CCArmature*, _catRun, CatRun);

public:
	
	Player(void);
	~Player(void);
	
	CC_SYNTHESIZE(PlayerState, _state, State);
	CC_SYNTHESIZE(bool, _inAir, InAir);
    CC_SYNTHESIZE(bool, _jumping, Jumping);
    CC_SYNTHESIZE(float, _maxSpeed, MaxSpeed);
    
    static Player * create (void);
// 	
// 	CREATE_FUNC(Player);
// 	virtual bool init();

	virtual void update (float dt);
	
    void reset (void);

	void updateAnimation(PlayerState pState);
   
	inline virtual void place () { 
		this->setPositionY( _nextPosition.y );
//         if (_vector.x > 0 && this->getPositionX() < _screenSize.width * 0.2f) {
//             this->setPositionX(this->getPositionX() + _vector.x);
//             if (this->getPositionX() > _screenSize.width * 0.2f) {
//                 this->setPositionX(_screenSize.width * 0.2f);
//             }
//         }
		if (this->getPositionY() > _screenSize.height)
		{
			this->setPositionY(_screenSize.height);
		}
	};
    
    inline int left() {
    	return this->getPositionX() - _width * 0.3f;
	}
    
	inline int right() {
    	return this->getPositionX() + _width * 0.3f;
	}
    
    inline int top() {
    	return this->getPositionY() ;
    }
    
    inline int bottom() {
		return this->getPositionY() - _height  ;
    }
    
    inline int next_left() {
    	return _nextPosition.x - _width * 0.3f;
    }
    
    inline int next_right() {
    	return _nextPosition.x + _width * 0.3f;
    }
    
    inline int next_top() {
    	return _nextPosition.y ;
    }
    
    inline int next_bottom() {
    	return _nextPosition.y - _height;
    }
	
};

#endif // __PLAYER_H__

		
