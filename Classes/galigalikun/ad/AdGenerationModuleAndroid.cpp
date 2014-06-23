#include "AdGenerationModule.h"


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
}

void AdGenerationModule::createView(const char* locationid, AdType adtype, cocos2d::Point pos)
{
}

void AdGenerationModule::createViewTop(const char *locationid, AdType adtype){
}

void AdGenerationModule::createViewBottom(const char *locationid, AdType adtype){
}

void AdGenerationModule::hideView()
{
}

void AdGenerationModule::showView()
{
}

void AdGenerationModule::load()
{
}

void AdGenerationModule::pause()
{
}

void AdGenerationModule::resume()
{
}

void AdGenerationModule::release(){
}
