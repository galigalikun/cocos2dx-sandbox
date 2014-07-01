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
    label->setString("ATSApplicationFontsPathは入力後、 Application fonts resource path に表示が変わるみたです。値には同梱するフォントファイルを置いているフォルダを指定します。");
    label->setFontName("fonts/ipaexg.ttf");
    label->setColor(Color3B::GREEN);
    label->setFontSize(40);
    label->ignoreContentAdaptWithSize(false);   // falseしないと自動改行されない
    label->setSize(Size(visibleSize.width, 100));   // ui::textだとおさまりきらなくても落ちない
    label->setTextAreaSize(Size(visibleSize.width, 200));
    label->setContentSize(Size(visibleSize.width, 200));
    label->setPosition(Vec2(visibleSize.width/2, 200));
    label->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label);
    

    auto ttf = Label::createWithTTF("ATSApplicationFontsPathは入力後、 Application fonts resource path に表示が変わるみたです。値には同梱するフォントファイルを置いているフォルダを指定します。", "fonts/ipaexg.ttf", 40);
    if(ttf) {
        ttf->setColor(Color3B::BLUE);
        ttf->setDimensions(visibleSize.width, 200); // 収まりきらないと落ちるどうすれば。。
        ttf->setPosition(Vec2(visibleSize.width/2, visibleSize.height - ttf->getDimensions().height));
        this->addChild(ttf);
    }
    
    auto _richText = ui::RichText::create();
    _richText->ignoreContentAdaptWithSize(false);
    _richText->setSize(Size(visibleSize.width, 300));
    
    auto re1 = ui::RichElementText::create(1, Color3B::WHITE, 255, "ATSApplicationFontsPathは入力後、", "Helvetica", 30);
    auto re2 = ui::RichElementText::create(2, Color3B::YELLOW, 255, "Application fonts resource path", "Helvetica", 30);
    auto re3 = ui::RichElementText::create(3, Color3B::BLUE, 255, " に表示が変わるみたです。", "Helvetica", 30);
    auto re4 = ui::RichElementText::create(4, Color3B::GREEN, 255, "値には同梱する", "fonts/ipaexg.ttf", 30);
    auto re5 = ui::RichElementText::create(5, Color3B::BLACK, 255, "フォントファイルを置いている", "Helvetica", 30);
    
    
    auto reimg = ui::RichElementImage::create(6, Color3B::WHITE, 255, "cocosui/sliderballnormal.png");
    
    
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("cocosui/100/100.ExportJson");
    cocostudio::Armature *pAr = cocostudio::Armature::create("100");
    pAr->getAnimation()->play("Animation1");
    
    auto recustom = ui::RichElementCustomNode::create(1, Color3B::WHITE, 255, pAr);
    auto re6 = ui::RichElementText::create(7, Color3B::ORANGE, 255, "フォルダを指定します。", "Helvetica", 30);
    _richText->pushBackElement(re1);
    _richText->insertElement(re2, 1);
    _richText->pushBackElement(re3);
    _richText->pushBackElement(re4);
    _richText->pushBackElement(re5);
    _richText->insertElement(reimg, 2);
    _richText->pushBackElement(recustom);
    _richText->pushBackElement(re6);
    
    _richText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _richText->setLocalZOrder(10);
    
    
    this->addChild(_richText);

    
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