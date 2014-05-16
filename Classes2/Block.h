#ifndef __BLOCK_H__
#define __BLOCK_H__

#define TILE_H_SIZE 10
#define TILE_W_SIZE 5.8

#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;


enum {
	kWallTile,
	kPeach
};

enum  {
	kBlockGap,
	kBlock
	
};

class Block : public GameSprite {

	CCSize _screenSize;

	CCArray * _wallTiles;

	CCSprite * _tile1;

	int _tileWidth; //do rong tuong
	int _tileHeight; //chieu cao tuong



	void initBlock(void); 


public:

	CC_SYNTHESIZE(int, _type, Type);


	Block();
	~Block();

	static Block * create();
	void setupBlock (int width, int height, int type);

	inline virtual int left() {
		return this->getPositionX();
	}

	inline virtual int right() {
		return this->getPositionX() + _width;
	}

	inline virtual int top() {
		return this->getHeight();
	}

	inline virtual int bottom() {
		return 0;
	}
};

#endif // __BLOCK_H__
