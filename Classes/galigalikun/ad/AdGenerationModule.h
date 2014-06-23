#ifndef __ADG_MODULE_H__
#define __ADG_MODULE_H__

#include "cocos2d.h"

class AdGenerationModule
{
public:
    // kADG_AdType_Sp：320x50, kADG_AdType_Large:320x100, kADG_AdType_Rect:300x250, kADG_AdType_Tablet:728x90, kADG_AdType_Free
    enum AdType {
        SP_320x50,
        LARGE_320x100,
        RECT_300x250,
        TABLET_728x90,
        FREE,
    };
private:
    AdGenerationModule();
    virtual ~AdGenerationModule();
    static void createView(const char*, AdType);
    static void load();
public:
    static void createView(const char*, AdType, cocos2d::Point);
    static void createViewBottom(const char*, AdType);
    static void createViewTop(const char*, AdType);
    static void hideView();
    static void showView();
    static void pause();
    static void resume();
    static void release();

};

#endif
