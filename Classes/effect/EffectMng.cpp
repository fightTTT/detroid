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

void EffectMng::AddEffect(EffectStatus efkState)
{
	auto rsize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	manager = efk::EffectManager::create(rsize);
	auto effect = efk::Effect::create(efkState.efkFileName);
	emitter = efk::EffectEmitter::create(manager);
	manager->setIsDistortionEnabled(true);
	emitter->setPlayOnEnter(true);
	emitter->setPosition(efkState.pos);	
	emitter->setScale(efkState.scale);
	emitter->setEffect(effect);

}

void EffectMng::update()
{
	emitter->setRemoveOnStop(false);
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