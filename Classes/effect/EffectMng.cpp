#include "EffectMng.h"


EffectMng::EffectMng()
{
}

EffectMng::~EffectMng()
{
	manager->release();
}

bool EffectMng::init()
{
	manager = nullptr;
	
	return false;
}

void EffectMng::AddEffect(std::string layerName)
{
	auto director = cocos2d::Director::getInstance();
	auto rsize = director->getOpenGLView()->getDesignResolutionSize();

	manager = efk::EffectManager::create(rsize);
	emitter = efk::EffectEmitter::create(manager);
	manager->setIsDistortionEnabled(true);
	director->getRunningScene()->getChildByName(layerName)->addChild(emitter);
}

void EffectMng::update()
{
	//emitter->setRemoveOnStop(false);
	if (emitter->getPlayOnEnter())
	{
		emitter->setIsLooping(true);
	}
	
	manager->update();
}

efk::EffectEmitter & EffectMng::GetEfkEmitter()
{
	return *emitter;
}