#include "HelloWorldScene.h"
#include "ScrollTestScene.h"
#include "PageTestScene.h"
#include "VideoTestScene.h"
#include "LabelTestScene.h"
#include "NetworkTestScene.h"
#include "AdGenerationModule.h"


USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, sprite->getContentSize().height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    {
        auto btn = ControlButton::create("scrollview", "Arial", 24);
        btn->setTag(1);
        btn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - btn->getContentSize().height - 50));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::testAction), Control::EventType::TOUCH_DOWN);
        this->addChild(btn, 1);
    }
    
    {
        auto btn = ControlButton::create("bannerview", "Arial", 24);
        btn->setTag(2);
        btn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - btn->getContentSize().height - 150));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::testAction), Control::EventType::TOUCH_DOWN);
        this->addChild(btn, 2);
    }

    {
        auto btn = ControlButton::create("videoview", "Arial", 24);
        btn->setTag(3);
        btn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - btn->getContentSize().height - 250));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::testAction), Control::EventType::TOUCH_DOWN);
        this->addChild(btn, 3);
    }
    
    {
        auto btn = ControlButton::create("labelview", "Arial", 24);
        btn->setTag(4);
        btn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - btn->getContentSize().height - 350));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::testAction), Control::EventType::TOUCH_DOWN);
        this->addChild(btn, 4);
    }
    
    {
        auto btn = ControlButton::create("network", "Arial", 24);
        btn->setTag(5);
        btn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - btn->getContentSize().height - 450));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::testAction), Control::EventType::TOUCH_DOWN);
        this->addChild(btn, 5);
    }
    
    AdGenerationModule::createViewBottom("aid", AdGenerationModule::AdType::SP_320x50);
    AdGenerationModule::showView();
    
    return true;
}

void HelloWorld::testAction(Ref* pSender, Control::EventType controlEvent)
{
    CCLOG("testAction:%d", static_cast<ControlButton*>(pSender)->getTag());
    switch (static_cast<ControlButton*>(pSender)->getTag()) {
        case 5:
        {
            auto scene = NetworkTest::createScene();
            Director::getInstance()->pushScene(cocos2d::CCTransitionFade::create(0.5f, scene));
            
            break;
        }
        case 4:
        {
            auto scene = LabelTest::createScene();
            Director::getInstance()->pushScene(cocos2d::CCTransitionFade::create(0.5f, scene));
            
            break;
        }
        case 3:
        {
            auto scene = VideoTest::createScene();
            Director::getInstance()->pushScene(cocos2d::CCTransitionFade::create(0.5f, scene));
            
            break;
        }
        case 2:
        {
            auto scene = PageTest::createScene();
            Director::getInstance()->pushScene(cocos2d::CCTransitionFade::create(0.5f, scene));

            break;
        }
        case 1:
        {
            auto scene = ScrollTest::createScene();
            Director::getInstance()->pushScene(cocos2d::CCTransitionFade::create(0.5f, scene));
            break;
        }
        default:
            break;
    }

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
