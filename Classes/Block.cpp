#include "Block.h"
Block::~Block () {

	CC_SAFE_RELEASE(_wallTiles);

}

Block::Block () {

	//get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	_tileWidth = _screenSize.width / TILE_W_SIZE;
	_tileHeight = _screenSize.height /TILE_H_SIZE;
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
	_height = height * _tileHeight + _tileHeight * 0.1f;
	this->setPositionY(_height);

	CCSprite * wallFrame;
//	CCSpriteFrame *peachFrame= _peach1;

	switch (type) {

	case kBlockGap:
		this->setVisible(false);
		return;

	case kBlock:
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
	int i;
	_wallTiles = CCArray::createWithCapacity(20); //ngoi
	_wallTiles->retain();

	CCSprite * tile;
		for (i = 0; i < 20; i++) {
			tile = CCSprite::create("nha2.png");
			tile->setAnchorPoint(ccp(0, 1));
			tile->setPosition(ccp(i * _tileWidth, 0));
			tile->setVisible(false);
			this->addChild(tile, kMiddleground, kWallTile);
			_wallTiles->addObject(tile);

		}
	//}
}

