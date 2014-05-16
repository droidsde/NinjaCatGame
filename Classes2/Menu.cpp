#include "Menu.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* Menu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Menu *layer = Menu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Menu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCNode *gameScene= SceneReader::sharedSceneReader()->createNodeWithSceneFile("menu.json");
	this->addChild(gameScene);

	CCNode *uiNode=gameScene->getChildByTag(10004);
	UILayer *ui=(UILayer*) uiNode->getComponent("GUIComponent")->getNode();

	UIButton *btnChoi=(UIButton*) ui->getWidgetByName("btnchoi");
	btnChoi->addReleaseEvent(this, coco_releaseselector(Menu::Choi));

    
    
    return true;
}

void Menu::Choi(CCObject *pSender){
	CCScene *newScene=CCTransitionFadeBL::create(0.5f, Game::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}

