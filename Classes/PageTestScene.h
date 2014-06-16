//
//  PageTestScene.h
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/16.
//
//

#ifndef __cocos2dx_sandbox__PageTestScene__
#define __cocos2dx_sandbox__PageTestScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class PageTest : public cocos2d::Layer
// , public cocos2d::extension::ScrollViewDelegate
{
private:
    // cocos2d::extension::ScrollView* mScrollView;
    
    cocos2d::Node* create9Sprite(float, float);
    
    
    int percent;
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void update(float);
    
    void pageViewEvent(cocos2d::Ref*, cocos2d::ui::PageView::EventType);
    void selectedEvent(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType);
    void sliderEvent(cocos2d::Ref*, cocos2d::ui::Slider::EventType);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PageTest);
};

#endif /* defined(__cocos2dx_sandbox__PageTestScene__) */
