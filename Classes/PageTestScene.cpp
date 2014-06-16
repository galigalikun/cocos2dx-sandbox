//
//  PageTestScene.cpp
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/16.
//
//

#include "PageTestScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* PageTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PageTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PageTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    scheduleUpdate();
    
    percent = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto loadingBar = ui::LoadingBar::create("sliderProgress.png");
    loadingBar->setTag(0);
    loadingBar->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    loadingBar->setPercent(percent);
    this->addChild(loadingBar);
    
    
    
    
    auto checkBox = ui::CheckBox::create("check_box_normal.png", "check_box_normal_press.png", "check_box_active.png", "check_box_normal_disable.png", "check_box_active_disable.png");
    checkBox->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 100));
    checkBox->addEventListener(CC_CALLBACK_2(PageTest::selectedEvent, this));
    this->addChild(checkBox);
    
    
    auto slider = ui::Slider::create();
    slider->loadBarTexture("sliderTrack.png");
    slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
    slider->loadProgressBarTexture("sliderProgress.png");
    slider->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 200));
    slider->addEventListener(CC_CALLBACK_2(PageTest::sliderEvent, this));
    this->addChild(slider);
    
    
    auto richText = ui::RichText::create();
    richText->ignoreContentAdaptWithSize(false);
    richText->setSize(Size(100, 100));
    richText->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 300));
    this->addChild(richText);
    
    auto re1 = ui::RichElementText::create(1, Color3B::WHITE, 255, "This color is white. ", "Arial", 10);
    richText->pushBackElement(re1);
    
    auto re2 = ui::RichElementText::create(2, Color3B::YELLOW, 255, "This color is yellow. ", "Arial", 24);
    richText->insertElement(re2, 1);
    
    auto reimg = ui::RichElementImage::create(6, Color3B::WHITE, 255, "sliderballnormal.png");
    richText->pushBackElement(reimg);
    
    // auto recustom = ui::RichElementCustomNode::create(1, Color3B::WHITE, 255, pAr);
    // richText->pushBackElement(recustom);
    
    
    
    auto videoPlayer = experimental::ui::VideoPlayer::create();
    videoPlayer->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 400));
    videoPlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    // videoPlayer->setURL("");
    videoPlayer->setFileName("cocosvideo.mp4");
    videoPlayer->play();
    this->addChild(videoPlayer);
    
    
    
    
    auto pageView = ui::PageView::create();
    
    pageView->setSize(Size(visibleSize.width, 130.0f));
    pageView->setPosition(Vec2::ZERO);
    
    for (int i = 0; i < 3; ++i) {
        auto layout = ui::Layout::create();
        layout->setSize(Size(240.0f, 130.0f));
        
        auto imageView = ui::ImageView::create("HelloWorld.png");
        imageView->setScale9Enabled(true);
        imageView->setSize(Size(240, 130));
        imageView->setPosition(Vec2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(imageView);
        
        auto label = ui::Text::create(StringUtils::format("page %d",(i+1)), "Arial", 30);
        label->setColor(Color3B(192, 192, 192));
        label->setPosition(Vec2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(label);
        
        
        pageView->addPage(layout);
    }
    pageView->addEventListener(CC_CALLBACK_2(PageTest::pageViewEvent, this));
    
    
    this->addChild(pageView);

    
    return true;
}


void PageTest::pageViewEvent(Ref* pSender, ui::PageView::EventType type)
{
    switch (type)
    {
        case ui::PageView::EventType::TURNING:
        {
            ui::PageView* pageView = dynamic_cast<ui::PageView*>(pSender);
            CCLOG("page = %ld", pageView->getCurPageIndex() + 1);
        }
            break;
            
        default:
            break;
    }
}

void PageTest::selectedEvent(Ref* pSender, ui::CheckBox::EventType type)
{
    switch (type)
    {
        case ui::CheckBox::EventType::SELECTED:
            break;
        case ui::CheckBox::EventType::UNSELECTED:
            break;
        default:
            break;
    }
}

void PageTest::sliderEvent(Ref *pSender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ui::Slider*>(pSender);
        CCLOG("sliderEvent:%d", slider->getPercent());
    }
}


void PageTest::update(float f)
{
    percent++;
    
    if(percent > 100) {
        percent = 100;
    }
    
    auto loadingBar = static_cast<ui::LoadingBar*>(this->getChildByTag(0));
    loadingBar->setPercent(percent);
}