#include "ScrollTestScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* ScrollTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ScrollTest::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScrollTest::init()
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
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("new sceen", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    auto btn = ControlButton::create("戻る", "Arial", 24);
    btn->setPosition(Vec2(btn->getContentSize().width, origin.y + visibleSize.height - btn->getContentSize().height));
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(ScrollTest::backAction), Control::EventType::TOUCH_DOWN);
    this->addChild(btn, 2);
    
    

    
    
    auto scrollView = ui::ScrollView::create();
    scrollView->setSize(Size(visibleSize.width, visibleSize.height - 100));
    scrollView->setPosition(Point::ZERO);
    // scrollView->setPositionType(ParticleSystem::PositionType::RELATIVE);
    
    scrollView->setInnerContainerSize(Size(2000, scrollView->getSize().height));
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    scrollView->addEventListener(CC_CALLBACK_2(ScrollTest::scrollEvent, this));
    this->addChild(scrollView, 3);
    
    auto a = ControlButton::create();
    a->setEnabled(true);
    auto continerLayer = Layer::create();
    continerLayer->setContentSize(Size(2000, visibleSize.height));
    continerLayer->setPosition(Point(0,0));
    for (int i = 0; i < 10; i++) {
        auto frame = ui::Layout::create();
        frame->addTouchEventListener(CC_CALLBACK_2(ScrollTest::testClick, this));
        frame->setBackGroundImage("");
        frame->setBackGroundColor(Color3B::BLACK);
        frame->setBackGroundColorOpacity(100);
        frame->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        
        auto img = ui::ImageView::create("");
        if(img->isTouchEnabled())
        {
            
        }
        img->setTouchEnabled(false);
        img->setScale(0.5);
        
        auto name = ui::Text::create("", "", 33);
        name->setColor(Color3B::RED);
        name->setString("");
        name->setTextAreaSize(Size(20,20));
        name->setTextHorizontalAlignment(TextHAlignment::CENTER);
        name->setTextVerticalAlignment(TextVAlignment::CENTER);
        
        
        
        scrollView->addChild(this->create9Sprite(i*200+100, visibleSize.height/2 + origin.y));
        // continerLayer->addChild(this->create9Sprite(visibleSize.width/2 + origin.x, i*200+100));
    }
    
    scrollView->addChild(continerLayer);
    
    scrollView->setInnerContainerSize(Size(10, 10));
    
    
    /*
    mScrollView = ScrollView::create();
    mScrollView->setViewSize(Size(visibleSize.width, visibleSize.height - 100));
    mScrollView->setPosition(0, 0);
    mScrollView->setContainer(continerLayer);
    mScrollView->setDirection(ScrollView::Direction::VERTICAL);
    mScrollView->setDelegate(this);
    this->addChild(mScrollView, 3);
     */
    
    
    
    /*
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ScrollTest::onTouchBegan, this);
    
    listener->onTouchMoved = CC_CALLBACK_2(ScrollTest::onTouchMoved, this);
    
    listener->onTouchEnded = CC_CALLBACK_2(ScrollTest::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    */
    
    return true;
}
/*
bool ScrollTest::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void ScrollTest::onTouchMoved(Touch* touch, Event* event)
{
    x = mScrollView->getContentOffset().x;
}

void ScrollTest::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded");
    mScrollView->unscheduleAllSelectors();
    int offset =  x % 200;
    int num    =  x / 200;
    Point adjustPos;
    float adjustAnimDelay;
    if (offset<=-100) {
        
        adjustPos = Point((num-1)*200, mScrollView->getContentOffset().y);
        adjustAnimDelay=(offset*(-1)%100)/600;
    }
    
    if (offset<=0&&offset>-100) {
        
        adjustPos = Point(num*200, mScrollView->getContentOffset().y);
        adjustAnimDelay=(offset*(-1)%100)/600;
    }
    
    if (offset>0) {
        
        adjustPos = Point(0, mScrollView->getContentOffset().y);
        adjustAnimDelay=(offset*(1)%100)/600;
    }
    
    if (x<=-1400) {
        adjustPos = Point(-1400, mScrollView->getContentOffset().y);
        adjustAnimDelay=(offset*(-1)%100)/600;
    }
    
    adjustAnimDelay=0.7;
    mScrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);

}


void ScrollTest::scrollViewDidScroll(ScrollView* view)
{
    
}

void ScrollTest::scrollViewDidZoom(ScrollView* view)
{
    
}
*/

Node* ScrollTest::create9Sprite(float w, float h)
{
    auto button = ui::Button::create("HelloWorld.png");
    button->setTitleText("Demo");
    button->addTouchEventListener(CC_CALLBACK_2(ScrollTest::testClick, this));
    button->setPosition(Point(w, h));
    
    return button;
    /*
    auto sprite9 = Scale9Sprite::create("HelloWorld.png");
    auto label = LabelTTF::create("Demo","Arial",50);
    
    auto btn = ControlButton::create(label, sprite9);
    btn->setPreferredSize(sprite9->getContentSize());
    btn->setPosition(Point(w, h));
    
    return btn;
     */
}

void ScrollTest::backAction(Ref* pSender, Control::EventType controlEvent)
{
    Director::getInstance()->popScene();
}

void ScrollTest::testClick(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("test click");
            break;
        default:
            break;
    }

}


void ScrollTest::scrollEvent(Ref* pSender, ui::ScrollView::EventType type)
{
    if(type == ui::ScrollView::EventType::SCROLLING) {
        auto scrollView = dynamic_cast<ui::ScrollView*>(pSender);
        // CCLOG("scrollEvent:%d", scrollView->getPercent());
    }
}