//
//  WebViewTestScene.cpp
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/20.
//
//

#include "WebViewTestScene.h"

#include "UIWebView.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* WebViewTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WebViewTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WebViewTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto webView = galigalikun::ui::WebView::create();
    webView->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    webView->setContentSize(Size(visibleSize.width, visibleSize.height));
    webView->setOpenDomains({"github.io"});
    webView->setURL("http://dev.xperia.biz/webview.html");
    webView->addEventListener([this](Ref* sender, galigalikun::ui::WebView::EventType eventType){
        CCLOG("callback");
    });
    this->addChild(webView);

    
    return true;

}

