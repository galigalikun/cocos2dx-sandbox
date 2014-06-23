// NENDモジュールのパクリ

#include "AdGenerationModule.h"
#include "AppController.h"
#import "CCEAGLView.h"
#import "ADGManagerViewController.h"

USING_NS_CC;

@interface ADGNI : NSObject<ADGManagerViewControllerDelegate>
{
}

@end

@implementation ADGNI


-(void)ADGManagerViewControllerReceiveAd:(ADGManagerViewController *)adView{
    //初回ロード終了後の処理を記述
    CCLOG("ADGManagerViewControllerReceiveAd");
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_RECEIVE_AD", NULL);
}

-(void)ADGManagerViewControllerFailedToReceiveAd:(ADGManagerViewController *)adView{
    //ロード終了後処理を記述
    CCLOG("ADGManagerViewControllerFailedToReceiveAd");
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_FAIL_TO_RECEIVE_AD", NULL);
}

-(void)ADGBrowserViewControllerShow{
    //ロード失敗の処理を記述
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_BROWSER_SHOW", NULL);
}

-(void)ADGBrowserViewControllerClose{
    //広告クリック時の処理を記述
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_BROWSER_CLOSE", NULL);
}
- (void)ADGVideoViewAppear{
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_VIDEO_APPEAR", NULL);
}
- (void)ADGVideoViewDisappear{
    NotificationCenter::getInstance()->postNotification("ADG_NOTIFICATION_VIDEO_DISAPPEAR", NULL);
}

@end


//シングルトンの設定
static ADGManagerViewController* adView = nil;
static NSString* locationidString = nil;


AdGenerationModule::AdGenerationModule()
{
    CCLOG("AdGenerationModule");
}

AdGenerationModule::~AdGenerationModule()
{
    CCLOG("~AdGenerationModule");
}

void AdGenerationModule::createView(const char* locationid, AdType adtype)
{
    if(adView){
        // すでにadViewを生成済み
        return;
    }
    
    locationidString = [NSString stringWithCString:locationid encoding:NSUTF8StringEncoding];
    [locationidString retain];
    
    
    NSInteger adTypeInt = 0;
    
    switch (adtype) {
        case SP_320x50:
            adTypeInt = kADG_AdType_Sp;
            break;
        case LARGE_320x100:
            adTypeInt = kADG_AdType_Large;
            break;
        case RECT_300x250:
            adTypeInt = kADG_AdType_Rect;
        case TABLET_728x90:
            adTypeInt = kADG_AdType_Tablet;
            break;
        case FREE:
            adTypeInt = kADG_AdType_Free;
            break;
        default:
            break;
    }


    NSDictionary *adgparam;
    
    if(adtype == FREE) {
        adgparam = @{
                     @"locationid" : locationidString, //管理画面から払い出された広告枠ID
                     @"adtype" : @(adTypeInt), //管理画面にて入力した枠サイズ(kADG_AdType_Sp：320x50, kADG_AdType_Large:320x100, kADG_AdType_Rect:300x250, kADG_AdType_Tablet:728x90, kADG_AdType_Free
                     @"originx" : @(0), //広告枠設置起点のx座標 ※下記参照
                     @"originy" : @(0),  //広告枠設置起点のy座標 ※下記参照
                     @"w" : @(0), //広告枠横幅 ※下記参照
                     @"h" : @(0)  //広告枠高さ ※下記参照
                     };
    } else {
        adgparam = @{
                               @"locationid" : locationidString, //管理画面から払い出された広告枠ID
                               @"adtype" : @(adTypeInt), //管理画面にて入力した枠サイズ(kADG_AdType_Sp：320x50, kADG_AdType_Large:320x100, kADG_AdType_Rect:300x250, kADG_AdType_Tablet:728x90, kADG_AdType_Free
                               @"originx" : @(0), //広告枠設置起点のx座標 ※下記参照
                               @"originy" : @(0)  //広告枠設置起点のy座標 ※下記参照
                               };
    }



    
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    // iOSのバージョンによる処理切り分け
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0){
        //iOS 6.0 未満の場合
        NSArray* viewsArray = window.subviews;
        for (UIView* subview in viewsArray) {
            if ([subview isKindOfClass:[CCEAGLView class]]) {
                NSLog(@"AdGenerationModule::create:iOS 6.0 未満の場合");
                adView = [[ADGManagerViewController alloc] initWithAdParams :adgparam : subview];
                break;
            }
        }
    }
    else {
        //iOS 6.0 以上の場合
        NSLog(@"AdGenerationModule::create:iOS 6.0 以上の場合%@",adgparam);
        adView = [[ADGManagerViewController alloc] initWithAdParams :adgparam : window.rootViewController.view];
    }
    
    [adView retain];
    
    adView.delegate = [[ADGNI alloc] init];
    
    
    load();
    hideView();
    

    
}

