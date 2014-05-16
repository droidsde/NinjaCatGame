#include "cocos2d.h"
#include "cocos-ext.h"
#include "Terrain.h"
#include "Player.h"
//#include "TerrainPeach.h"


USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
	kGameIntro,
	kGamePlay,
	kGameOver,
	kGameTutorial,
	kGameTutorialJump,
	kGameTutorialFloat,
	kGameTutorialDrop

} GameState;

enum{
	kSpritePeachS,
	kSpritePeachL
};
class GameLayer : public cocos2d::CCLayer
{
private:
	CCSize _screenSize;

	Terrain *_terrain;
	Player *_player;

	GameState _GameState;

	bool _running;
	int _speedIncreaseInterval;
	float _speedIncreaseTimer;

	CCParticleMeteor *_parNode;
	
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	~GameLayer();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(GameLayer);

	void addBackground();
	void addTerrain();
	void addPlayer();

	virtual void update(float dt);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};