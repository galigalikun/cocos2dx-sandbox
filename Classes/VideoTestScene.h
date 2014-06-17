//
//  VideoTestScene.h
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/16.
//
//

#ifndef __cocos2dx_sandbox__VideoTestScene__
#define __cocos2dx_sandbox__VideoTestScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class VideoTest : public cocos2d::Layer
// , public cocos2d::extension::ScrollViewDelegate
{
private:
    // cocos2d::extension::ScrollView* mScrollView;

    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    
    void videoEventCallback(cocos2d::Ref*, cocos2d::experimental::ui::VideoPlayer::EventType);
    
    // implement the "static create()" method manually
    CREATE_FUNC(VideoTest);
};

#endif /* defined(__cocos2dx_sandbox__VideoTestScene__) */
