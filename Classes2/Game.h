#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Terrain.h"
#include "Player.h"

USING_NS_CC;
class Game : public cocos2d::CCLayer
{
private:
	CCSize _screenSize;
	Terrain *_terrain;
	Player *_player;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(Game);
	virtual void update(float delta);

	void addBackground();
	void addTerrain();
	void addPlayer();
};

#endif // __GAME_SCENE_H__
