#include "EffectMng.h"

EffectMng* EffectMng::s_Instance = nullptr;

EffectMng::EffectMng()
{
	manager = nullptr;

	auto director = cocos2d::Director::getInstance();
	auto rsize = director->getOpenGLView()->getDesignResolutionSize();

	manager = efk::EffectManager::create(rsize);
}

EffectMng::~EffectMng()
{
	manager->release();
}

bool EffectMng::Init()
{
	
	emitter = efk::EffectEmitter::create(manager);
	
	return false;
}

bool EffectMng::Create(std::string effectName,std::string imageName)
{
	auto effect = efk::Effect::create(imageName);
	if (effect == nullptr)
	{
		return false;
	}
	if (effectData.insert(std::make_pair(effectName, efk::EffectEmitter::create(manager))).second)
	{
		effectData[effectName]->setEffect(effect);

		return true;
	}
	return false;
}

void EffectMng::Pos(std::string effectName, cocos2d::Vec2 pos)
{
	effectData[effectName]->setPosition(pos);
}

void EffectMng::Scale(std::string effectName, int scale)
{
	effectData[effectName]->setScale(scale);
}

void EffectMng::PlayEffect(std::string effectName, bool playEffect)
{
	effectData[effectName]->setPlayOnEnter(playEffect);
}

efk::EffectEmitter* EffectMng::AddLayer(std::string layerName, std::string effectName)
{
	auto director = cocos2d::Director::getInstance();
	manager->setIsDistortionEnabled(true);
	//director->getRunningScene()->getChildByName(layerName)->addChild(effectData[effectName]);

	return effectData[effectName];
}

void EffectMng::update()
{
	//emitter->setRemoveOnStop(false);
	//if (emitter->getPlayOnEnter())
	//{
	//	emitter->setIsLooping(true);
	//}

	for (auto effect : effectData)
	{
		effect.second->setRemoveOnStop(false);
		if (effect.second->getPlayOnEnter())
		{
			effect.second->setIsLooping(true);
		}
	}

	manager->update();
}

efk::EffectEmitter & EffectMng::GetEfkEmitter()
{
	return *emitter;
}