void AdGenerationModule::createView(const char* locationid, AdType adtype, cocos2d::Point pos)
{
    //広告View生成
    AdGenerationModule::createView(locationid, adtype);
    
    //位置設定
    
    //cocos2d-x上の座標をiOSの座標に変換
    //cocos2d-xで管理するwindowサイズを取得
    cocos2d::Size size = Director::getInstance()->getWinSize();
    
    //座標を割合で取得
    cocos2d::Point pointRate;
    pointRate.x = (pos.x / size.width);
    pointRate.y = (pos.y / size.height);
    
    //iOSで管理するViewのサイズを取得
    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView*) glview->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //高さをiOS基準に変換する
    CGPoint newPosition;
    newPosition.x = mainViewRect.size.width * pointRate.x;
    newPosition.y = mainViewRect.size.height - (mainViewRect.size.height * pointRate.y);
    
    //座標の設定
    [adView setAdOrigin:newPosition];


}

void setPositionTop(){
    //NADViewを画面上部・中央に移動する
    
    //Windowサイズを取得
    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView*) glview->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //NADViewの位置を変更
    CGPoint newPosition;
    newPosition.x = (mainViewRect.size.width - adView.view.frame.size.width) /2;
    newPosition.y = 0;
    [adView setAdOrigin:newPosition];

    
    
    return;
}

void setPositionButtom(){

    
    //Windowサイズを取得
    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView*) glview->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    

    CGPoint newPosition;
    newPosition.x = (mainViewRect.size.width - adView.view.frame.size.width) /2;
    newPosition.y = mainViewRect.size.height - adView.view.frame.size.height;
    [adView setAdOrigin:newPosition];

    
    
    return;
}

void AdGenerationModule::createViewTop(const char *locationid, AdType adtype){
    //広告View生成
    AdGenerationModule::createView(locationid, adtype);
    
    //位置設定
    setPositionTop();

}

void AdGenerationModule::createViewBottom(const char *locationid, AdType adtype){
    //広告View生成
    AdGenerationModule::createView(locationid, adtype);
    
    //位置設定
    setPositionButtom();

}

void AdGenerationModule::hideView()
{
    if(adView) {
        [adView.view setHidden:YES];
    }
}

void AdGenerationModule::showView()
{
    if(adView) {
        [adView.view setHidden:NO];
    }
}

void AdGenerationModule::load()
{
    if(adView) {
        [adView loadRequest];
    }
}

void AdGenerationModule::pause()
{
    if(adView) {
        [adView pauseRefresh];
    }
}

void AdGenerationModule::resume()
{
    if(adView) {
        [adView resumeRefresh];
    }
}

void AdGenerationModule::release(){
    CCLOG("AdGenerationModule::release");
    AdGenerationModule::pause();



    [adView.view removeFromSuperview];
    [adView.view release];
    [adView.delegate release];
    adView.delegate = nil;
    [adView release];
    adView = nil;
    
    [locationidString release];


}
