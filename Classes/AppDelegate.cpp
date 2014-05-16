#include "AppDelegate.h"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	SceneReader::sharedSceneReader()->purgeSceneReader();
	GUIReader::shareReader()->purgeGUIReader();
	ActionManager::shareManager()->purgeActionManager();
	CCArmatureDataManager::sharedArmatureDataManager()->purge();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();


	pDirector->setOpenGLView(pEGLView);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 480, kResolutionExactFit);

	std::vector<std::string> searchPaths;
	searchPaths.push_back("menu");
	searchPaths.push_back("images");
	searchPaths.push_back("fonts");
	searchPaths.push_back("anicat");
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("anicat0.png","anicat0.plist", "anicat.ExportJson");

	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.8f);

	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = MenuLayer::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
