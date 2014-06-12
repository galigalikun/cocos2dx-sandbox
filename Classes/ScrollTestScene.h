#ifndef __SCROLLTEST_SCENE_H__
#define __SCROLLTEST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

class ScrollTest : public cocos2d::Layer
// , public cocos2d::extension::ScrollViewDelegate
{
private:
    // cocos2d::extension::ScrollView* mScrollView;
    
    cocos2d::Node* create9Sprite(float, float);
    
    
    int x;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    /*
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView*);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView*);
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    */
    
    void backAction(cocos2d::Ref*, cocos2d::extension::Control::EventType);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ScrollTest);
};

#endif // __SCROLLTEST_SCENE_H__
