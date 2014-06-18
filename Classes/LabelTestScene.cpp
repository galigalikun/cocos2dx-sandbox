//
//  LabelTestScene.cpp
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/18.
//
//

#include "LabelTestScene.h"


USING_NS_CC;
USING_NS_CC_EXT;

Scene* LabelTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LabelTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LabelTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto layoutView = ui::Layout::create();
    
    layoutView->setSize(Size(visibleSize.width, visibleSize.height));
    layoutView->setPosition(Vec2::ZERO);
    layoutView->setAnchorPoint(Vec2::ZERO);
    layoutView->setBackGroundColor(Color3B::RED);
    layoutView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    
    
    this->addChild(layoutView);
    
    
    auto label = ui::Text::create();
    label->setString("Text");
    label->setFontName("Arial");
    label->setColor(Color3B::GREEN);
    label->setFontSize(40);
    label->setPosition(Vec2(visibleSize.width/2, 500));
    this->addChild(label);
    

    auto ttf = Label::createWithTTF("ATSApplicationFontsPathは入力後、 Application fonts resource path に表示が変わるみたです。値には同梱するフォントファイルを置いているフォルダを指定します。", "fonts/ipaexg.ttf", 40);
    if(ttf) {
        ttf->setPosition(Vec2(visibleSize.width/2, 600));
        ttf->setColor(Color3B::BLUE);
        ttf->setDimensions(visibleSize.width, 200);
        this->addChild(ttf);
    }
    
    
    CCLOG("labeltest");
    
    return true;
}

void LabelTest::videoEventCallback(Ref* sender, experimental::ui::VideoPlayer::EventType eventType)
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