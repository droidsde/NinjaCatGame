#define TOTAL_PUFFS 3


#include "Block.h"
Block::~Block () {

	CC_SAFE_RELEASE(_wallTiles);
}

Block::Block () {

	//get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	_tileWidth = _screenSize.width / TILE_W_SIZE;
	_tileHeight = _screenSize.height / TILE_H_SIZE;
	this->setVisible(false);
}

Block * Block::create () {

	Block * block = new Block();
	if (block && block->init()) {
		block->autorelease();
		block->initBlock();
		return block;
	}
	CC_SAFE_DELETE(block);
	return NULL;
}



void Block::setupBlock (int width, int height, int type) {

	_type = type;

	_width = width * _tileWidth;
	_height = height * _tileHeight + _tileHeight * 0.49f;
	this->setPositionY(_height);

	CCSprite * wallFrame;

	switch (type) {

	case kBlockGap:
		this->setVisible(false);
		return;

	case kBlock1:
		wallFrame = _tile1;

		break;
	}

	int i;
	int count;	

	this->setVisible(true);

	CCSprite * tile;

	count = _wallTiles->count();
	for (i  = 0; i < count; i++) {
		tile = (CCSprite *) _wallTiles->objectAtIndex(i);
		if (tile->getPositionX() < _width && tile->getPositionY() > -_height) {
			tile->setVisible(true);
		} else {
			tile->setVisible(false);
		}
	}
}

void Block::initBlock() {


	_tile1 = CCSprite::create("nha2.png");


	//create tiles
//	int i;
	_wallTiles = CCArray::createWithCapacity(20); //tuong
	_wallTiles->retain();


	CCSprite * tile;

		for (int j = 0; j < 20; j++) {
			tile = CCSprite::create("nha2.png");
			tile->setAnchorPoint(ccp(0, 1));
			tile->setPosition(ccp(j * tile->boundingBox().size.width, 0));
			tile->setVisible(false);
			this->addChild(tile, kBackground, kWallTile);
			_wallTiles->addObject(tile);
		}

	
}