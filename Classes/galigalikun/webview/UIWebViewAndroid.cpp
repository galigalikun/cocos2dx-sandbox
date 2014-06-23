#include "UIWebView.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <unordered_map>
#include <stdlib.h>
#include <jni.h>
#include <string>
#include "jni/JniHelper.h"

WebView::WebView()
: _eventCallback(nullptr)
{
}

WebView::~WebView()
{
    if(_webView)
    {
    }
}


void WebView::setHtml(const std::string& html)
{
    _html = html;
}


void WebView::setURL(const std::string& url)
{
    _url = url;
}

void WebView::setOpenDomains(const std::vector<std::string>& openDomains)
{
    _openDomains = openDomains;
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
        
    }
    

}

void WebView::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);
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
