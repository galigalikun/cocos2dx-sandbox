//
//  WebViewTestScene.h
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/20.
//
//

#ifndef __cocos2dx_sandbox__WebViewTestScene__
#define __cocos2dx_sandbox__WebViewTestScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"



class WebViewTest : public cocos2d::Layer
, public cocos2d::extension::AssetsManagerDelegateProtocol
// , public cocos2d::extension::ScrollViewDelegate
{
private:
    // cocos2d::extension::ScrollView* mScrollView;
    
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(WebViewTest);
};

#endif /* defined(__cocos2dx_sandbox__WebViewTestScene__) */
