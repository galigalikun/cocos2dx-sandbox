#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "plugin/protocols/include/PluginManager.h"
#include "plugin/protocols/include/ProtocolAnalytics.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // http://laboyukai.blogspot.jp/2014/06/cocos2dx-v30-plugin-x-admob.html
    auto pluginAnalytics = dynamic_cast<cocos2d::plugin::ProtocolAnalytics*>(cocos2d::plugin::PluginManager::getInstance()->loadPlugin("AnalyticsFlurry"));
    
    pluginAnalytics->startSession("N4KJMYNR7H8BSNG62GP5");

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
