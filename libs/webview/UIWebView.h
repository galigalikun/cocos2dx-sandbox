#ifndef __COCOS2D_UI_WEBVIEW_H_
#define __COCOS2D_UI_WEBVIEW_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ui/UIWidget.h"

namespace galigalikun {
    namespace ui{

        class WebView : public cocos2d::ui::Widget
        {
        public:
            enum class EventType
            {
                ERROR = 0,
                REQUEST,
                FINISH,
                START
            };
            typedef std::function<void(Ref*, WebView::EventType)> ccWebViewCallback;

            CREATE_FUNC(WebView);

            //Sets local file[support assets' file on android] as a video source for VideoPlayer
            virtual void setFileName(const std::string&);
            virtual const std::string& getFileName() const { return _file;}

            virtual void setURL(const std::string&);
            virtual const std::string& getURL() const { return _url;}
            
            virtual void setOpenDomains(const std::vector<std::string>&);

            virtual void setVisible(bool visible) override;

            virtual void addEventListener(const WebView::ccWebViewCallback&);
            virtual void onWebViewEvent(WebView::EventType);
            virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, bool transformUpdated) override;

        protected:
            virtual cocos2d::ui::Widget* createCloneInstance() override;
            
            WebView();
            virtual ~WebView();

            std::string _file;
            std::string _url;
            std::vector<std::string> _openDomains;

            ccWebViewCallback _eventCallback;

            void* _webView;
        };
    }
}


#endif
#endif
