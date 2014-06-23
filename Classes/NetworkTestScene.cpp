//
//  NetworkTestScene.cpp
//  cocos2dx-sandbox
//
//  Created by t_akaishi on 2014/06/20.
//
//

#include "NetworkTestScene.h"
#include "picojson/picojson.h"
// #include "external/unzip/unzip.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* NetworkTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NetworkTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NetworkTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    {
        auto request = new network::HttpRequest();
        request->setUrl("http://weather.livedoor.com/forecast/webservice/json/v1?city=400040");
        request->setRequestType(network::HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(NetworkTest::httpCallback, this));
        request->setTag("json");
        network::HttpClient::getInstance()->send(request);
    }
    
    {
        auto request = new network::HttpRequest();
        request->setUrl("http://www.colorado.edu/conflict/peace/download/peace.zip");
        request->setRequestType(network::HttpRequest::Type::GET);
        request->setResponseCallback([this](network::HttpClient* client, network::HttpResponse* response){
            if(false == response->isSucceed()) {
                return;
            }
            /*
            
            auto buff = response->getResponseData();
            
            std::string filePath = FileUtils::getInstance()->getWritablePath();
            std::string zipFile = "img_100.zip";
            std::string path = filePath.c_str() + zipFile;
            
            
            // zipファイルの保存
            auto fp = fopen(path.c_str() , "wb");
            CCLOG("debug writtern :: %zu" , fwrite(buff->data() , 1, buff->size() , fp));
            fclose(fp);
            
            auto zipfile = unzOpen(path.c_str());
            unz_global_info global_info;
            if ( unzGetGlobalInfo( zipfile, &global_info ) != UNZ_OK )
            {
                printf( "could not read file global infon" );
                unzClose( zipfile );
                return;
            }
            
            unzGoToFirstFile(zipfile);
            for ( uLong i = 0; i < global_info.number_entry; ++i )
            {
                // Get info about current file.
                char filename[ 100 ];
                if ( unzGetCurrentFileInfo64(zipfile,
                                             NULL,
                                             filename,
                                             100,
                                             NULL, 0, NULL, 0)
                    
                    != UNZ_OK )
                {
                    CCLOG( "could not read file" );
                    unzClose( zipfile );
                    return;
                }
                auto str = std::string(filename);
                
                CCLOG("file[%lu] name == %s" , i , str.c_str());
                // ここでstd::vectorにでも詰めればOK
                
                // 次にカーソルを進める
                unzGoToNextFile(zipfile);
            }
            // 終わったらcloseを忘れずに。
            unzClose(zipfile);
            */
            
        });
        request->setTag("json");
        network::HttpClient::getInstance()->send(request);
    }
    
    
    /*
    auto assetsManager = new AssetsManager("https://raw.github.com/samuele3hu/AssetsManagerTest/master/package.zip",
                      "https://raw.github.com/samuele3hu/AssetsManagerTest/master/version",
                      FileUtils::getInstance()->getWritablePath().c_str());
    assetsManager->setDelegate(this);
    assetsManager->update();
    */
    
    return true;
}

void NetworkTest::httpCallback(network::HttpClient* client, network::HttpResponse* response) {
    
    if(false == response->isSucceed()) {
        return;
    }
    

    auto buff = response->getResponseData();
    
    std::string data(buff->begin(), buff->end());
    
    CCLOG("data=>%s", data.c_str());
    
    picojson::value v;
    std::string err;
    picojson::parse(v, data.c_str(), data.c_str() + strlen(data.c_str()), &err);
    if(! err.empty()) {
        CCLOG("error:%s", err.c_str());
        return;
    }
    
    auto array = v.get<picojson::object>()["pinpointLocations"].get<picojson::array>();
    for(auto it = array.begin(); it != array.end(); it++) {
        CCLOG("name:%s=>link:%s", it->get<picojson::object>()["name"].get<std::string>().c_str(), it->get<picojson::object>()["link"].get<std::string>().c_str());
    }
    

}

/*
void NetworkTest::onError(cocos2d::extension::AssetsManager::ErrorCode errorCode) {
    
}
void NetworkTest::onProgress(int percent) {
    CCLOG("onProgress:%d", percent);
}
void NetworkTest::onSuccess() {
    CCLOG("onSuccess");
}
*/
