#include "UIWebView.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

using namespace galigalikun::ui;
//-------------------------------------------------------------------------------------
#include "CCEAGLView.h"


@interface UIWebViewWrapperIos : NSObject<UIWebViewDelegate>

@property (strong,nonatomic) UIWebView* webView;


- (void) setFrame:(int) left :(int) top :(int) width :(int) height;
- (void) setOpenDomains:(std::vector<std::string> &) openDomain;
- (void) loadURL:(std::string&) url;
- (void) loadData:(std::string&) data;
- (void) setVisible:(bool) visible;



-(id) init:(void*) webView;


@end

@implementation UIWebViewWrapperIos
{
    int _left;
    int _top;
    int _width;
    int _height;
    
    WebView* _view;
    
    std::vector<std::string> _openDomain;
}

-(id)init:(void*)webView
{
    if (self = [super init]) {
        _view = (WebView*)webView;
        
        self.webView = [[UIWebView alloc] init];
        self.webView.delegate= self;
        
        
        auto view = cocos2d::Director::getInstance()->getOpenGLView();
        auto eaglview = (CCEAGLView *) view->getEAGLView();
        [eaglview addSubview:self.webView];

    }
    
    return self;
}

-(void) dealloc
{
    if (self.webView != nullptr) {

        [self.webView removeFromSuperview];
        [self.webView release];
        self.webView = nullptr;
        _view = nullptr;
    }
    [super dealloc];
}

-(void) setFrame:(int)left :(int)top :(int)width :(int)height
{
    _left = left;
    _width = width;
    _top = top;
    _height = height;
    if (self.webView != nullptr) {
        NSLog(@"setFrame:%d,%d,%d,%d", left, top, width, height);
        [self.webView setFrame:CGRectMake(left, top, width, height)];
    }
}

-(void) setOpenDomains:(std::vector<std::string> &)openDomain
{
    _openDomain = openDomain;
}

-(void) loadURL:(std::string &)url
{
    [self.webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@(url.c_str())]]];

}


-(void) loadData:(std::string &)data
{
    [self.webView loadData:[@(data.c_str()) dataUsingEncoding:NSUTF8StringEncoding] MIMEType:@"text/html" textEncodingName:@"utf-8" baseURL:nil];

}


- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{

    NSLog(@"didFailLoadWithError");
    if(_webView != nullptr)
    {
        _view->onWebViewEvent(WebView::EventType::ERROR);
    }

}
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{

    NSString *checkURL = [request.URL absoluteString];
    
    if(_webView != nullptr)
    {
        // todo リクエストurl情報を送るようにする　_view->setUserData(checkURL);
        _view->onWebViewEvent(WebView::EventType::REQUEST);
    }
    
    
    // スキーマがcocos2dxだったらなにもしない(webviewを閉じるときなどに使用する
    if([checkURL hasPrefix:@"cocos2dx:"])
    {
        return NO;
    }
    
    // 指定のドメインのみブラウザで起動する
    NSLog(@"shouldStartLoadWithRequest:%ld", _openDomain.size());
    for(auto it = _openDomain.begin(); it != _openDomain.end(); it++)
    {
        NSRange linkMatch = [checkURL rangeOfString:@((*it).c_str())];
        
        if (linkMatch.location != NSNotFound) {
            [[UIApplication sharedApplication] openURL:request.URL];
            return NO;
        }
    }

    
    return YES;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    if(_webView != nullptr)
    {
        _view->onWebViewEvent(WebView::EventType::FINISH);
    }
}
     
- (void)webViewDidStartLoad:(UIWebView *)webView
{
    if(_webView != nullptr)
    {
        _view->onWebViewEvent(WebView::EventType::START);
    }
}



-(void) setVisible:(bool)visible
{
    if (self.webView != NULL) {
        [self.webView setHidden:visible];
    }
}




@end
//------------------------------------------------------------------------------------------------------------

WebView::WebView()
: _eventCallback(nullptr)
{
    _webView = [[UIWebViewWrapperIos alloc] init:this];
}

WebView::~WebView()
{
    if(_webView)
    {
        [((UIWebViewWrapperIos*)_webView) dealloc];
    }
}


void WebView::setHtml(const std::string& html)
{
    _html = html;
    [((UIWebViewWrapperIos*)_webView) loadData:_html];
}


void WebView::setURL(const std::string& url)
{
    _url = url;
    [((UIWebViewWrapperIos*)_webView) loadURL:_url];
}

void WebView::setOpenDomains(const std::vector<std::string>& openDomains)
{
    _openDomains = openDomains;
    [((UIWebViewWrapperIos*)_webView) setOpenDomains:_openDomains];
}

void WebView::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
    cocos2d::ui::Widget::draw(renderer,transform,transformUpdated);
    
    if (transformUpdated)
    {
        auto directorInstance = cocos2d::Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();
        auto scaleFactor = directorInstance->getContentScaleFactor();
        
        auto winSize = directorInstance->getWinSize();
        
        auto leftBottom = convertToWorldSpace(cocos2d::Vec2::ZERO);
        auto rightTop = convertToWorldSpace(cocos2d::Vec2(_contentSize.width,_contentSize.height));
        
        auto uiLeft = (frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX()) / scaleFactor;
        auto uiTop = (frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY()) / scaleFactor;
        
        [((UIWebViewWrapperIos*)_webView) setFrame :uiLeft :uiTop
                                                       :(rightTop.x - leftBottom.x) * glView->getScaleX() / scaleFactor
                                                       :( (rightTop.y - leftBottom.y) * glView->getScaleY()/scaleFactor)];
    }
    

}

void WebView::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);
    

    [((UIWebViewWrapperIos*)_webView) setVisible:visible];

}

void WebView::addEventListener(const WebView::ccWebViewCallback& callback)
{
    _eventCallback = callback;
}

void WebView::onWebViewEvent(WebView::EventType event)
{
    if (_eventCallback)
    {
        _eventCallback(this, event);
    }
}

cocos2d::ui::Widget* WebView::createCloneInstance()
{
    return WebView::create();
}


#endif
