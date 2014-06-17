//
//  VideoTestScene.cpp
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/16.
//
//

#include "VideoTestScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* VideoTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = VideoTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool VideoTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    

    
    
    auto videoPlayer = experimental::ui::VideoPlayer::create();
    videoPlayer->setPosition(Vec2::ZERO);
    videoPlayer->setContentSize(Size(visibleSize.width, visibleSize.height));

    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->setKeepAspectRatioEnabled(true);
    videoPlayer->setVisible(true);
    videoPlayer->setFileName("cocosvideo.mp4");
    // videoPlayer->setURL("http://www.aji.sakura.ne.jp/motion/dnld.php?fpath=emu.mp4");
    videoPlayer->play();
    videoPlayer->addEventListener(CC_CALLBACK_2(VideoTest::videoEventCallback, this));
    this->addChild(videoPlayer);

    
    return true;
}

void VideoTest::videoEventCallback(Ref* sender, experimental::ui::VideoPlayer::EventType eventType)
{
    switch (eventType) {
        case experimental::ui::VideoPlayer::EventType::PLAYING:
            CCLOG("PLAYING");
            break;
        case experimental::ui::VideoPlayer::EventType::PAUSED:
            CCLOG("PAUSED");
            break;
        case experimental::ui::VideoPlayer::EventType::STOPPED:
            CCLOG("STOPPED");
            break;
        case experimental::ui::VideoPlayer::EventType::COMPLETED:
            CCLOG("COMPLETED");
            break;
        default:
            break;
    }
}